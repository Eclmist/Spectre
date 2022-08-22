#include "perspectivecamera.h"
#include "core/spectrum/illuminantspectrum.h"
#include "core/spectrum/reflectantspectrum.h"
#include "exporter/stbexporter.h"

#include <chrono>
#include <iostream>

#include "core/ray/ray.h"
#include <thread>
#include "system/threading/threadpool.h"
#include <core/sampling/sampling.h>

const int NumSamples = 30000;
constexpr double DeltaArea = 1.0 / NumSamples;
struct hit_record;

class material {
public:
	virtual bool scatter(
		const Ray& r_in, const hit_record& rec, Spectrum* attenuation, Ray& scattered
	) const = 0;
};

Vector3 reflect(const Vector3& v, const Vector3& n) {
	return v - Vector3(2) * Vector3(Vector3::Dot(v, n)) * n;
}

Vector3 refract(const Vector3& uv, const Vector3& n, double etai_over_etat) {
	auto cos_theta = fmin(Vector3::Dot(-uv, n), 1.0);
	Vector3 r_out_perp = Vector3(etai_over_etat) * (uv + Vector3(cos_theta) * n);
	Vector3 r_out_parallel = Vector3(-sqrt(fabs(1.0 - r_out_perp.SquareMagnitude()))) * n;
	return r_out_perp + r_out_parallel;
}
struct hit_record {
	Vector3 p;
	Vector3 normal;
	double t;
	std::shared_ptr<material> mat_ptr;

	int lambdaIndex;
	bool front_face;

