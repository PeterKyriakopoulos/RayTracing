#pragma once
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"
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
	vec3 trace(Ray r, vector<Sphere> sphere, int &depth);
private:
	Surface* screen;
};

}; // namespace Tmpl8