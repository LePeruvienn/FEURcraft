#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#include "glad/glad.h"

#include <stddef.h>
#include <stdbool.h>

typedef enum ProgramStatus ProgramStatus;

enum ProgramStatus
{
	PROGRAM_STATUS_LINKED,
	PROGRAM_STATUS_NOT_LINKED,
	PROGRAM_STATUS_LINK_FAILED
};

typedef struct ShaderProgram ShaderProgram;

struct ShaderProgram
{
	GLuint id;
	ProgramStatus status;

	Shader* shaders[SHADER_TYPE_COUNT];
};

ShaderProgram* shader_program_create();

void shader_program_free(ShaderProgram* program);

void shader_program_attach(ShaderProgram* program, Shader* shader);
void shader_program_detach(ShaderProgram* program, Shader* shader);

void shader_program_detach_all(ShaderProgram* program);

void shader_program_link(ShaderProgram* program);

void shader_program_use(ShaderProgram* program);

void shader_program_unbind();

void shader_program_set_bool(ShaderProgram* program, const char* uniform, bool value);
void shader_program_set_float(ShaderProgram* program, const char* uniform, float value);

void shader_program_set_vec2(ShaderProgram* program, const char* uniform, Vec2 vec);
void shader_program_set_vec3(ShaderProgram* program, const char* uniform, Vec3 vec);
void shader_program_set_vec4(ShaderProgram* program, const char* uniform, Vec4 vec);

void shader_program_set_mat4(ShaderProgram* program, const char* uniform, Mat4 mat);

#endif // SHADER_PROGRAM_H
