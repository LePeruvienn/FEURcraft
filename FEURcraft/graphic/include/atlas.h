#ifndef ATLAS_H
#define ATLAS_H

#include "image.h"
#include "texture_coord.h"

#include <stdbool.h>

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

	bool is_empty;
};

Atlas* atlas_create(unsigned int width, unsigned int height,
                    unsigned int channels);

void atlas_free(Atlas* atlas);

bool atlas_add_image(Atlas* atlas, Image* img, TextureCoord* uv_out);

void atlas_write_image(Atlas* atlas, const char* file_path);

#endif // ATLAS_H
