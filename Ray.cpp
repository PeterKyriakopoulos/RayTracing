#include "precomp.h"
#include "Ray.h"


Ray::Ray(vec3 direction, vec3 origin)
{
	this->dir = direction;
	this->orig = origin;
}


Ray::~Ray()
{
}

//Find intersection with object and return color
vec3 trace(Ray r, vector<Sphere> spheres, int &depth)
{
	//Nearest obj hit
	float tnear = std::numeric_limits<float>::infinity();
	Sphere *sphere = NULL;

	//Loop over all spheres
	for (int i = 0; i < spheres.size(); i++)
	{
		float t0 = std::numeric_limits<float>::infinity();
		float t1 = std::numeric_limits<float>::infinity();

		//If ray hits, store the closest hit sphere
		if (spheres[i].intersect(r, &t0, &t1));
		{
			if (t0 < 0)
				t0 = t1;
			if (t0 < tnear)
			{
				tnear = t0;
				sphere = spheres[i];
			}
		}

		//If ray miss, return black color
		if (!sphere)
			return vec3(0);

		//The final pixel color
		vec3 pixCol = 0;
		//Point of collision and normal
		vec3 posHit = r.orig + r.dir * tnear;
		vec3 normHit = posHit - sphere->pos;

		//Normalize the normal vector
		normHit.normalize();

		//If the material is reflective or transparent continue tracing
		if (sphere->mat->reflect && depth < 3)
		{
			//Compute the new reflected direction in which we check
			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
			Ray *tempRay = new Ray(reflDir, posHit+normHit);
			depth++;
			
			vec3 reflect = trace(*tempRay, spheres, depth);

			return reflect * pixCol;
		}
		else if (sphere->mat->transp && depth < 3)
		{
			//Material density and resulting angle
			float dens = 1/1.3;
			float cosAng = -normHit.dot(r.dir);
			float snell = dens*dens * (1 - cosAng*cosAng);

			//Compute the new refracted direction in which we check
			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
			refrDir.normalize();
			Ray *tempRay = new Ray(refrDir, posHit - normHit);
			depth++;

			vec3 refract = trace(*tempRay, spheres, depth);
		
			return refract * pixCol;
		}

		//If material is diffuse return its color and stop tracing
		return pixCol + sphere->color;
	}
}

