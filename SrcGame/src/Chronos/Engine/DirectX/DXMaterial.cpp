#include "DXMaterial.h"

#include <vector>

namespace DX
{

	Material::Material()
	{
		vTextures.reserve(MAX_MATERIAL_TEXTURES);
	}

	Material::~Material()
	{
	}

}