#pragma once
class Material
{
public:
	Material(int type);
	~Material();

	bool diffuse;
	bool reflect;
	bool transp;
};

