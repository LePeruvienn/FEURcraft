#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"

#include "glad/glad.h"
#include <stddef.h>

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

#endif // SHADER_PROGRAM_H
