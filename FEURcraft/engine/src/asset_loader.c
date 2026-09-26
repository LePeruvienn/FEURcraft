#include "asset_loader.h"
#include "assets.h"

#include "image.h"
#include "image_array.h"

#include "error_checker.h"
#include "ptr_helper.h"
#include "c_str_helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

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
	FILE* fd = asset_open_fd(file_path);

	CHECK_IS_NULL_RET(fd, "Failed to open file", NULL);

	ImageArray* img_array = NULL;

	char* buffer = NULL;

	while(asset_read_line(fd, &buffer) != 0)
	{
		CHECK_IS_NULL_RET(buffer, "Failed to read line correctly", NULL);

		c_str_trim(buffer);

		LOG("Image : %s", buffer);

		Image* img = assets_get_image(buffer);

		CHECK_IS_NULL_RET(img, "Failed to get Asset Image", NULL);

		if (image_is_loaded(img) == false)
			image_load(img);

		CHECK_COND_RET(image_is_loaded(img), "Failed to load Image", NULL);

		if (img_array == NULL)
		{
			img_array = image_array_create(img->width, img->height, img->channels);
			CHECK_IS_NULL_RET(img_array, "Failed to create ImageArray", NULL);
		}

		if (image_array_add_image(img_array, img) == -1)
		{
			LOG_ERROR("Failed to add image %s to ImageArray",
				img->file_path->c_str);
		}
	}

	FREE_PTR_NOT_NULL(buffer, free);

	return img_array;
}

