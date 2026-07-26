#include "atlas.h"

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

	atlas->images_amount = 0;

	memset(atlas->images_coords, 0,
		sizeof(TextureCoords) *  ATLAS_MAX_IMAGE_AMOUNT);

	return atlas;
}

void atlas_free(Atlas* atlas)
{
	CHECK_IS_NULL_RET(atlas, "Cannot free a NULL Atlas.", );

	free(atlas->data);
	free(atlas);
}

bool atlas_add_image(Atlas* atlas, Image* img, TextureCoords* uv_out)
{
	CHECK_IS_NULL_RET(atlas, "Cannot Image to a NULL Atlas.", false);
	CHECK_IS_NULL_RET(img, "Cannot add a NULL Image to Atlas.", false);

	CHECK_COND_RET(atlas->images_amount < ATLAS_MAX_IMAGE_AMOUNT,
		"Atlas max image amount reached, cannot add image.", false);

	CHECK_COND_RET(image_is_loaded(img),
		"Cannot add to atlas an unloaded image", false);

	CHECK_COND_RET(atlas->channels == img->channels,
		"Cannot add an Image to Atlas that have not the same channels", false);

	CHECK_COND_RET(atlas->width >= img->width && atlas->height >= atlas->height,
		"Cannot add an Image that is begire than the entire Atlas", false);

	bool not_enough_width = (atlas->cursor_x + img->width > atlas->width) || atlas->row_height < img->height;
	bool not_enough_height = atlas->row_height + atlas->cursor_y + img->height > atlas->height;

	bool not_enough_space = not_enough_width && not_enough_height;

	bool is_empty = atlas->images_amount == 0;

	// Si c'est vide, alors on peut ajouter l'image.
	// mais si ce n'est pas vide, et qu'il n'y a pllus de place,
	// alors on ne peut pas ajouter l'image à l'atlas
	CHECK_COND_RET(is_empty || !not_enough_space,
		"There is not enough space in Atlas to add this Image", false);

	// Si l'image n'est pas vide et qu'il faut déplacer le curseur en Y
	// Et bas on le fait
	if (!is_empty && not_enough_width)
	{
		atlas->cursor_x = 0;
		atlas->cursor_y += atlas->row_height;
		atlas->row_height = img->height;
	}

	int channels = atlas->channels;
	unsigned int cursor_x = atlas->cursor_x;
	unsigned int cursor_y = atlas->cursor_y;

	for (unsigned int img_y = 0; img_y < img->height; img_y++)
	{
		unsigned int atlas_offset =
			((cursor_y + img_y) * atlas->width * channels) + (cursor_x * channels);

		unsigned int img_offset   = img_y * img->width * channels;

		memcpy(atlas->data + atlas_offset, img->data + img_offset, img->width * channels);
	}

	atlas->cursor_x += img->width;

	if (is_empty)
	{
		atlas->row_height = img->height;
	}

	uv_out->u.x = (float) cursor_x / (float) atlas->width;
	uv_out->u.y = (float) cursor_y / (float) atlas->height;

	uv_out->v.x = (float) (cursor_x + img->width)  / (float) atlas->width;
	uv_out->v.y = (float) (cursor_y + img->height) / (float) atlas->height;

	atlas->images_coords[atlas->images_amount++] = *uv_out;

	return true;
}

bool atlas_get_image_coords(Atlas* atlas, unsigned int index, TextureCoords* uv_out)
{
	CHECK_IS_NULL_RET(atlas, "Cannot Image to a NULL Atlas.", false);

	CHECK_COND_RET(index < atlas->images_amount,
		"Atlas image index is not valid", false);
	
	*uv_out = atlas->images_coords[index];

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
