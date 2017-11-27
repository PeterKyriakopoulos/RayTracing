#include "precomp.h"
#include "Material.h"


Material::Material(int type)
{
	switch (type)
	{
		case 0: this->diffuse = true;
				this->reflect = false;
				this->transp = false;
				break;
		case 1: this->diffuse = false;
				this->reflect = true;
				this->transp = false;
				break;
		case 2: this->diffuse = false;
				this->reflect = false;
				this->transp = true;
				break;
	}
}


Material::~Material()
{
}
