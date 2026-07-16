#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"
#include "shader_type.h"

#include "glad/glad.h"
#include <stddef.h>

typedef struct ShaderProgram ShaderProgram;

struct ShaderProgram
{
	GLuint id;
	ShaderStatus status;

	Shader shaders[SHADER_TYPE_COUNT];
};

void shader_program_init(ShaderProgram* program);

void shader_program_deinit(ShaderProgram* program);

void shader_program_add_shader(ShaderProgram* program, Shader shader);

void shader_program_link_shaders(ShaderProgram* program);

void shader_program_update_status(ShaderProgram* program);

#endif // SHADER_PROGRAM_H
