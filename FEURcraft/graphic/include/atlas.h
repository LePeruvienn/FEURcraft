#ifndef ATLAS_H
#define ATLAS_H

/**
 * \file atlas.h
 * \brief Atlas pour stocker plusieurs images sur la même images.
 *
 * Atlas représente les données CPU d'un texture atlas,
 * elle permet d'ajouter des images de tailles différents sur la même image.
 * On peut ensuite récupérer les UVs de ces images facilement.
 */

#include "image.h"
#include "texture_coord.h"

#include <stdbool.h>

#define ATLAS_MAX_IMAGE_AMOUNT 32

typedef struct Atlas Atlas;

struct Atlas
{
	unsigned int width;
	unsigned int height;
	unsigned int channels;

	unsigned int cursor_x;
	unsigned int cursor_y;
	unsigned int row_height;

	unsigned char* data;

	unsigned int images_amount;
	TextureCoords images_coords[ATLAS_MAX_IMAGE_AMOUNT];
};

Atlas* atlas_create(unsigned int width, unsigned int height,
                    unsigned int channels);

void atlas_free(Atlas* atlas);

bool atlas_add_image(Atlas* atlas, Image* img, TextureCoords* uv_out);

bool atlas_get_image_coords(Atlas* atlas, unsigned int index, TextureCoords* uv_out);

void atlas_write_image(Atlas* atlas, const char* file_path);

#endif // ATLAS_H
