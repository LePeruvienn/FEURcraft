#include "image_array.h"

#include "error_checker.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define IMAGE_ARRAY_DEFAULT_IMG_MAX_COUNT 16

ImageArray* image_array_create(unsigned int width, unsigned int height,
                               unsigned int channels)
{
	ImageArray* img_array = malloc(sizeof(struct ImageArray));

	CHECK_IS_NULL_RET(img_array, "ImageArray malloc failed.", NULL);

	img_array->width = width;
	img_array->height = height;
	img_array->channels = channels;

	img_array->img_count = 0;
	img_array->img_max_count = IMAGE_ARRAY_DEFAULT_IMG_MAX_COUNT;

	size_t data_size =
		width * height * channels * sizeof(unsigned char) * img_array->img_max_count;

	img_array->data = malloc(data_size);

	return img_array;
}

void image_array_free(ImageArray* img_array)
{
	CHECK_IS_NULL_RET(img_array, "Cannot free a NULL ImageArray", );

	free(img_array->data);
	free(img_array);
}

int image_array_add_image(ImageArray* img_array, Image* img)
{
	CHECK_IS_NULL_RET(img_array, "Cannnot add Image to a NULL ImageArray", -1);
	CHECK_IS_NULL_RET(img, "Cannot add a NULL Image to ImageArray", -1);

	CHECK_COND_RET(image_is_loaded(img), "Cannot add an unloaded Image to ImageArray.", -1);

	bool image_fit_size = (img_array->width    == img->width   ) &&
	                      (img_array->height   == img->height  ) &&
	                      (img_array->channels == img->channels);

	CHECK_COND_RET(image_fit_size,
			"Tried to add an image that dont fit the ImageArra size.", -1);

	size_t img_size = img_array->width * img_array->height * img_array->channels;

	if (img_array->img_count == img_array->img_max_count)
	{
		unsigned int new_img_max_count = img_array->img_max_count * 2;

		size_t new_data_size = sizeof(unsigned char) * img_size * new_img_max_count;

		unsigned char* new_data = realloc(img_array->data, new_data_size);

		CHECK_IS_NULL_RET(new_data, "Failed to realloc ImageArray.", -1);

		img_array->img_max_count = new_img_max_count;
		img_array->data = new_data;
	}
	
	unsigned char* dest = img_array->data + (img_array->img_count * img_size);

	memcpy(dest, img->data, img_size);

	return img_array->img_count++;
}

