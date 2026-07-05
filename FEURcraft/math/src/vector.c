#include "vector.h"
#include "logger.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define CHECK_VEC_NULL(v, msg, ret) \
	do {                            \
		if (v == NULL)              \
		{                           \
			LOG_ERROR(msg);         \
			return ret;             \
		}                           \
	} while (0)

#define CHECK_VEC_NULL2(u, v, msg, ret) \
	do {                                \
		if (u == NULL || v == NULL)     \
		{                               \
			LOG_ERROR(msg);             \
			return ret;                 \
		}                               \
	} while (0)

#define CHECK_VEC_SAME_SIZE(u, v, msg, ret) \
	do {                                    \
		if (u->size != v->size)             \
		{                                   \
			LOG_ERROR(msg);                 \
			return ret;                     \
		}                                   \
	} while (0)

struct vec
{
	float* buf;
	unsigned int size;
};

vec create_vec(unsigned int size)
{
	vec v = malloc(sizeof(struct vec));
	float* buf = malloc(sizeof(float) * size);

	v->size = size;
	v->buf = buf;

	for (unsigned int i = 0; i < size; i++)
	{
		v->buf[i] = 0.0;
	}

	return v;
}

vec create_vec2(float x, float y)
{
	vec v = create_vec(2);
	vec_set_xy(v, x, y);
	return v;
}

vec create_vec3(float x, float y, float z)
{
	vec v = create_vec(3);
	vec_set_xyz(v, x, y, z);
	return v;
}

vec create_vec4(float x, float y, float z, float w)
{
	vec v = create_vec(4);
	vec_set_xyzw(v, x, y, z, w);
	return v;
}

vec vec_copy(vec v)
{
	CHECK_VEC_NULL(v, "Trying to copy a NULL vector ! Returned NULL.", NULL);

	vec u = create_vec(v->size);

	vec_copy_inplace(u, v);
	
	return u;
}

void vec_copy_inplace(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to copy NULL vector.", );
	CHECK_VEC_SAME_SIZE(u, v, "Tried to copy values from a vector that have not the same size", );

	for (unsigned int i = 0; i < u->size; i++)
	{
		u->buf[i] = v->buf[i];
	}
}

void free_vec(vec v)
{
	CHECK_VEC_NULL(v, "Trying to free a NULL vector.", );

	free(v->buf);
	free(v);
}

bool vec_same_size(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to same size a NULL vector ! Returned false.", false);
	return (u->size == v->size);
}

bool vec_equal(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to equal a NULL vector ! Returned false.", false);

	if(!vec_same_size(u, v))
	{
		return false;
	}

	for (unsigned int i = 0; i < u->size; i++)
	{
		if (u->buf[i] != v->buf[i])
		{
			return false;
		}
	}

	return true;
}

unsigned int vec_get_size(vec v)
{
	CHECK_VEC_NULL(v, "Trying to get size of a NULL vector ! Returned 0.", 0);
	return v->size;
}

float vec_get_value(vec v, unsigned int index)
{
	CHECK_VEC_NULL(v, "Trying to get value of a NULL vector ! Returned 0.0.", 0.0);

	// ERROR !! BAD VALUE
	if (index >= v->size)
	{
		LOG_ERROR("Index >= vector size ! Returned 0.0.");
		return 0.0;
	}

	return v->buf[index];
}

float vec_get_x(vec v)
{
	return vec_get_value(v, 0);
}

float vec_get_y(vec v)
{
	return vec_get_value(v, 1);
}

float vec_get_z(vec v)
{
	return vec_get_value(v, 2);
}

float vec_get_w(vec v)
{
	return vec_get_value(v, 3);
}

void vec_set_value(vec v, unsigned int index, float value)
{
	CHECK_VEC_NULL(v, "Trying to set value of a NULL vector.", );

	// ERROR !! BAD VALUE
	if (index >= v->size)
	{
		LOG_ERROR("Index >= vector size ! Returned 0.0.");
		return;
	}

	v->buf[index] = value;
}

