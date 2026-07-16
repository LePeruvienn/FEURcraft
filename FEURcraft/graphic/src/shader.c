#include "shader.h"

#include "read_file.h"

#include "ptr_helper.h"

#include "glad/glad.h"

#include <stdbool.h>
#include <stdlib.h>

static int shader_get_status(GLuint id, GLenum pname, const char* name)
{
	int  success;
	char infoLog[512];

	glGetShaderiv(id, pname, &success);

	if(!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);

		if (name != NULL)
			LOG_ERROR("shader \"%s\" status failed :\n %s", name, infoLog);
		else
			LOG_ERROR("shader status failed :\n %s", infoLog);
	}

	return success;
}

Shader* shader_create(const char* file_path, ShaderType type)
{
	GLenum gl_shader_type = shader_type_to_gl_type(type);

	if(gl_shader_type == 0)
	{
		LOG_ERROR("Invalid shader type.");
		return NULL;
	}

	GLuint id = glCreateShader(gl_shader_type);

	if (id == 0)
	{
		LOG_ERROR("Failed to create OpenGL shader. Returning NULL");
		return NULL;
	}

	Shader* shader = malloc(sizeof(Shader));

	if (shader == NULL)
	{
		LOG_ERROR("malloc Shader failed.");
		glDeleteShader(id);
		return NULL;
	}

	shader->id = id;
	shader->type = type;
	shader->file_path = file_path;
	shader->status = SHADER_STATUS_NOT_COMPILED;

	return shader;
}

void shader_free(Shader* shader)
{
	CHECK_IS_NULL_RET(shader, "Tried to free a NULL Shader", );

	if (shader->id != 0)
	{
		glDeleteShader(shader->id);
	}
	else
	{
		LOG_WARNING("Freed a shader that shader id is 0.");
	}

	free(shader);
}

void shader_compile(Shader* shader)
{
	CHECK_IS_NULL_RET(shader, "Tried to compile a NULL shader.", );

	if(shader->id == 0)
	{
		LOG_ERROR("Trying to compile invalid shader.");
		return;
	}

	if (shader->status == SHADER_STATUS_COMPILED)
	{
		LOG_WARNING("Shader already compiled, recompiling shader.");
	}

	const char* source = read_file_txt(shader->file_path);

	CHECK_IS_NULL_RET(source, "Failed to read shader source", );

	glShaderSource(shader->id, 1, &source, NULL);
	glCompileShader(shader->id);

	free((void*) source);

	int success = shader_get_status(shader->id, GL_COMPILE_STATUS, shader->file_path);

	shader->status = (success != 0) ?
		SHADER_STATUS_COMPILED : SHADER_STATUS_COMPILE_FAILED;
}

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

		case SHADER_TYPE_COUNT:
			LOG_ERROR("Shader type is count ???");
			break;
	}

	return str;
}
