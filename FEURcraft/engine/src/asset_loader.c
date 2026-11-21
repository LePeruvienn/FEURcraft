#include "asset_loader.h"
#include "assets.h"

#include "image.h"
#include "image_array.h"

#include "shader.h"
#include "shader_program.h"

#include "error_checker.h"
#include "ptr_helper.h"
#include "c_str_helper.h"

#include "file_helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static bool is_line_readable(char* buffer, size_t len)
{
	CHECK_IS_NULL_RET(buffer, 
		"Cannot check if line is readable of a NULL buffer", false);

	for (size_t i = 0; i < len; ++i)
	{
		char c = buffer[i];

		if (c == '#')
			return false;

		if (c != ' ' && c != '\r' && c != '\n' && c != '\t')
			return true;
	}

	return false;
}

static size_t asset_read_line(FILE* fd, char** buffer)
{
	size_t len = 0;

	do
	{
		if (getline(buffer, &len , fd) == -1)
		{
			return 0;
		}

	} while(is_line_readable(*buffer, len) == false);

	*buffer[len - 1] = '\0';

	return len;
}

static FILE* asset_open_fd(const char* file_path)
{
	CHECK_IS_NULL_RET(file_path,
		"Cannot load an asset that have a NULL file path.", NULL);

	FILE* fd = fopen(file_path, "r");

	if (fd == NULL)
	{
		LOG_ERROR("Failed to load ImageArray asset : %s", file_path);
		return NULL;
	}

	return fd;
}

ImageArray* asset_load_image_array(const char* file_path)
{
	CHECK_IS_NULL_RET(file_path,
		"Cannot load an ImageArray from an empty file path.", NULL);

	FILE* fd = asset_open_fd(file_path);

	CHECK_IS_NULL_RET(fd, "Failed to open file", NULL);

	ImageArray* img_array = NULL;

	const size_t file_path_len = strlen(file_path);

	char* dir_path = file_create_directory_path(file_path, file_path_len + 1);

	CHECK_IS_NULL_RET(dir_path, "Failed to create directory path", NULL);

	char* line_buffer = NULL;

	bool sucess = true;

	while(asset_read_line(fd, &line_buffer) != 0)
	{
		if (line_buffer == NULL)
		{
			LOG_ERROR("Failed to read line correctly");
			sucess = false;
			break;
		}

		c_str_trim(line_buffer);

		if(c_str_is_empty(line_buffer))
		{
			continue;
		}

		// LOG("Image : %s", line_buffer);

		char* absolute_path = file_create_path_from_dir(dir_path, line_buffer);

		// LOG("absolute_path: \"%s\"", absolute_path);

		Image* img = assets_get_image(absolute_path);

		if (img == NULL)
		{
			LOG_ERROR("Failed to get image \"%s\" from assets.", absolute_path);
			free(absolute_path);
			sucess = false;
			continue;
		}

		free(absolute_path);

		if (image_is_loaded(img) == false)
		{
			image_load(img);
		}

		if (image_is_loaded(img) == false)
		{
			LOG_ERROR("Failed to load Image \"%s\"", img->file_path->c_str);
			sucess = false;
			continue;
		}

		if (img_array == NULL)
		{
			img_array = image_array_create(img->width, img->height, img->channels);

			if (img_array == NULL)
			{
				LOG_ERROR("Failed to create ImageArray");
				sucess = false;
				break;
			}
		}

		if (image_array_add_image(img_array, img) == -1)
		{
			LOG_ERROR("Failed to add image %s to ImageArray",
				img->file_path->c_str);
			sucess = false;
		}
	}

	FREE_PTR_NOT_NULL(line_buffer, free);
	FREE_PTR_NOT_NULL(dir_path, free);

	if (sucess == false)
	{
		FREE_PTR_NOT_NULL(img_array, image_array_free);
	}

	return img_array;
}

ShaderProgram* asset_load_shader_program(const char* file_path)
{
	CHECK_IS_NULL_RET(file_path, "Cannot load an Shader from an empty file path.", NULL);

	FILE* fd = asset_open_fd(file_path);

	CHECK_IS_NULL_RET(fd, "Failed to open file", NULL);

	ShaderProgram* program = NULL;

	const size_t file_path_len = strlen(file_path);

	char* dir_path = file_create_directory_path(file_path, file_path_len + 1);

	CHECK_IS_NULL_RET(dir_path, "Failed to create directory path", NULL);

	char* line_buffer = NULL;

	while(asset_read_line(fd, &line_buffer) != 0)
	{
		if (line_buffer == NULL)
		{
			LOG_ERROR("Failed to read line correctly");
			break;
		}

		c_str_trim(line_buffer);

		if(c_str_is_empty(line_buffer))
		{
			continue;
		}

		// LOG("Shader : %s", line_buffer);

		char* absolute_path = file_create_path_from_dir(dir_path, line_buffer);

		// LOG("absolute_path: \"%s\"", absolute_path);

		Shader* shader = assets_get_shader(absolute_path);

		if (shader == NULL)
		{
			LOG_ERROR("Failed to get shader \"%s\"", absolute_path);
			free(absolute_path);
			continue;
		}

		free(absolute_path);

		if (shader->status != SHADER_STATUS_COMPILED)
		{
			shader_compile(shader);
		}

		if (shader->status != SHADER_STATUS_COMPILED)
		{
			LOG_ERROR("Failed to compile Shader : \"%s\"", shader->file_path->c_str);
			continue;
		}

		if (program == NULL)
		{
			program = shader_program_create();

			if (program == NULL)
			{
				LOG_ERROR("Failed to create ShaderProgram");
				break;
			}
		}

		if (shader_program_attach(program, shader) == false)
		{
			LOG_ERROR("Failed to attach shader \"%s\"to program.",
				shader->file_path->c_str);
		}
	}

	FREE_PTR_NOT_NULL(line_buffer, free);
	FREE_PTR_NOT_NULL(dir_path, free);

	if (program == NULL)
		return NULL;

	bool sucess = shader_program_link(program);

	if (sucess == false)
	{
		FREE_PTR_NOT_NULL(program, shader_program_free);
	}

	return program;
}

