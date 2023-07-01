/*
    This file is part of RTCore, an open-source physically based
    renderer.
    Copyright (c) 2020-2023 Samuel Van Allen - All rights reserved.
    RTCore is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "playground.h"

#include "core/camera/perspectivecamera.h"
#include "core/spectrum/illuminantspectrum.h"
#include "core/spectrum/reflectantspectrum.h"
#include "exporter/stbexporter.h"

#include <chrono>
#include <iostream>

#include <thread>
#include "system/threading/threadpool.h"
#include <core/sampling/sampling.h>
#include <core/camera/orthographiccamera.h>

#include "core/film/tonemapper/uncharted2filmictonemapper.h"

/* ====================================================================
    BANNER OF SHAME
    MESSY TEMP TEST CODE HERE
   ==================================================================== */



float* hdri;
int hdri_w;
int hdri_h;
int hdri_stride = 3;
int hdri_rowpitch;
float exposure = 255;

RgbCoefficients SampleHdri(Point2 uv)
{
    int x = (uv.x * hdri_w);
    int y = uv.y * hdri_h;

    int addr = hdri_rowpitch * y + hdri_stride * x;
    RgbCoefficients out = { hdri[addr] / 255.0, hdri[addr + 1] / 255.0, hdri[addr + 2] / 255.0};
    return out * exposure;
}

Point2 ToSphericalCoordinates(const Vector3& cartesian)
{
    Vector3 proj = cartesian;
    proj.y = 0;
    proj.Normalize();

    double theta = Vector3::Angle(proj, { 1, 0,0 });
    bool thetaExceeds180 = Vector3::Cross(proj, { 1, 0, 0 }).y > 0;

    if (thetaExceeds180)
        theta = 2 * SMath::Pi - theta;

    theta /= (SMath::Pi * 2);

    double phi = Vector3::Angle(cartesian, { 0, 1, 0 }) / (SMath::Pi);

    return { theta, phi };
}

double GetLuminance(const RgbCoefficients& color)
{
    return 0.2126 * color[0] + 0.7152 * color[1] + 0.0722 * color[2];
}

double GetHdriWhitePoint()
{
    double maxLuminance = 0;

    for (int x = 0; x < hdri_w; ++x)
    {
        for (int y = 0; y < hdri_h; ++y)
        {
            RgbCoefficients color = SampleHdri(Point2(x/ (double)hdri_w, y/ (double)hdri_h));
            double lum = GetLuminance(color);

            if (lum > maxLuminance)
                maxLuminance = lum;
        }
    }

    return maxLuminance;
}


struct hit_record;

class aabb {
public:
    aabb() {}
    aabb(const Point3& a, const Point3& b) { minimum = a; maximum = b; }

    Point3 min() const { return minimum; }
    Point3 max() const { return maximum; }

    bool hit(const Ray& r, double t_min, double t_max) const {
        for (int a = 0; a < 3; a++) {
            auto t0 = std::fmin((minimum[a] - r.GetOrigin()[a]) / r.GetDirection()[a],
                (maximum[a] - r.GetOrigin()[a]) / r.GetDirection()[a]);
            auto t1 = std::fmax((minimum[a] - r.GetOrigin()[a]) / r.GetDirection()[a],
                (maximum[a] - r.GetOrigin()[a]) / r.GetDirection()[a]);
            t_min = std::fmax(t0, t_min);
            t_max = std::fmin(t1, t_max);
            if (t_max <= t_min)
                return false;
        }
        return true;
    }

    Point3 minimum;
    Point3 maximum;
};

class material {
public:
    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, Spectrum* attenuation, Ray& scattered
    ) const = 0;

    virtual Spectrum emitted() const {
        return {};
    }
};

Vector3 reflect(const Vector3& v, const Normal3& n) {
    return v - Vector3(2) * Vector3(Vector3::Dot(v, n)) * n;
}

Vector3 refract(const Vector3& uv, const Normal3& n, double etai_over_etat) {
    auto cos_theta = fmin(Vector3::Dot(-uv, n), 1.0);
    Vector3 r_out_perp = Vector3(etai_over_etat) * (uv + Vector3(cos_theta) * n);
    Vector3 r_out_parallel = Vector3(-sqrt(fabs(1.0 - r_out_perp.SquareMagnitude()))) * n;
    return r_out_perp + r_out_parallel;
}
struct hit_record {
    Point3 p;
    Normal3 normal;
    double t;
    std::shared_ptr<material> mat_ptr;

