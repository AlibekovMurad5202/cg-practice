#version 430

#define BIG 1000000.0
#define EPSILON 0.001

/*********** DATA STRUCTURES *************/

struct Camera
{
	vec3 position;
	vec3 view;
	vec3 up;
	vec3 side;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};

struct Sphere
{
	vec3 center;
	float radius;
	vec3 color;
	int material_idx;
};

struct Triangle
{
	vec3 vert1;
	vec3 vert2;
	vec3 vert3;
	vec3 color;
	int material_idx;
};

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float specular_power;
};

struct Intersection
{
	float time;
	vec3 point;
	vec3 normal;
	vec3 color;
	int material_idx;
};

/*****************************************/

layout(std430, binding = 0) buffer SphereBuffer
{
	Sphere sphere_data[];
};

/*****************************************/

in vec3 interpolated_vertex;
out vec4 frag_color;

Material material = {.2f, .9f, 2.f, 512.f};
vec3 light_pos = vec3(-3, 3, -3);

uniform Camera camera;
uniform vec2 scale;

const int count_of_triangles = 10;
uniform Triangle triangles[count_of_triangles];

/*****************************************/

Ray GenerateRay(Camera camera)
{
	vec2 coords = interpolated_vertex.xy * normalize(scale);
	vec3 direction = camera.view + camera.side * coords.x + camera.up * coords.y;
	return Ray(camera.position, normalize(direction));
};

bool IntersectSphere(Sphere sphere, Ray ray, out float time)
{
	ray.origin -= sphere.center;
	float B = dot(ray.direction, ray.origin);
	float C = dot(ray.origin, ray.origin) - sphere.radius * sphere.radius;
	float D = B * B - C;

	if (D > 0.0)
	{	
		D = sqrt(D);

		float t1 = -B - D;
		float t2 = -B + D;

		float min_t = min(t1, t2);
		float max_t = max(t1, t2);

		if (max_t < 0)
			return false;
		if (min_t < 0)
		{
			time = max_t;
			return true;
		}
		time = min_t;
		return true;
	}
	return false;
};

bool IntersectTriangle(Triangle triangle, Ray ray, out float time)
{
	time = -1;
	vec3 edge_1 = triangle.vert3 - triangle.vert1;
	vec3 edge_2 = triangle.vert2 - triangle.vert1;
	vec3 normal = cross(edge_2, edge_1);
	float dotRayDirection = dot(normal, ray.direction);

	if (abs(dotRayDirection) < EPSILON)
		return false;

	float t = -(dot(normal, ray.origin) - dot(normal, triangle.vert1)) / dotRayDirection;

	if (t < 0) return false;

	vec3 r = ray.origin + t * ray.direction;
	vec3 edge1 = triangle.vert2 - triangle.vert1;
	vec3 edge2 = triangle.vert3 - triangle.vert2;
	vec3 edge3 = triangle.vert1 - triangle.vert3;

	if (dot(normal, cross(edge1, r - triangle.vert1)) < 0) return false;
	if (dot(normal, cross(edge2, r - triangle.vert2)) < 0) return false;
	if (dot(normal, cross(edge3, r - triangle.vert3)) < 0) return false;

	time = t;
	return true;
};

bool Intersect(Ray ray, float start, float final, inout Intersection intersect)
{
	bool result = false;
	float time = start;
	intersect.time = final;

	for (int j = 0; j < count_of_triangles; j++)
	{
		if (IntersectTriangle(triangles[j], ray, time) && (time < intersect.time))
		{
			intersect.time = time;
			intersect.point = ray.origin + ray.direction * time;
			vec3 edge1 = triangles[j].vert1 - triangles[j].vert2;
			vec3 edge2 = triangles[j].vert1 - triangles[j].vert3;
			intersect.normal = normalize(cross(edge1, edge2));
			intersect.color = triangles[j].color;
			intersect.material_idx = triangles[j].material_idx;
			result = true;
		}
	}

	for (int i = 0; i < sphere_data.length(); i++)
	{
		if (IntersectSphere(sphere_data[i], ray, time) && (time < intersect.time))
		{
			intersect.time = time;
			intersect.point = ray.origin + ray.direction * time;
			intersect.normal = normalize(intersect.point - sphere_data[i].center);
			intersect.color = sphere_data[i].color;
			intersect.material_idx = sphere_data[i].material_idx;
			result = true;
		}
	}
	
	return result;
};

float Shadow(vec3 pos_light, vec3 point)
{
	float light = 1.f;
	vec3 direction = normalize(pos_light - point);
	Ray shadow_ray = Ray(point + direction * EPSILON, direction);
	Intersection intersect;
	intersect.time = distance(pos_light, point);

	if (Intersect(shadow_ray, 0, intersect.time, intersect))
		light = 0.f;
	return light;
};

vec3 Phong(Intersection intersect, vec3 pos_light, float shadow)
{
	vec3 light = normalize(pos_light - intersect.point);
	float diffuse = max(dot(light, intersect.normal), 0.f);
	vec3 view = normalize(camera.position - intersect.point);
	vec3 reflected = reflect(-view, intersect.normal);
	float specular = pow(max(dot(reflected, light), 0.f), material.specular_power);

	return material.ambient * intersect.color + 
		shadow * (material.diffuse * diffuse * intersect.color +
		material.specular * specular * vec3(1, 1, 1));
};

vec4 RayTrace(Ray primary_ray)
{
	vec4 resultColor = vec4(0, 0, 0, 0);
	Ray ray = primary_ray;

	Intersection intersect;
	intersect.time = BIG;
	float start = 0.f;
	float final = BIG;

	if (Intersect(ray, start, final, intersect))
	{
		float shadowing = Shadow(light_pos, intersect.point);
		resultColor += vec4(Phong(intersect, light_pos, shadowing), 0);
	};
	
	return resultColor;
};

/*****************************************/

void main()
{
	Ray ray = GenerateRay(camera);
	frag_color = RayTrace(ray);
};