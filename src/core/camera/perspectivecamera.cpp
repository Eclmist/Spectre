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

const int NumSamples = 1000;
constexpr double DeltaArea = 1.0 / NumSamples;
struct hit_record;

class aabb {
public:
	aabb() {}
	aabb(const Vector3& a, const Vector3& b) { minimum = a; maximum = b; }

	Vector3 min() const { return minimum; }
	Vector3 max() const { return maximum; }

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

	Vector3 minimum;
	Vector3 maximum;
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
	sphere(Vector3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(
		const Ray& r, double t_min, double t_max, hit_record& rec) const override;
	virtual bool bounding_box(double time0, double time1, aabb& output_box) const override;

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
	Vector3 small(std::fmin(box0.min().x, box1.min().x),
		std::fmin(box0.min().y, box1.min().y),
		std::fmin(box0.min().z, box1.min().z));

	Vector3 big(std::fmax(box0.max().x, box1.max().x),
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
		Vector3 target = hit.p + hit.normal + Sampling::UniformSampleSphere();

		Spectrum attenuation;
		Ray scattered(Vector3{}, Vector3{});
		hit.lambdaIndex = lambdaIdx;

		Spectrum emitted = hit.mat_ptr->emitted();

		if (!hit.mat_ptr->scatter(ray, hit, &attenuation, scattered))
			return emitted;

		return emitted + attenuation * raytraceScene(scattered, lambdaIdx, depth - 1);
	}

	Vector3 unit_direction = ray.GetDirection().Normalized();
	auto t = 0.5 * (unit_direction.y + 1.0);
	Vector3 skyColorVec = Vector3(1.0 - t) * Vector3(1.0, 1.0, 1.0) + Vector3(t) * Vector3(0.5, 0.7, 1.0);
	RgbCoefficients skyColor(skyColorVec[0], skyColorVec[1], skyColorVec[2]);
	return ReflectantSpectrum(skyColor);
}

inline int random_int(int min, int max) {
	// Returns a random integer in [min,max].
	return Random::UniformInt(min, max);
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

		int axis = Random::UniformInt(0, 2);
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
			left = make_shared<bvh_node>(objects, start, mid, time0, time1);
			right = make_shared<bvh_node>(objects, mid, end, time0, time1);
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
	auto material_light = std::make_shared<diffuse_light>(&lightColor);

	world.add(std::make_shared<sphere>(Vector3(0, 0.2, -1), 0.5, material_glass));
	//world.add(std::make_shared<sphere>(Vector3(-0.5, 1, -0.5), 0.2, material_light));
	world.add(std::make_shared<sphere>(Vector3(0.9, -0.1, 4.5), 0.5, material_ground));
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

								Spectrum L = singleColoredRay * raytraceScene(ray, w - MinWavelength, 8);
								SampledSpectrum L2(L);
								currentTile->SplatPixel(tileSpacePos, L2.ToXyz(), DeltaArea);
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