void vec_set_values(vec v, float* buf, unsigned int size)
{
	CHECK_VEC_NULL(v, "Trying to set values of a NULL vector.", );

	// ERROR !! BAD VALUE
	if (size > v->size)
	{
		LOG_ERROR("Size > vector size !");
		return;
	}

	for (unsigned int i = 0; i < size; i++)
	{
		v->buf[i] = buf[i];
	}
}

void vec_set_x(vec v, float value)
{
	vec_set_value(v, 0, value);
}

void vec_set_y(vec v, float value)
{
	vec_set_value(v, 1, value);
}

void vec_set_z(vec v, float value)
{
	vec_set_value(v, 2, value);
}

void vec_set_w(vec v, float value)
{
	vec_set_value(v, 3, value);
}

void vec_set_xy(vec v, float x, float y)
{
	CHECK_VEC_NULL(v, "Trying to set values of a NULL vector.", );

	// ERROR !! BAD VALUE
	if (v->size < 2)
	{
		LOG_ERROR("vector size < 2");
		return;
	}

	v->buf[0] = x;
	v->buf[1] = y;
}

void vec_set_xyz(vec v, float x, float y, float z)
{
	CHECK_VEC_NULL(v, "Trying to set values of a NULL vector.", );

	// ERROR !! BAD VALUE
	if (v->size < 3)
	{
		LOG_ERROR("vector size < 3");
		return;
	}

	v->buf[0] = x;
	v->buf[1] = y;
	v->buf[2] = z;
}

void vec_set_xyzw(vec v, float x, float y, float z, float w)
{
	CHECK_VEC_NULL(v, "Trying to set values of a NULL vector.", );

	// ERROR !! BAD VALUE
	if (v->size < 4)
	{
		LOG_ERROR("vector size < 4");
		return;
	}

	v->buf[0] = x;
	v->buf[1] = y;
	v->buf[2] = z;
	v->buf[3] = w;
}

float vec_length(vec v)
{
	CHECK_VEC_NULL(v, "Trying to get length of a NULL vector ! Returned 0.0.", 0.0);

	float sum = 0.0;

	for (unsigned int i = 0; i < v->size; i++)
	{
		sum += v->buf[i] * v->buf[i];
	}

	return sqrtf(sum);
}

float vec_fast_length(vec v)
{
	CHECK_VEC_NULL(v, "Trying to get length of a NULL vector ! Returned 0.0.", 0.0);

	float sum = 0.0;

	for (unsigned int i = 0; i < v->size; i++)
	{
		sum += v->buf[i] * v->buf[i];
	}

	return sum;
}

float vec_dist(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to get distance of a NULL vector ! Returned 0.0.", 0.0);
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match ! Returned 0.0.", 0.0);

	float sum = 0.f;

	for (unsigned int i = 0; i < u->size; i++)
	{
		float diff = u->buf[i] - v->buf[i];
		sum += diff * diff;
	}

	return sqrtf(sum);
}

float vec_fast_dist(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to get distance of a NULL vector ! Returned 0.0.", 0.0);
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match ! Returned 0.0.", 0.0);

	float sum = 0.f;

	for (unsigned int i = 0; i < u->size; i++)
	{
		float diff = u->buf[i] - v->buf[i];
		sum += diff * diff;
	}

	return sum;
}

float vec_dot(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to dot a NULL vector ! Returned 0.0.", 0.0);
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match ! Returned 0.0.", 0.0);

	float sum = 0.0;

	for (unsigned int i = 0; i < u->size; i++)
	{
		sum += u->buf[i] * v->buf[i];
	}

	return sum;
}

vec vec_add(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to add a NULL vector ! Returned NULL.", NULL);
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match ! Returned NULL.", NULL);

	vec w = create_vec(u->size);

	for (unsigned int i = 0; i < u->size; i++)
	{
		w->buf[i] = u->buf[i] + v->buf[i];
	}

	return w;
}

