#ifndef MATERIAL_DATA_H
#define MATERIAL_DATA_H

#include <aiMaterial.h>

struct aiMaterial;
struct cMaterialData
{
	std::string macPath;
	aiMaterial* mpMaterial;
};

#endif;

