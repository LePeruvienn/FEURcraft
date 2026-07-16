#ifndef SHADER_H
#define SHADER_H

#include "shader_type.h"

#include "glad/glad.h"

#define SHADER_DEFAULT \
	(Shader) { .id = 0, .file_path = NULL, \
	.type = SHADER_TYPE_UNKNOWN, .status = SHADER_STATUS_NOT_INIT } \

typedef enum ShaderStatus ShaderStatus;

enum ShaderStatus
{
	SHADER_STATUS_VALID = 0,

	SHADER_STATUS_NOT_INIT,

	SHADER_STATUS_NOT_VALID,
	SHADER_STATUS_COMPILE_FAILED,
	SHADER_STATUS_LINK_FAILED
};

typedef struct Shader Shader;

struct Shader
{
	GLuint id;

	const char* file_path;

	ShaderType type;
	ShaderStatus status;
};

void shader_init(Shader* shader, const char* file_path, ShaderType type);

void shader_deinit(Shader* shader);

void shader_compile(Shader* shader);

void shader_init_and_compile(Shader* shader, const char* file_path, ShaderType type);

void shader_update_status(Shader* shader);

#endif // SHADER_H
