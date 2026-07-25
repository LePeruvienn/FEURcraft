#include "image.h"

#include "error_checker.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdlib.h>
#include <string.h>

Image* image_create(const char* filepath)
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

Image* image_create_and_load(const char* filepath)
{
	Image* img = image_create(filepath);

	CHECK_IS_NULL_RET(img, "Failed to create image", NULL);

	image_load(img);

	if (image_is_loaded(img) == false)
	{
		LOG_ERROR("Failed to load Image. Returing NULL");
		image_free(img);
		return NULL;
	}

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
	CHECK_IS_NULL_RET(img, "Cannot check a NULL Image.", false);

	return img->data != NULL;
}

void image_free(Image* img)
{
	CHECK_IS_NULL_RET(img, "Cannot free a NULL Image.", );

	image_unload(img);
	free(img);
}

void image_write(Image* img, const char* file_path)
{
	image_write_from_data(file_path,
	                       img->data,
	                       img->width,
	                       img->height,
	                       img->channels);
}

void image_write_from_data(const char* file_path,
                           unsigned char* data,
                           unsigned int width,
                           unsigned int height,
                           unsigned int channels)
{
	stbi_flip_vertically_on_write(1);

	stbi_write_png(
		file_path,
		width,
		height,
		channels,
		data,
		width * channels
	);
}

bool image_are_equal(Image* img1, Image* img2)
{
	CHECK_COND_RET(image_is_loaded(img1) && image_is_loaded(img2),
		"Cannot compare image if they are not laoded", false);

	bool same_width = img1->width == img2->width;
	bool same_height = img1->height == img2->height;
	bool same_channels = img1->channels == img2->channels;

	if (!same_width || !same_height || !same_channels)
	{
		return false;
	}

	size_t img_size = img1->width * img1->height * img1->channels;

	return memcmp(img1->data, img2->data, img_size) == 0;
}

