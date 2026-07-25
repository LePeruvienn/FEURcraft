#include "image.h"

#include "ptr_helper.h"
#include "error_checker.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>

Image* image_create(char* filepath)
{
	Image* img = malloc(sizeof(struct Image));

	CHECK_IS_NULL_RET(img, "Failed to malloc Image", NULL);

	img->filepath = filepath;
	img->data = NULL;
	img->channels = 0;
	img->width = 0;
	img->height = 0;

	return img;
}

void image_load(Image* img)
{
	CHECK_IS_NULL_RET(img, "Cannot load an image that is NULL.", );
	CHECK_IS_NULL_RET(img->filepath, "Cannot load an image with NULL filepath", );

	CHECK_COND_RET(image_is_loaded(img) == false,
		"Cannot load an image that is already loaded", );

	// cause opengl origin is at bottom left
	stbi_set_flip_vertically_on_load(1);

	int width = 0;
	int height = 0;
	int channels = 0;

	img->data = NULL;

	// If force 4 channels to have RBGA
	img->data = stbi_load(img->filepath, &width, &height, &channels, STBI_rgb_alpha);

	CHECK_IS_NULL_RET(img->data, "Failed to load Image from file", );

	img->width = (unsigned int) width;
	img->height = (unsigned int) height;
	img->channels = (unsigned int) channels;
}

void image_unload(Image* img)
{
	CHECK_IS_NULL_RET(img, "Cannot unload a NULL Image.", );

	CHECK_COND_RET(image_is_loaded(img) == true,
		"Cannot unload an image that is not loaded", );

	stbi_image_free(img->data);

	img->data = NULL;
	img->channels = 0;
	img->width = 0;
	img->height = 0;
}

bool image_is_loaded(Image* img)
{
	return img->data != NULL;
}

void image_free(Image* img)
{
	CHECK_IS_NULL_RET(img, "Cannot free a NULL Image.", );

	image_unload(img);
	free(img);
}
