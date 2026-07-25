#include "texture.h"

#include "logger.h"
#include "gl_debug.h"
#include "error_checker.h"

#include "glad/glad.h"

// L'import de stb_image.h fait crash le linter,
// - Pas un soucis pour le programme juste pour l'IDE.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <stdbool.h>

Texture* create_texture(const char* filepath)
{
	CHECK_IS_NULL_RET(filepath, "Texture path is NULL.", NULL);

	Texture* t = malloc(sizeof(struct Texture));

	t->id = 0;
	t->type = GL_TEXTURE_2D;
	t->width = 0;
	t->height = 0;

	GL_CALL(glGenTextures(1, &t->id));
	GL_CALL(glBindTexture(t->type, t->id));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(1);

	int width = 0;
	int height = 0;
	int channels = 0;
	
	unsigned char* data = stbi_load(filepath, &width, &height, &channels, STBI_rgb_alpha);

	CHECK_IS_NULL_RET(data, "Failed to load image", NULL);

	t->width = (unsigned int) width;
	t->height = (unsigned int) height;

	GL_CALL(glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	));

	LOG_INFO("Loaded an image of %dx%d pixels.", t->width, t->height);

	glBindTexture(t->type, 0);

	return t;
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

