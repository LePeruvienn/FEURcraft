#include "atlas.h"

#include "logger.h"
#include "error_checker.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

Atlas* atlas_create(unsigned int width, unsigned int height,
                    unsigned int channels)
{
	Atlas* atlas = malloc(sizeof(Atlas));

	CHECK_IS_NULL_RET(atlas, "Failed to malloc Atlas.", NULL);

	atlas->width = width;
	atlas->height = height;
	atlas->channels = channels;

	size_t data_size = sizeof(unsigned char) * width * height * channels;
	
	atlas->data = malloc(data_size);

	memset(atlas->data, 0, data_size);

	atlas->cursor_x = 0;
	atlas->cursor_y = 0;

	atlas->row_height = 0;

	atlas->is_empty = true;

	return atlas;
}

void atlas_free(Atlas* atlas)
{
	CHECK_IS_NULL_RET(atlas, "Cannot free a NULL Atlas.", );

	free(atlas->data);
	free(atlas);
}

bool atlas_add_image(Atlas* atlas, Image* img, TextureCoord* uv_out)
{
	CHECK_IS_NULL_RET(atlas, "Cannot Image to a NULL Atlas.", false);
	CHECK_IS_NULL_RET(img, "Cannot add a NULL Image to Atlas.", false);

	bool is_image_loaded = image_is_loaded(img);

	bool not_same_channels = atlas->channels != img->channels;

	bool not_enough_width = (atlas->cursor_x + img->width > atlas->width) || atlas->row_height < img->height;
	bool not_enough_height = atlas->row_height + atlas->cursor_y + img->height > atlas->height;

	bool not_enough_space = not_enough_width && not_enough_height;

	if (!atlas->is_empty && (!is_image_loaded || not_same_channels || not_enough_space))
	{
		LOG_ERROR("Cannot add image to atlas :\n"
		" [ Atlas Status ]\n"
		" - atlas_is_empty : %b\n"
		" - image_is_loaded : %b\n"
		" - not_same_channels : %b\n"
		" - not_enough_space : %b",
		atlas->is_empty, is_image_loaded, not_same_channels, not_enough_space);

		return false;
	}

	if (!atlas->is_empty && not_enough_width)
	{
		atlas->cursor_x = 0;
		atlas->cursor_y += atlas->row_height;
		atlas->row_height = img->height;
	}

	int channels = atlas->channels;
	unsigned int cursor_x = atlas->cursor_x;
	unsigned int cursor_y = atlas->cursor_y;

	uv_out->u.x = (float) cursor_x / (float) atlas->width;
	uv_out->u.y = (float) cursor_y / (float) atlas->height;

	uv_out->v.x = (float) (cursor_x + img->width)  / (float) atlas->width;
	uv_out->v.y = (float) (cursor_y + img->height) / (float) atlas->height;

	for (unsigned int img_y = 0; img_y < img->height; img_y++)
	{
		unsigned int atlas_offset =
			((cursor_y + img_y) * atlas->width * channels) + (cursor_x * channels);

		unsigned int img_offset   = img_y * img->width * channels;

		memcpy(atlas->data + atlas_offset, img->data + img_offset, img->width * channels);
	}

	atlas->cursor_x += img->width;

	if (atlas->is_empty)
	{
		atlas->row_height = img->height;
		atlas->is_empty = false;
	}

	return true;
}

void atlas_write_image(Atlas* atlas, const char* file_path)
{
	CHECK_IS_NULL_RET(atlas, "Cannot write image of a NULL Atlas.", );

	CHECK_IS_NULL_RET(file_path,
		"Cannot write Atlas image to a NULL file path", );

	image_write_from_data(file_path,
	                      atlas->data,
	                      atlas->width,
	                      atlas->height,
	                      atlas->channels);
}
