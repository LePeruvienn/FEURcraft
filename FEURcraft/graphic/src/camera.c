#include "camera.h"
#include "vec3.h"
#include "mat4.h"

#include "error_checker.h"

#include <math.h>

#define M_PI 3.14159265358979323846

void camera_init(Camera* c, Vec3 pos, Vec3 target,
                 float fov, float near, float far,
                 unsigned int width, unsigned int height)
{
	CHECK_IS_NULL_RET(c, "Cannot init a null camera", );

	c->pos = pos;
	c->target = target;

	c->fov = fov;

	c->aspect = (float) width / (float) height;

	c->near = near;
	c->far = far;

	float ddx = target.x - pos.x;
	float ddy = target.y - pos.y;
	float ddz = target.z - pos.z;

	c->yaw = atan2f(ddz, ddx);
	c->pitch = atan2f(ddy, sqrtf(ddx*ddx + ddz*ddz));
}

void camera_init_default(Camera* c, Window* w)
{
	// les deux valeurs ne doivent pas être égale,
	// sinon la matrice vue peut être remplie de zéro !
	static Vec3 camera_default_pos = VEC3(0.f, 0.f, 5.f);
	static Vec3 camera_default_target = VEC3(0.f, 0.f, 0.f);

	static float camera_default_fov = 45.f;
	static float camera_default_near = 0.1f;
	static float camera_default_far = 100.f;

	camera_init(c,
		camera_default_pos,
		camera_default_target,
		camera_default_fov,
		camera_default_near,
		camera_default_far,
		w->width,
		w->height
	);
}

void camera_translate(Camera* c, float dx, float dy, float dz)
{
	CHECK_IS_NULL_RET(c, "Cannot translate a null camera", );
	
	Vec3 forward_raw = vec3_sub(c->target, c->pos);
	Vec3 forward = vec3_norm(forward_raw);

	Vec3 world_up = VEC3(0.f, 1.f, 0.f);
	Vec3 right_raw = vec3_cross(forward, world_up);
	Vec3 right = vec3_norm(right_raw);

	Vec3 up = vec3_cross(right, forward);

	vec3_mult_scal_in(&right, dx);
	vec3_mult_scal_in(&up, dy);
	vec3_mult_scal_in(&forward, dz);

	vec3_add_in(&c->pos, right);
	vec3_add_in(&c->pos, up);
	vec3_add_in(&c->pos, forward);

	vec3_add_in(&c->target, right);
	vec3_add_in(&c->target, up);
	vec3_add_in(&c->target, forward);
}

void camera_rotate(Camera* c, float dyaw, float dpitch)
{
	CHECK_IS_NULL_RET(c, "Cannot rotate a null camera", );

	c->yaw   += dyaw;
	c->pitch += dpitch;

	// clamp le pitch pour éviter le flip
	if (c->pitch >  M_PI / 2.0f - 0.001f)
		c->pitch =  M_PI / 2.0f - 0.001f;

	if (c->pitch < -M_PI / 2.0f + 0.001f)
		c->pitch = -M_PI / 2.0f + 0.001f;

	float cp = cosf(c->pitch);
	float dx = cp * cosf(c->yaw);
	float dz = cp * sinf(c->yaw);
	float dy = sinf(c->pitch);

	c->target.x = c->pos.x + dx;
	c->target.y = c->pos.y + dy;
	c->target.z = c->pos.z + dz;
}

void camera_update_aspect(Camera* c, unsigned int width, unsigned int height)
{
	CHECK_IS_NULL_RET(c, "Cannot set aspect of a null camera", );

	c->aspect = (float) width / (float) height;
}

Mat4 camera_compute_view(Camera* c)
{
	CHECK_IS_NULL_RET(c, "Cannot compute view of a null camera", MAT4_IDENTITY);

	Vec3 forward = vec3_sub(c->target, c->pos);
	vec3_norm_in(&forward);

	Vec3 world_up = VEC3(0.f, 1.f, 0.f);
	Vec3 right = vec3_cross(forward, world_up);
	vec3_norm_in(&right);

	Vec3 up = vec3_cross(right, forward);

	float tx = -vec3_dot(right,   c->pos);
	float ty = -vec3_dot(up,      c->pos);
	float tz = -vec3_dot(forward, c->pos);

	// Déjà bien en column order ! Pas besoin de transpose 
	return MAT4(right.x,  up.x,  -forward.x,  0.f,
	            right.y,  up.y,  -forward.y,  0.f,
	            right.z,  up.z,  -forward.z,  0.f,
	                 tx,    ty,         -tz,  1.f);
}

Mat4 camera_compute_proj(Camera* c)
{
	CHECK_IS_NULL_RET(c, "Cannot compute project of a null camera", MAT4_IDENTITY);

	float fov_rad = c->fov * (M_PI / 180.0f);
	float f  = 1.0f / tanf(fov_rad * 0.5f);
	float nf = 1.0f / (c->near - c->far);

	// Déjà bien en column order ! Pas besoin de transpose 
	return MAT4(f / c->aspect,  0.f,  0.f,                            0.f,
	            0.f,            f,    0.f,                            0.f,
	            0.f,            0.f,  (c->far + c->near) * nf,       -1.f,
	            0.f,            0.f,  (2.f * c->far * c->near) * nf,  0.f
	);
}

