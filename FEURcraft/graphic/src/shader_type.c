#include "shader_type.h"

#include "logger.h"

#include "glad/glad.h"

GLenum shader_type_to_GL(ShaderType type)
{
	GLenum gl_type = 0;

	switch(type)
	{
		case SHADER_TYPE_VERT:
			gl_type = GL_VERTEX_SHADER;
			break;

		case SHADER_TYPE_FRAG:
			gl_type = GL_FRAGMENT_SHADER;
			break;

		case SHADER_TYPE_UNKNOWN:
			LOG_ERROR("Shader type is unkown.");
			break;

		case SHADER_TYPE_COUNT:
			LOG_ERROR("Shader type is count ???");
			break;
	}

	return gl_type;
}


const char* shader_type_get_name(ShaderType type)
{
	const char* str = "Unkown";

	switch(type)
	{
		case SHADER_TYPE_VERT:
			str = "Vertex";
			break;

		case SHADER_TYPE_FRAG:
			str = "Fragment";
			break;

		case SHADER_TYPE_UNKNOWN:
			LOG_ERROR("Shader type is unkown.");
			break;

		case SHADER_TYPE_COUNT:
			LOG_ERROR("Shader type is count ???");
			break;
	}

	return str;
}
