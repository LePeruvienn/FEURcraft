#include "shader.h"
#include "shader_type.h"

#include "read_file.h"

#include "ptr_helper.h"

#include "glad/glad.h"

#include <stdbool.h>

void shader_init(Shader* shader, const char* file_path, ShaderType type)
{
	CHECK_IS_NULL_RET(shader, "Tried init a NULL shader.", );

	GLenum gl_shader_type = shader_type_to_gl_type(type);

	shader->id = glCreateShader(gl_shader_type);
	shader->type = type;
	shader->file_path = file_path;
	shader->status = SHADER_STATUS_NOT_VALID;
}

void shader_deinit(Shader* shader)
{
	if(shader->status != SHADER_STATUS_VALID)
		return;

	glDeleteShader(shader->id);

	shader->id = 0;
	shader->status = SHADER_STATUS_NOT_INIT;
	shader->type = SHADER_TYPE_UNKNOWN;
}

void shader_compile(Shader* shader)
{
	CHECK_IS_NULL_RET(shader, "Tried to compile a NULL shader.", );

	if (shader->status == SHADER_STATUS_NOT_INIT)
	{
		LOG_ERROR("Cannot compille an un initialized shader.");
		return;
	}

	const char* source = read_file_txt(shader->file_path);

	CHECK_IS_NULL_RET(source, "Failed to read shader source", );

	glShaderSource(shader->id, 1, &source, NULL);
	glCompileShader(shader->id);

	shader_update_status(shader);
}

void shader_init_and_compile(Shader* shader, const char* file_path, ShaderType type)
{
	CHECK_IS_NULL_RET(shader, "Tried to init and compile of a NULL shader.", );
	shader_init(shader, file_path, type);
	shader_compile(shader);
}

static int get_shader_status(GLuint id, GLenum pname, const char* name)
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

void shader_update_status(Shader* shader)
{
	CHECK_IS_NULL_RET(shader, "Tried to check status of a NULL shader.", );

	int status = get_shader_status(shader->id, GL_COMPILE_STATUS, shader->file_path);

	if (status == 0)
	{
		shader->status = SHADER_STATUS_VALID;
	}
	else
	{
		shader->status = SHADER_STATUS_LINK_FAILED;
	}
}