    int lambdaIndex;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Normal3& outward_normal) {
        front_face = Vector3::Dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : Normal3(-outward_normal);
    }
};
class lambertian : public material {
public:
    lambertian(Spectrum* a) : albedo(a) {}

    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, Spectrum* attenuation, Ray& scattered
    ) const override {
        Vector3 scatter_direction = rec.normal + (Sampling::UniformSampleSphere() - Point3(0,0,0));

        // Catch degenerate scatter direction
        if (scatter_direction.SquareMagnitude() <= 0.001)
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);
        *attenuation = *albedo;
        return true;
    }

public:
    Spectrum* albedo;
};

class dielectric : public material {
public:
    dielectric(Spectrum index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, Spectrum* attenuation, Ray& scattered
    ) const override {
        *attenuation = ReflectantSpectrum({ 0.9, 1.0, 1.0 });
        Spectrum refraction_ratio = rec.front_face ? (Spectrum(1.0) / ir) : ir;

        Vector3 unit_direction = r_in.GetDirection().Normalized();
        double cos_theta = fmin(Vector3::Dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio.m_Coefficients[rec.lambdaIndex] * sin_theta > 1.0;
        Vector3 direction;
        double glossF = 0;
        Point3 glossFactor = Sampling::UniformSampleSphere();
        glossFactor.x *= glossF;
        glossFactor.y *= glossF;
        glossFactor.z *= glossF;
        Vector3 glossVec = glossFactor - Point3(0,0,0);

        if (cannot_refract || reflectance(cos_theta, refraction_ratio.m_Coefficients[rec.lambdaIndex]) > SMath::Random::UniformFloat())
            direction = (reflect(unit_direction, rec.normal) + glossVec).Normalized();
        else
            direction = (refract(unit_direction, rec.normal, refraction_ratio.m_Coefficients[rec.lambdaIndex]) + glossVec).Normalized();

        scattered = Ray(rec.p, direction);
        return true;
    }

private:
    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

public:
    Spectrum ir; // Index of Refraction
};

class diffuse_light : public material {
public:
    diffuse_light(Spectrum* a) : emit(a) {}

    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, Spectrum* attenuation, Ray& scattered
    ) const override {
        return false;
    }

    virtual Spectrum emitted() const override {
        return *emit;
    }

public:
    Spectrum* emit;
};


class hittable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;

};

class sphere : public hittable {
public:
    sphere() {}
    sphere(Point3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(
        const Ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

public:
    Point3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;

};

bool sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    Vector3 oc = (r.GetOrigin() - center);
    auto a = r.GetDirection().SquareMagnitude();
    auto half_b = Vector3::Dot(oc, r.GetDirection());
    auto c = oc.SquareMagnitude() - radius * radius;
    ;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r(rec.t);
    Vector3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal.Normalized());
    rec.mat_ptr = mat_ptr;

    return true;
}

bool sphere::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = aabb(
        center - Vector3(radius, radius, radius),
        center + Vector3(radius, radius, radius));
    return true;
}


