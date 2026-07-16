#include "shader_program.h"
#include "shader.h"
#include "shader_type.h"

#include "logger.h"

void shader_program_init(ShaderProgram* program)
{
	program->id = 0;
	program->status = SHADER_STATUS_VALID;

	for (unsigned int i = 0; i < SHADER_TYPE_COUNT; ++i)
	{
		program->shaders[i] = SHADER_DEFAULT;
	}
}

void shader_program_deinit(ShaderProgram* program)
{
	program->id = 0;
	program->status = SHADER_STATUS_VALID;

	for (unsigned int i = 0; i < SHADER_TYPE_COUNT; ++i)
	{
		shader_deinit(&program->shaders[i]);
	}
}

void shader_program_add_shader(ShaderProgram* program, Shader shader)
{
	if (shader.type == SHADER_TYPE_UNKNOWN)
	{
		LOG_ERROR("Cannot add a shader of type Unknown.");
		return;
	}

	if (program->status == SHADER_STATUS_VALID)
	{
		LOG_WARNING("Adding a shader to a shader program that is already compiled.");
	}

	Shader* target_shader = &program->shaders[shader.type];

	if (target_shader->status != SHADER_STATUS_NOT_INIT)
	{
		const char* shader_type_name = shader_type_get_name(shader.type);

		LOG_WARNING(
			"Shader program have already a %s shader, replacing it.",
			shader_type_name);

		shader_deinit(target_shader);
	}

	*target_shader = shader;
}

void shader_program_link_shaders(ShaderProgram* program)
{
	Shader* shaders = program->shaders;

	for (unsigned int i = 0; i < SHADER_TYPE_COUNT; ++i)
	{
		if(shaders[i].status == SHADER_STATUS_NOT_INIT)
			continue;

		if(shaders[i].status != SHADER_STATUS_VALID)
			shader_compile(&shaders[i]);

		if(shaders[i].status != SHADER_STATUS_VALID)
		{
			LOG_ERROR("Failed to compile shader %d : %s",
				i, shaders[i].file_path);

			continue;
		}

		glAttachShader(shaders[i].id, program->id);
	}

	glLinkProgram(program->id);

	shader_program_update_status(program);
}

static int get_shader_program_status(GLuint id, GLenum pname)
{
	int  success;
	char infoLog[512];

	glGetProgramiv(id, pname, &success);

	if(!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		LOG_ERROR("ShaderProgram %d status failed, %s", id, infoLog);
	}

	return success;
}

void shader_program_update_status(ShaderProgram* program)
{
	int success = get_shader_program_status(program->id, GL_LINK_STATUS);

	if (success)
	{
		program->status = SHADER_STATUS_VALID;
	}
	else
	{
		program->status = SHADER_STATUS_NOT_VALID;
	}
}