vec vec_substract(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to substract a NULL vector ! Returned NULL.", NULL);
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match ! Returned NULL.", NULL);

	vec w = create_vec(u->size);

	for (unsigned int i = 0; i < u->size; i++)
	{
		w->buf[i] = u->buf[i] - v->buf[i];
	}

	return w;
}

vec vec_scale(vec u, float lambda)
{
	CHECK_VEC_NULL(u, "Trying to scale a NULL vector ! Returned NULL.", NULL);

	vec v = create_vec(u->size);

	for (unsigned int i = 0; i < u->size; i++)
	{
		v->buf[i] = u->buf[i] * lambda;
	}

	return v;
}

vec vec_normalize(vec v)
{
	CHECK_VEC_NULL(v, "Trying to normalize a NULL vector ! Returned NULL.", NULL);

	float l = vec_length(v);

	if (l == 0.0)
	{
		return vec_copy(v);
	}
	return vec_scale(v, 1 / l);
}

void vec_add_inplace(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to add a NULL vector" , );
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match", );

	for (unsigned int i = 0; i < u->size; i++)
	{
		u->buf[i] += v->buf[i];
	}
}

void vec_substract_inplace(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to substract a NULL vector" , );
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes doesnt match", );

	for (unsigned int i = 0; i < u->size; i++)
	{
		u->buf[i] -= v->buf[i];
	}
}

void vec_scale_inplace(vec v, float lambda)
{
	CHECK_VEC_NULL(v, "Trying to scale a NULL vector" , );

	for (unsigned int i = 0; i < v->size; i++)
	{
		v->buf[i] *= lambda;
	}
}

void vec_normalize_inplace(vec v)
{
	CHECK_VEC_NULL(v, "Trying to normalize a NULL vector" , );

	float l = vec_length(v);

	if (l == 0.0)
	{
		return;
	}

	vec_scale_inplace(v, 1 / l);
}


vec vec3_cross(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to cross product a null vector ! Returned NULL.", NULL);

	if (u->size != 3 || v->size != 3)
	{
		LOG_ERROR("Trying to cross product with a vector that is not of size 3 ! Returned NULL");
		return NULL;
	}

	float ux = vec_get_x(u);
	float uy = vec_get_y(u);
	float uz = vec_get_z(u);

	float vx = vec_get_x(v);
	float vy = vec_get_y(v);
	float vz = vec_get_z(v);

	return create_vec3(
		(uy * vz) - (uz * vy),
		(uz * vx) - (ux * vz),
		(ux * vy) - (uy * vx)
	);
}

void vec3_cross_inplace(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Trying to cross product a null vector.", );

	if (u->size != 3 || v->size != 3)
	{
		LOG_ERROR("Trying to cross product with a vector that is not of size 3.");
		return;
	}

	float ux = vec_get_x(u);
	float uy = vec_get_y(u);
	float uz = vec_get_z(u);

	float vx = vec_get_x(v);
	float vy = vec_get_y(v);
	float vz = vec_get_z(v);

	vec_set_xyz(
		u,
		(uy * vz) - (uz * vy),
		(uz * vx) - (ux * vz),
		(ux * vy) - (uy * vx)
	);
}

float vec_angle(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Angle calculation with NULL vector! Returned 0.0.", 0.0);
	CHECK_VEC_SAME_SIZE(u, v, "Vectors sizes don't match! Returned 0.0.", 0.0);

	float dot = vec_dot(u, v);
	float len_product = vec_length(u) * vec_length(v);

	if (len_product == 0.0)
	{
		LOG_ERROR("Angle calculation with a zero-length vector! Returned 0.0.");
		return 0.0;
	}

	float cos_theta = dot / len_product;

	if (cos_theta > 1.0)
	{
		cos_theta = 1.0;
	}
	else if (cos_theta < -1.0)
	{
		cos_theta = -1.0;
	}

	return acosf(cos_theta);
}

