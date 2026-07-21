#include "shader_program.h"
#include "shader.h"

#include "glad/glad.h"

#include "gl_debug.h"
#include "logger.h"
#include "error_checker.h"

static int get_program_status(GLuint program, GLenum pname)
{
	int  success;
	char infoLog[512];

	glGetProgramiv(program, pname, &success);

	if(!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		LOG_ERROR("Program status failed, %s", infoLog);
	}

	return success;
}

ShaderProgram* shader_program_create()
{
	GLuint id = glCreateProgram();

	if (id == 0)
	{
		LOG_ERROR("Failed to create OpenGL program.");
		return NULL;
	}

	ShaderProgram* program = malloc(sizeof(ShaderProgram));

	if (program == NULL)
	{
		LOG_ERROR("malloc of ShaderProgram failed.");
		glDeleteProgram(id);
		return NULL;
	}

	program->id = id;
	program->status = PROGRAM_STATUS_NOT_LINKED;

	for (unsigned int i = 0; i < SHADER_TYPE_COUNT; ++i)
	{
		program->shaders[i] = NULL;
	}
	
	return program;
}

void shader_program_free(ShaderProgram* program)
{
	CHECK_IS_NULL_RET(program, "Tried to free a null ShaderProgram.", );

	shader_program_detach_all(program);

	if (program->id != 0)
	{
		GL_CALL(glDeleteProgram(program->id));
	}
	else
	{
		LOG_WARNING("Freed a ShaderProgrom with an id of 0");
	}

	free(program);
}

void shader_program_attach(ShaderProgram* program, Shader* shader)
{
	CHECK_IS_NULL_RET(program, "Tried to attach a Shader to a NULL ShaderProgram.", );
	CHECK_IS_NULL_RET(shader, "Tried to attach a NULL Shader to a ShaderProgram.", );

	if (shader->type == SHADER_TYPE_COUNT)
	{
		LOG_ERROR("Shader type is COUNT this should never happen wtf.");
		return;
	}

	if (shader->status != SHADER_STATUS_COMPILED)
	{
		LOG_ERROR("You must compile your shader first before attaching it");
		return;
	}

	Shader* current_shader = program->shaders[shader->type];

	if (current_shader != NULL)
	{
		const char* shader_type_name = shader_type_get_name(shader->type);
		LOG_ERROR("Add shader of type %s already exist in this program.", shader_type_name);
		return;
	}

	GL_CALL(glAttachShader(program->id, shader->id));

	program->shaders[shader->type] = shader;
}

void shader_program_detach(ShaderProgram* program, Shader* shader)
{
	CHECK_IS_NULL_RET(program, "Tried to detach a Shader to a NULL ShaderProgram.", );
	CHECK_IS_NULL_RET(shader, "Tried to detach a NULL Shader to a ShaderProgram.", );

	if (shader->type == SHADER_TYPE_COUNT)
	{
		LOG_ERROR("Shader type is COUNT this should never happen wtf.");
		return;
	}

	Shader* current_shader = program->shaders[shader->type];

	if (current_shader != shader)
	{
		LOG_ERROR("Could not find the shader you are trying to remove.");
		return;
	}

	GL_CALL(glDetachShader(program->id, shader->id));

	program->shaders[shader->type] = NULL;
}

void shader_program_detach_all(ShaderProgram* program)
{
	CHECK_IS_NULL_RET(program, "Tried to detach all Shaders of a NULL ShaderProgram.", );

	for (unsigned int i = 0; i < SHADER_TYPE_COUNT; ++i)
	{
		if(program->shaders[i] == NULL)
			continue;

		GL_CALL(glDetachShader(program->id, program->shaders[i]->id));
		program->shaders[i] = NULL;
	}
}

void shader_program_link(ShaderProgram* program)
{
	CHECK_IS_NULL_RET(program, "Tried to link a NULL ShaderProgram.", );

	if(program->shaders[SHADER_TYPE_VERT] == NULL ||
	   program->shaders[SHADER_TYPE_FRAG] == NULL )
	{
		LOG_ERROR("Cannot link a program without a Vertex and a Fragment Shader.");
		return;
	}

	if (program->status == PROGRAM_STATUS_LINKED)
	{
		LOG_WARNING("Program was already linked, relink program ...");
	}

	GL_CALL(glLinkProgram(program->id));

	int success = get_program_status(program->id, GL_LINK_STATUS);
	program->status = (success == 0) ?
		PROGRAM_STATUS_LINK_FAILED : PROGRAM_STATUS_LINKED;
}

void shader_program_use(ShaderProgram* program)
{
	CHECK_IS_NULL_RET(program, "Canno use a NULL shader", );

	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GL_CALL(glUseProgram(program->id));
}

void shader_program_unbind()
{
	GL_CALL(glUseProgram(0));
}

void shader_program_set_bool(ShaderProgram* program, const char* uniform, bool value)
{
	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GLint location = glGetUniformLocation(program->id, uniform);

	CHECK_COND_RET(location > 0, "uniform location less or equal than 0", );

	GL_CALL(glUniform1i(location, value));
}

void shader_program_set_float(ShaderProgram* program, const char* uniform, float value)
{
	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GLint location = glGetUniformLocation(program->id, uniform);

	CHECK_COND_RET(location >= 0, "uniform location less than 0", );

	GL_CALL(glUniform1f(location, value));
}

void shader_program_set_vec2(ShaderProgram* program, const char* uniform, Vec2 vec)
{
	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GLint location = glGetUniformLocation(program->id, uniform);

	CHECK_COND_RET(location >= 0, "uniform location less than 0", );

	GL_CALL(glUniform2f(location, vec.x, vec.y));
}

void shader_program_set_vec3(ShaderProgram* program, const char* uniform, Vec3 vec)
{
	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GLint location = glGetUniformLocation(program->id, uniform);

	CHECK_COND_RET(location >= 0, "uniform location less than 0", );

	GL_CALL(glUniform3f(location, vec.x, vec.y, vec.z));
}

void shader_program_set_vec4(ShaderProgram* program, const char* uniform, Vec4 vec)
{
	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GLint location = glGetUniformLocation(program->id, uniform);

	CHECK_COND_RET(location >= 0, "uniform location less than 0", );

	GL_CALL(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
}

void shader_program_set_mat4(ShaderProgram* program, const char* uniform, Mat4 mat)
{
	CHECK_COND_RET(program->status == PROGRAM_STATUS_LINKED,
	               "Cannot set a uniform of a not linked shader", );

	GLint location = glGetUniformLocation(program->id, uniform);

	CHECK_COND_RET(location >= 0, "uniform location less than 0", );

	glUniformMatrix4fv(location, 1, GL_FALSE, mat.data);
}

