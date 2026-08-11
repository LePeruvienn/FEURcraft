#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "mesh.h"
#include "material.h"

typedef struct RenderObject RenderObject;

struct RenderObject
{
	Mesh* mesh;
	Material* material;
};

#endif // RENDER_OBJECT_H
