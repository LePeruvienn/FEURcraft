#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H

#include "glad/glad.h"

typedef enum ShaderType ShaderType;

enum ShaderType
{
	SHADER_TYPE_UNKNOWN = -1,

	SHADER_TYPE_VERT,
	SHADER_TYPE_FRAG,

	SHADER_TYPE_COUNT
};

GLenum shader_type_to_gl_type(ShaderType type);

const char* shader_type_get_name(ShaderType type);

#endif // SHADER_TYPE_H
