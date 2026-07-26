#ifndef IMAGE_ARRAY_H
#define IMAGE_ARRAY_H

#include "image.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct ImageArray ImageArray;

struct ImageArray
{
	// theses are the param for a single image !
	unsigned int width;
	unsigned int height;
	unsigned int channels;

	unsigned int img_count;
	unsigned int img_max_count;

	unsigned char* data;
};

ImageArray* image_array_create(unsigned int width, unsigned int height,
                               unsigned int channels);

void image_array_free(ImageArray* tex_array);

int image_array_add_image(ImageArray* tex_array, Image* img);

#endif // IMAGE_ARRAY_H
