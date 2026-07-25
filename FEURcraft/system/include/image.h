#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

typedef struct Image Image;

struct Image
{
	const char* filepath;
	
	unsigned char* data;

	unsigned int channels;
	unsigned int width;
	unsigned int height;
};

Image* image_create(const char* filepath);

Image* image_create_and_load(const char* filepath);

void image_load(Image* img);
void image_unload(Image* img);

bool image_is_loaded(Image* img);

void image_free(Image* img);

void image_write(Image* img, const char* file_path);

void image_write_from_data(const char* file_path,
                           unsigned char* data,
                           unsigned int width,
                           unsigned int height,
                           unsigned int channels);

bool image_are_equal(Image* img1, Image* img2);

#endif // IMAGE_H
