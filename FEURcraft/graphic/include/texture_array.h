#ifndef TEXTURE_ARRAY_H
#define TEXTURE_ARRAY_H

#include "image_array.h"

#include "glad/glad.h"

typedef struct TextureArray TextureArray;

struct TextureArray
{
	GLuint id;

	unsigned int width;
	unsigned int height;
	unsigned int layer_count;
};

TextureArray* texture_array_create(unsigned char* data,
                                   unsigned int width,
                                   unsigned int height,
                                   unsigned int channels,
                                   unsigned int layer_count);

TextureArray* texture_array_create_from_img_array(ImageArray* img_array);

void texture_array_free(TextureArray* tex_array);

void texture_array_bind(TextureArray* tex_array, unsigned int unit);

void texture_array_unbind();

#endif // TEXTURE_ARRAY_H
