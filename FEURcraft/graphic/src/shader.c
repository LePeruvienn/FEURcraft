#include "shader.h"
#include "debug.h"

#include "logger.h"
#include "read_file.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CHECK_SHADER_IS_NULL(s, msg, ret) \
	do { if (s == NULL) {                 \
		LOG_ERROR(msg); return ret;       \
	}} while(0)

#define LOG_SHADER_IS_OK(s, n)                         \
	do { if (s != NULL) LOG_INFO("[%s] : OK", n);      \
	     else           LOG_ERROR("[%s] : FAILED", n); \
	} while (0)

struct shader
{
	// ID du shader OpenGL 
	GLuint program;
};

static int get_shader_status(GLuint shader, GLenum pname, const char* shader_name)
{
	int  success;
	char infoLog[512];

	glGetShaderiv(shader, pname, &success);

	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);

		if (shader_name != NULL)
			LOG_ERROR("shader \"%s\" status failed :\n    %s", shader_name, infoLog);
		else
			LOG_ERROR("shader status failed :\n    %s", infoLog);
	}

	return success;
}

static int get_program_status(GLuint program, GLenum pname)
{
	int  success;
	char infoLog[512];

	glGetProgramiv(program, pname, &success);

	if(!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		LOG_ERROR("program status failed, %s", infoLog);
	}

	return success;
}

int compile_shader(const char* path, GLuint type, GLuint* out)
{
	GLuint shader = glCreateShader(type);

	const char* source = read_file_txt(path);

	if (source == NULL)
	{
		LOG_ERROR("Failed to read shader source file.");
		return 1;
	}

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	if (!get_shader_status(shader, GL_COMPILE_STATUS, path))
	{
		LOG_ERROR("GL_COMPILE_STATUS failed");
		return 2;
	}

	*out = shader;

	return 0;
}

int compile_shader_program(GLuint* shaders, unsigned int size, GLuint* out)
{
	GLuint shader_program = glCreateProgram();

	for (size_t i = 0; i < size; i++)
	{
		glAttachShader(shader_program, shaders[i]);
	}

	glLinkProgram(shader_program);

	if (!get_program_status(shader_program, GL_LINK_STATUS))
	{
		LOG_ERROR("GL_LINK_STATUS failed");
		return 1;
	}

	*out = shader_program;

	return 0;
}

shader create_shader(const char* vert_shader_path, const char* frag_shader_path)
{
	shader s = malloc(sizeof(struct shader));

	GLuint vert_shader;

	if (compile_shader(vert_shader_path, GL_VERTEX_SHADER, &vert_shader) != 0)
	{
		free(s);

		LOG_ERROR("Failed to compile vertex shader.");
		return NULL;
	}

	GLuint frag_shader;

	if (compile_shader(frag_shader_path, GL_FRAGMENT_SHADER, &frag_shader) != 0)
	{
		glDeleteShader(vert_shader);
		free(s);

		LOG_ERROR("Failed to compile fragment shader.");
		return NULL;
	}

	GLuint shaders[2] = {vert_shader, frag_shader};

	if (compile_shader_program(shaders, 2, &s->program) != 0)
	{
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);
		free(s);

		LOG_ERROR("Failed to compile shader program.");
		return NULL;
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return s;
}

void free_shader(shader s)
{
	if (s == NULL)
	{
		LOG_ERROR("Tried to free a NULL shader");
		return;
	}

	glDeleteProgram(s->program);
	free(s);
}

void bind_shader(shader s)
{
	if (s == NULL)
	{
		LOG_ERROR("Tried to bind a NULL shader.");
		return;
	}

	GL_CALL(glUseProgram(s->program));
}

void unbind_shader()
{
	glUseProgram(0);
}

