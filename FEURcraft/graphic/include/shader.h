#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

typedef enum ShaderType ShaderType;
typedef enum ShaderStatus ShaderStatus;

enum ShaderType
{
	SHADER_TYPE_VERT,
	SHADER_TYPE_FRAG,

	SHADER_TYPE_COUNT
};

enum ShaderStatus
{
	SHADER_STATUS_COMPILED,
	SHADER_STATUS_NOT_COMPILED,
	SHADER_STATUS_COMPILE_FAILED
};

typedef struct Shader Shader;

struct Shader
{
	GLuint id;

	const char* file_path;

	ShaderType type;
	ShaderStatus status;
};

Shader* shader_create(const char* file_path, ShaderType type);

void shader_free(Shader* shader);

void shader_compile(Shader* shader);

GLenum shader_type_to_gl_type(ShaderType type);

const char* shader_type_get_name(ShaderType type);

#endif // SHADER_H