	inline void set_face_normal(const Ray& r, const Vector3& outward_normal) {
		front_face = Vector3::Dot(r.GetDirection(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};
class lambertian : public material {
public:
	lambertian(Spectrum* a) : albedo(a) {}

	virtual bool scatter(
		const Ray& r_in, const hit_record& rec, Spectrum* attenuation, Ray& scattered
	) const override {
		auto scatter_direction = rec.normal + Sampling::UniformSampleSphere();

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
		*attenuation = ReflectantSpectrum({ 1.0, 1.0, 1.0 });
		Spectrum refraction_ratio = rec.front_face ? (Spectrum(1.0) / ir) : ir;

		Vector3 unit_direction = r_in.GetDirection().Normalized();
		double cos_theta = fmin(Vector3::Dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio.m_Coefficients[rec.lambdaIndex] * sin_theta > 1.0;
		Vector3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio.m_Coefficients[rec.lambdaIndex]) > Random::UniformFloat())
			direction = reflect(unit_direction, rec.normal);
		else
			direction = refract(unit_direction, rec.normal, refraction_ratio.m_Coefficients[rec.lambdaIndex]);

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



class hittable {
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

class sphere : public hittable {
public:
	sphere() {}
	sphere(Vector3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(
		const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	Vector3 center;
	double radius;
	std::shared_ptr<material> mat_ptr;

};

bool sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
	Vector3 oc = r.GetOrigin() - center;
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
    rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

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

hittable_list world;

void raytraceScene(const Ray& ray, int lambdaIdx, Spectrum* spectrum, int depth)
{
	hit_record hit;
	if (world.hit(ray, 0.001, 99999999, hit) && depth > 0)
	{
		Vector3 target = hit.p + hit.normal + Sampling::UniformSampleSphere();

		Spectrum spec;
		Ray scattered(Vector3{}, Vector3{});
		hit.lambdaIndex = lambdaIdx;
		if (hit.mat_ptr->scatter(ray, hit, &spec, scattered))
		{
			*spectrum *= spec;// ReflectantSpectrum({ 0.5, 0.5, 0.5 });
			raytraceScene(scattered, lambdaIdx, spectrum, depth - 1);
		}
		else
		{
			*spectrum *= 0;
		}
	}

	Vector3 unit_direction = ray.GetDirection().Normalized();
	auto t = 0.5 * (unit_direction.y + 1.0);
	Vector3 skyColorVec = Vector3(1.0 - t) * Vector3(1.0, 1.0, 1.0) + Vector3(t) * Vector3(0.5, 0.7, 1.0);
	RgbCoefficients skyColor(skyColorVec[0], skyColorVec[1], skyColorVec[2]);
	*spectrum *= ReflectantSpectrum(skyColor);
}
void PerspectiveCamera::Render()
{
	Random::Seed(0);

	//Resolution resolution;
	//resolution.SetWidth(800);
	//resolution.SetHeight(4);
	//m_Film.SetResolution(resolution);

	ReflectantSpectrum groundColor({ 0.8, 0.8, 0.8 });
	ReflectantSpectrum red({ 0.8, 0.2, 0.25 });
	ReflectantSpectrum black({ 0.1, 0.1, 0.1 });
	IlluminantSpectrum lightColor({ 50.8, 50.8, 50.8 });

	SampleArray samples = { {MinWavelength, 1.35}, {MaxWavelength, 1.55} };
	SampledSpectrum ir(samples);


	auto material_ground = std::make_shared<lambertian>(&groundColor);
	auto material_red = std::make_shared<lambertian>(&red);
	auto material_black = std::make_shared<lambertian>(&black);
	auto material_glass = std::make_shared<dielectric>(ir);
	auto material_light = std::make_shared<lambertian>(&lightColor);

	world.add(std::make_shared<sphere>(Vector3(0, 0.2, -1), 0.5, material_glass));
	world.add(std::make_shared<sphere>(Vector3(-0.5, 1, -0.5), 0.2, material_light));
	world.add(std::make_shared<sphere>(Vector3(0.9, -0.1, 4.5), 0.6, material_ground));
	world.add(std::make_shared<sphere>(Vector3(1.1, -0.1, 5.5), 0.9, material_black));
	world.add(std::make_shared<sphere>(Vector3(0, -100.5, -1), 100, material_red));
	world.add(std::make_shared<sphere>(Vector3(0, -100.65, 2), 100, material_black));

	StbExporter exporter;
	std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch());
	std::string filename = std::to_string(ms.count());
	exporter.SetOutputName(filename);

	Resolution resolution = m_Film.GetResolution();

	/*
				y	
				|	  z
				|    /
				|   /  
				|  /
				| /	
		Camera  * ------------- x
		
	*/

	{
		std::mutex timeMutex;
		auto lastExportTime = duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

		int numSamplesLeft = NumSamples;

		while(numSamplesLeft > 0)
		{
			int numSamplesThisRun = std::min(256, numSamplesLeft);
			ThreadPool threadPool(15);

			for (int i = 0; i < m_Film.GetNumTiles(); ++i)
			{
				double fov = 25.0;
				double fov2 = fov / 2.0;
				double filmZPlane = (resolution.GetWidth() / 2.0) / std::tan(Math::DegToRad(fov2));

				FilmTile* currentTile = &m_Film.GetTile(i);
				double distFromCenterX = std::abs(currentTile->GetPosition().x - (resolution.GetWidth() / 2.0));
				double distFromCenterY = std::abs(currentTile->GetPosition().y - (resolution.GetHeight() / 2.0));
				double priority = std::sqrt(distFromCenterX * distFromCenterX + distFromCenterY * distFromCenterY);

				threadPool.ScheduleTask(priority, [=, &exporter, &timeMutex, &lastExportTime]()
				{
					for (int y = 0; y < currentTile->GetSize().y; ++y)
					{
						for (int x = 0; x < currentTile->GetSize().x; ++x)
						{
							Vector2i tileSpacePos = { x, y };
							Vector2i filmSpacePos = currentTile->TileToFilmSpace(tileSpacePos);

							double rayDirX = filmSpacePos.x - resolution.GetWidth() / 2.0;
							double rayDirY = resolution.GetHeight() / 2.0 - filmSpacePos.y;

							for (int i = 0; i < numSamplesThisRun; ++i)
							{
								//\sin\left(\frac{ x }{47.621\pi}\right)\ \cdot\ 0.00334211677814

								//double pdf = std::sin(w / (47.621 * Math::Pi)) * 0.00334211677814

								int w = (int)(Random::UniformFloat() * (MaxWavelength - MinWavelength) + MinWavelength);
								Vector2 randomInDisk = Sampling::RejectionSampleDisk() / Vector2(2.0);
								Ray ray({ 0, 0.5, -10 }, { rayDirX + randomInDisk.x, rayDirY + randomInDisk.y, filmZPlane });
								SampledSpectrum singleColoredRay(0);
								singleColoredRay.m_Coefficients[w - MinWavelength] = (MaxWavelength - MinWavelength);

								raytraceScene(ray, w - MinWavelength, &singleColoredRay, 8);
								currentTile->SplatPixel(tileSpacePos, singleColoredRay.ToXyz(), DeltaArea);
							}

							auto timeNow = duration_cast<std::chrono::milliseconds>(
								std::chrono::system_clock::now().time_since_epoch()).count();

							{
								if (timeNow - lastExportTime > 3000)
								{
									lastExportTime = timeNow;
									std::cout << "Exporting tile {" << std::to_string(currentTile->GetPosition().y) << ", " << std::to_string(currentTile->GetPosition().y) << "}, priority: " << std::to_string(priority) << std::endl;
									exporter.Export(m_Film);
								}
							}
						}
					}
				});
			}

			numSamplesLeft -= numSamplesThisRun;
			std::cout << "Samples remaining: " << std::to_string(numSamplesLeft) << std::endl;
		}
	}


	exporter.Export(m_Film);

	system((".\\" + filename + ".png").c_str());
}

