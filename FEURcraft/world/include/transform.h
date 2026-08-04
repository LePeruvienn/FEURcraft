#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec3.h"
#include "mat4.h"

typedef struct Transform Transform;

struct Transform
{
	Vec3 pos;
	Vec3 scale;

	Vec3 forward;
	Vec3 up;
};

void transform_translate(Transform* transform, Vec3 translate);

void transform_rotate(Transform* transform, Vec3 rotate);

void transform_scale(Transform* transformn, Vec3 scale);

Mat4 transform_compute_model(Transform* transform);

#endif // TRANSFORM_H
