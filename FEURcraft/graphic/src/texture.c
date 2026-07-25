#include "texture.h"
#include "image.h"

#include "logger.h"
#include "gl_debug.h"
#include "error_checker.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stdbool.h>

Texture* create_texture(unsigned char* data,
                        unsigned int width, unsigned int height)
{
	Texture* t = malloc(sizeof(struct Texture));

	CHECK_IS_NULL_RET(t, "Failed to malloc Texture.", NULL);

	t->id = 0;
	t->type = GL_TEXTURE_2D;
	t->width = 0;
	t->height = 0;

	GL_CALL(glGenTextures(1, &t->id));
	GL_CALL(glBindTexture(t->type, t->id));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	t->width = width;
	t->height = height;

	GL_CALL(glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		t->width,
		t->height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	));

	LOG_INFO("Loaded an image of %dx%d pixels.", t->width, t->height);

	glBindTexture(t->type, 0);

	return t;
}

Texture* create_texture_from_image(Image* img)
{
	CHECK_COND_RET(img->channels == 4,
		"Image that are not RGBA (4 channels) are not supported.", NULL);

	return create_texture(img->data, img->width, img->height);
}

Texture* create_texture_from_file(const char* filepath)
{
	Image* img = image_create(filepath);

	CHECK_IS_NULL_RET(img, "Failed to load texture file.", NULL)

	Texture* texture = create_texture_from_image(img);

	image_free(img);

	return texture;
}

Texture* create_texture_from_atlas(Atlas* atlas)
{
	CHECK_IS_NULL_RET(atlas,
		"Cannot create texture from a NULL Atlas", NULL);

	CHECK_COND_RET(atlas->channels == 4,
			"Atlas that are not RGBA (4 channels) are not supported", NULL);

	return create_texture(atlas->data, atlas->width, atlas->height);
}

void free_texture(Texture* t)
{
	CHECK_IS_NULL_RET(t, "Cannot free a NULL texture.", );

	glDeleteTextures(1, &t->id);
	free(t);
}

void bind_texture(Texture* t, unsigned int unit)
{
	CHECK_IS_NULL_RET(t, "Cannot bind a NULL texture.", );

	glActiveTexture(GL_TEXTURE0 + unit);
	GL_CALL(glBindTexture(t->type, t->id));

	glActiveTexture(GL_TEXTURE0);
}

void unbind_texture(Texture* t, unsigned int unit)
{
	CHECK_IS_NULL_RET(t, "Cannot unbind a NULL texture.", );

	glActiveTexture(GL_TEXTURE0 + unit);
	GL_CALL(glBindTexture(t->type, 0));

	glActiveTexture(GL_TEXTURE0);
}

