#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

typedef struct Image Image;

struct Image
{
	char* filepath;
	
	unsigned char* data;

	unsigned int channels;
	unsigned int width;
	unsigned int height;
};

Image* image_create(char* filepath);

void image_load(Image* img);
void image_unload(Image* img);

bool image_is_loaded(Image* img);

void image_free(Image* img);

#endif // IMAGE_H
