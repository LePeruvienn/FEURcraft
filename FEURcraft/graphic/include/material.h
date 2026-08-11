#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader_program.h"
#include "material_parameter.h"

#include "array_list.h"

typedef struct Material Material;

struct Material
{
	ShaderProgram* program;
	ArrayList* parameters;
};

Material* material_create(ShaderProgram* program);

Material* material_free(Material* material);

void material_add_param(Material* material, MaterialParameter param);

void material_use(Material* material);

void material_unbind();

#endif // MATERIAL_H
