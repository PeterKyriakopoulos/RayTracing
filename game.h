#pragma once
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"
#include "Camera.h"
#include "Plane.h"
#include "Object.h"
#include "Light.h"
#include <vector>

namespace Tmpl8 {

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	//vec3 trace(Ray r, vector<Sphere> &sphere, vector<Plane> &planes, int &depth);
	//bool trace(Ray r, vector<Object> &objects, float &tnear, Object *&hitObject);
	//vec3 castRay(Ray r, vector<Object> &objects);
	//void render(vector<Sphere> &sphere, vector<Plane> &planes, Camera *cam);
	void render(vector<Object*> objects, vector<Light*> lights, Camera *cam);
private:
	Surface* screen;
};

}; // namespace Tmpl8