float vec2_angle_oriented(vec u, vec v)
{
	CHECK_VEC_NULL2(u, v, "Angle calculation with NULL vector! Returned 0.0.", 0.0);

	if (u->size != 2 || v->size != 2)
	{
		LOG_ERROR("vec2_angle_oriented requires vectors of size 2! Returned 0.0.");
		return 0.0;
	}

	// atan2(det(u,v), dot(u,v))
	float dot = (u->buf[0] * v->buf[0]) + (u->buf[1] * v->buf[1]);
	float det = (u->buf[0] * v->buf[1]) - (u->buf[1] * v->buf[0]);

	return atan2f(det, dot);
}

float vec3_angle_oriented(vec u, vec v, vec axis)
{
	CHECK_VEC_NULL2(u, v, "Angle calculation with NULL vector! Returned 0.0.", 0.0);
	CHECK_VEC_NULL(axis, "Reference axis is NULL! Returned 0.0.", 0.0);

	if (u->size != 3 || v->size != 3 || axis->size != 3)
	{
		LOG_ERROR("vec3_angle_oriented requires vectors of size 3! Returned 0.0.");
		return 0.0;
	}

	vec cross = vec3_cross(u, v);

	float angle = vec_angle(u, v);
	float direction = vec_dot(cross, axis);

	free_vec(cross);

	return (direction < 0.0) ? -angle : angle;
}

vec vec2_rotate(vec v, float alpha)
{
	CHECK_VEC_NULL(v, "Rotating NULL vector! Returned NULL.", NULL);

	if (v->size != 2)
	{
		LOG_ERROR("vec2_rotate requires a vector of size 2! Returned NULL.");
		return NULL;
	}

	vec u = create_vec(2);

	float c = cosf(alpha);
	float s = sinf(alpha);

	u->buf[0] = v->buf[0] * c - v->buf[1] * s;
	u->buf[1] = v->buf[0] * s + v->buf[1] * c;

	return u;
}

void vec2_rotate_inplace(vec v, float alpha)
{
	CHECK_VEC_NULL(v, "Rotating NULL vector!", );
	if (v->size != 2)
	{
		LOG_ERROR("vec2_rotate_inplace requires a vector of size 2!");
		return;
	}

	float x = v->buf[0];
	float y = v->buf[1];
	float c = cosf(alpha);
	float s = sinf(alpha);

	v->buf[0] = x * c - y * s;
	v->buf[1] = x * s + y * c;
}

vec vec3_rotate(vec v, vec axis, float alpha)
{
	CHECK_VEC_NULL2(v, axis, "Rotation with NULL vector! Returned NULL.", NULL);

	if (v->size != 3 || axis->size != 3)
	{
		LOG_ERROR("vec3_rotate requires vectors of size 3! Returned NULL.");
		return NULL;
	}

	// Formule de Rodrigues : v_rot = v*cos(a) + (axis x v)*sin(a) + axis*(axis.v)*(1-cos(a))
	float c = cosf(alpha);
	float s = sinf(alpha);
	float dot = vec_dot(axis, v);

	vec cross = vec3_cross(axis, v);

	vec u = create_vec(3);

	for (int i = 0; i < 3; i++)
	{
		u->buf[i] = v->buf[i] * c + cross->buf[i] * s +  axis->buf[i] * dot * (1.0 - c);
	}

	free_vec(cross);

	return u;
}

void vec3_rotate_inplace(vec v, vec axis, float alpha)
{
	vec rotated = vec3_rotate(v, axis, alpha);

	if (rotated)
	{
		vec_copy_inplace(v, rotated);
		free_vec(rotated);
	}
}

float vec_deg_to_rad(float deg)
{
	return deg * (M_PI / 180.0);
}

float vec_rad_to_deg(float rad)
{
	return rad * (180.0 / M_PI);
}