class hittable_list : public hittable {
public:
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(
        const Ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(
        double time0, double time1, aabb& output_box) const override;

public:
    std::vector<std::shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
aabb surrounding_box(aabb box0, aabb box1) {
    Point3 small(std::fmin(box0.min().x, box1.min().x),
        std::fmin(box0.min().y, box1.min().y),
        std::fmin(box0.min().z, box1.min().z));

    Point3 big(std::fmax(box0.max().x, box1.max().x),
        fmax(box0.max().y, box1.max().y),
        fmax(box0.max().z, box1.max().z));

    return aabb(small, big);
}

bool hittable_list::bounding_box(double time0, double time1, aabb& output_box) const {
    if (objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto& object : objects) {
        if (!object->bounding_box(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}

hittable_list world;

Spectrum raytraceScene(const Ray& ray, int lambdaIdx, int depth)
{
    hit_record hit;
    if (world.hit(ray, 0.001, 99999999, hit) && depth > 0)
    {
        Spectrum attenuation;
        Ray scattered(Point3{}, Vector3{});
        hit.lambdaIndex = lambdaIdx;

        Spectrum emitted = hit.mat_ptr->emitted();

        if (!hit.mat_ptr->scatter(ray, hit, &attenuation, scattered))
            return emitted;

        return emitted + attenuation * raytraceScene(scattered, lambdaIdx, depth - 1);
    }

    Vector3 unit_direction = ray.GetDirection().Normalized();
    RgbCoefficients hdri = SampleHdri(ToSphericalCoordinates(unit_direction));

    //auto t = 0.5 * (unit_direction.y + 1.0);
    //Vector3 skyColorVec = Vector3(1.0 - t) * Vector3(1.0, 1.0, 1.0) + Vector3(t) * Vector3(0.5, 0.7, 1.0);
    //RgbCoefficients skyColor(skyColorVec[0], skyColorVec[1], skyColorVec[2]);
    return ReflectantSpectrum(hdri);
}

inline bool box_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, int axis) {
    aabb box_a;
    aabb box_b;

    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min()[axis] < box_b.min()[axis];
}


bool box_x_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    return box_compare(a, b, 2);
}


class bvh_node : public hittable {
public:
    bvh_node();

    bvh_node(const hittable_list& list, double time0, double time1)
        : bvh_node(list.objects, 0, list.objects.size(), time0, time1)
    {}

    bvh_node(
        const std::vector<std::shared_ptr<hittable>>& src_objects,
        size_t start, size_t end, double time0, double time1)
    {

        auto objects = src_objects; // Create a modifiable array of the source scene objects

        int axis = SMath::Random::UniformInt(0, 2);
        auto comparator = (axis == 0) ? box_x_compare
            : (axis == 1) ? box_y_compare
            : box_z_compare;

        size_t object_span = end - start;

        if (object_span == 1) {
            left = right = objects[start];
        }
        else if (object_span == 2) {
            if (comparator(objects[start], objects[start + 1])) {
                left = objects[start];
                right = objects[start + 1];
            }
            else {
                left = objects[start + 1];
                right = objects[start];
            }
        }
        else {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            auto mid = start + object_span / 2;
            left = std::make_shared<bvh_node>(objects, start, mid, time0, time1);
            right = std::make_shared<bvh_node>(objects, mid, end, time0, time1);
        }

        aabb box_left, box_right;

        if (!left->bounding_box(time0, time1, box_left)
            || !right->bounding_box(time0, time1, box_right)
            )
            std::cerr << "No bounding box in bvh_node constructor.\n";

        box = surrounding_box(box_left, box_right);

    }

    virtual bool hit(
        const Ray& r, double t_min, double t_max, hit_record& rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

public:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    aabb box;
};

bool bvh_node::bounding_box(double time0, double time1, aabb& output_box) const {
    output_box = box;
    return true;
}

bool bvh_node::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


//#define DEBUG_HDRI

#ifdef DEBUG_HDRI
const int NumSamples = 1;
#else
const int NumSamples = 100;
#endif

const int NumThreads = 15;
constexpr double DeltaArea = 1.0 / NumSamples;

void Playground::RenderThing()
{
    int actualNumChannels;
    hdri = stbi_loadf("D:\\Graphics_Projects\\Atelier\\Workspaces\\Hdri\\shanghai_bund_16k.hdr", &hdri_w, &hdri_h, &actualNumChannels, 0);

    if (hdri == nullptr)
        std::cerr << "Failed to load HDRI\n" << std::endl;

    hdri_rowpitch = hdri_w * hdri_stride;
    double hdriWhitepoint = GetHdriWhitePoint();

    SMath::Random::Seed(0);
    //Random::Seed(std::chrono::system_clock::now().time_since_epoch().count());
    double perspectiveFov = 75.0;
    //double orthoSize = 1.0;
    PerspectiveCamera camera(perspectiveFov);
    //OrthographicCamera camera(1.0);

    Film m_Film = camera.GetFilm();
    Matrix4x4& transform = camera.GetTransform();
    transform = Transform::GetTranslationMatrix({ 0, 0.2, -3.5 }) * Transform::GetRotationMatrix({ SMath::DegToRad(0.0), SMath::DegToRad(0.0), 0 });

    ReflectantSpectrum groundColor({ 0.8, 0.8, 0.8 });
    ReflectantSpectrum red({ 0.8, 0.2, 0.25 });
    ReflectantSpectrum white({ 1.0, 1.0, 1.0 });
    ReflectantSpectrum black({ 0.1, 0.1, 0.1 });
    IlluminantSpectrum lightColor({ 50.8, 50.8, 50.8 });

    SampleArray samples = { {MinWavelength, 1.3}, {MaxWavelength, 1.5} };
    SampledSpectrum ir(samples);

    auto material_ground = std::make_shared<lambertian>(&groundColor);
    auto material_red = std::make_shared<lambertian>(&red);
    auto material_white = std::make_shared<lambertian>(&white);
    auto material_black = std::make_shared<lambertian>(&black);
    auto material_glass = std::make_shared<dielectric>(ir);
    auto material_light = std::make_shared<diffuse_light>(&lightColor);

    world.add(std::make_shared<sphere>(Point3(0, 0.2, -1), 0.5, material_glass));
    //world.add(std::make_shared<sphere>(Point3(-0.5, 1, -0.5), 0.2, material_light));
    //world.add(std::make_shared<sphere>(Point3(0.9, -0.1, 4.5), 0.5, material_ground));
    //world.add(std::make_shared<sphere>(Point3(1.1, -0.1, 5.5), 0.9, material_black));
    //world.add(std::make_shared<sphere>(Point3(0, -100.5, -1), 100, material_white));
    //world.add(std::make_shared<sphere>(Point3(0, -100.65, 2), 100, material_black));

    std::shared_ptr<Tonemapper> tonemapper = std::make_shared<Uncharted2FilmicTonemapper>();
    StbExporter exporter(tonemapper);

    std::chrono::milliseconds startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    std::string filename = std::to_string(startTime.count());
    exporter.SetOutputName(filename);

    Resolution resolution = m_Film.GetResolution();

    /*
                y
                |      z
                |    /
                |   /
                |  /
                | /
        Camera  * ------------- x
    */

    {
        std::mutex timeMutex;
        auto lastExportTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

        int numSamplesLeft = NumSamples;

        while (numSamplesLeft > 0)
        {
            int numSamplesThisRun = std::min(1024, numSamplesLeft);
            ThreadPool threadPool(NumThreads);
            std::mutex mutex;
            mutex.lock();
            // Lockup first thread to give time to adding other tasks
            threadPool.ScheduleTask(99999, [&]()
            {
                std::lock_guard<std::mutex> lock(mutex);
            });


            for (int i = 0; i < m_Film.GetNumTiles(); ++i)
            {
                FilmTile* currentTile = &m_Film.GetTile(i);
                double distFromCenterX = std::abs(currentTile->GetPosition().x - (resolution.GetWidth() / 2.0));
                double distFromCenterY = std::abs(currentTile->GetPosition().y - (resolution.GetHeight() / 2.0));
                double priority = 100.0 / std::sqrt(distFromCenterX * distFromCenterX + distFromCenterY * distFromCenterY);

                threadPool.ScheduleTask(priority, [&](FilmTile* currentTile, double priority)
                {
                    for (int y = 0; y < currentTile->GetSize().y; ++y)
                    {
                        for (int x = 0; x < currentTile->GetSize().x; ++x)
                        {

                            Point2i tileSpacePos = { x, y };
                            Point2i filmSpacePos = currentTile->TileToFilmSpace(tileSpacePos);

                            for (int i = 0; i < numSamplesThisRun; ++i)
                            {
                                const int StepSize = WavelengthRange / NumSpectralSamples;

                                int wIdx = SMath::Random::UniformInt(0, NumSpectralSamples);
                                int w = MinWavelength + (int)(wIdx * StepSize);
                                double pdf = 1.0 / NumSpectralSamples;
                                Point2 randomInDisk = Sampling::RejectionSampleDisk();

                                Ray ray = camera.GenerateRay(filmSpacePos, {randomInDisk.x / 2.0, randomInDisk.y / 2.0});
                                SampleArray singleW = { SpectralSample(w - StepSize, 0), SpectralSample(w, 1 / pdf), SpectralSample(w + StepSize, 0) };
                                SampledSpectrum singleColoredRay(singleW);


#ifdef DEBUG_HDRI
                                Point2 hdri(filmSpacePos.x / (double)resolution.GetWidth(), filmSpacePos.y / (double)resolution.GetHeight());
                                ReflectantSpectrum L(SampleHdri(hdri));
#else
                                Spectrum L = singleColoredRay * raytraceScene(ray, wIdx, 6);
#endif
                                SampledSpectrum L2(L);
                                currentTile->SplatPixel(tileSpacePos, L2.ToXyz(), DeltaArea);
                            }

                            auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::system_clock::now().time_since_epoch()).count();
                            {
                                if (timeNow - lastExportTime > 10000)
                                {
                                    lastExportTime = timeNow;
                                    std::cout << "Exporting tile {" << std::to_string(currentTile->GetPosition().x) << ", " << std::to_string(currentTile->GetPosition().y) << "}, priority: " << std::to_string(priority) << std::endl;
                                    exporter.Export(m_Film);
                                }
                            }
                        }
                    }
                }, currentTile, priority);
            }

            mutex.unlock();

            std::cout << "Samples remaining: " << std::to_string(numSamplesLeft) << std::endl;
            numSamplesLeft -= numSamplesThisRun;
        }
    }

    std::chrono::milliseconds endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch());
    std::cout << "Time elapsed: " << endTime - startTime << std::endl;


    exporter.Export(m_Film);

    //system((".\\" + filename + ".png").c_str());
}