#include "texture_array.h"
#include "image_array.h"

#include "error_checker.h"
#include "logger.h"

TextureArray* texture_array_create(unsigned char* data,
                                   unsigned int width,
                                   unsigned int height,
                                   unsigned int channels,
                                   unsigned int layer_count)
{
	CHECK_COND_RET(channels == 4,
		"Texture Array only support RBGA (4 channels) images.", NULL);

	GLuint id = 0;
	glGenTextures(1, &id);

	CHECK_COND_RET(id != 0, "Failed to genrate GPU texture.", NULL);

	TextureArray* tex_array = malloc(sizeof(struct TextureArray));

	CHECK_IS_NULL_RET(tex_array, "TextureArray malloc failed.", NULL);

	tex_array->id = id;
	tex_array->width = width;
	tex_array->height = height;
	tex_array->layer_count = layer_count;

	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_array->id);

	// http://gaarlicbread.com/post/gl_2d_array
	glTexImage3D(GL_TEXTURE_2D_ARRAY,
		 0,                // mipmap level
		 GL_RGBA8,         // gpu texel format
		 width,            // width
		 height,           // height
		 layer_count,      // depth
		 0,                // border
		 GL_RGBA,          // cpu pixel format
		 GL_UNSIGNED_BYTE, // cpu pixel coord type
		 data);            // pixel data

	// texture param (optional ?)
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	return tex_array;
}

TextureArray* texture_array_create_from_img_array(ImageArray* img_array)
{
	CHECK_IS_NULL_RET(img_array, "Cannot create TextureArray from NULL ImageArray", NULL);
	CHECK_COND_RET(img_array->img_count > 0, "ImageArray contains 0 images.", NULL);

	return texture_array_create(img_array->data,
	                            img_array->width,
	                            img_array->height,
	                            img_array->channels,
	                            img_array->img_count);
}

void texture_array_free(TextureArray* tex_array)
{
	CHECK_IS_NULL_RET(tex_array, "Cannot free a NULL TextureArray", );

	if (tex_array->id != 0)
	{
		glDeleteTextures(1, &tex_array->id);
	}
	else
	{
		LOG_WARNING("Freed a TextureArray wich the ID was 0.");
	}

	free(tex_array);
}

void texture_array_bind(TextureArray* tex_array, unsigned int unit)
{
	CHECK_IS_NULL_RET(tex_array, "Cannot bind a NULL TextureArray", );

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_array->id);
}

void texture_array_unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

