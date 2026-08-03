#ifndef TEXTURE_H
#define TEXTURE_H

#include "image.h"
#include "atlas.h"

#include "glad/glad.h"

#include <stddef.h>

/**
 * \file texture.h
 * \brief Structure représentant les données d'une texture charger dans le GPU
 *
 * Contrairement à la structure \ref Image ici une texture représente des données de type "image" 
 * charger dans le GPU. Ces données peuvent ensuite être utilisé dans les shaders durant le rendu
 */

/**
* \brief Type représentant une texture charger dans le GPU
*/
typedef struct Texture Texture;

struct Texture
{
	GLuint id;
	GLuint type;

	unsigned int width;
	unsigned int height;
};

/**
* \brief Créer une texture à partir des données passer en paramêtre
*
* \warning Doit être un buffer de données RGBA (4 octets) 
* avec la taille du buffer est égale à width \times height
*
* \param data pointeur vers le buffer de données
* \param width largeur de la texture
* \param height hateur de la texture
* \return texture dont la mémoire à été alloué
*/
Texture* create_texture(unsigned char* data,
                        unsigned int width, unsigned int height);

/**
* \brief Créer une texture à partir de l'image passer en paramêtre
*
* \param img image à partir de laquelle créer la texture
* \return texture dont la mémoire à été alloué
*/
Texture* create_texture_from_image(Image* img);

/**
* \brief Créer une texture à partir du fichier passer en paramêtre
*
* \param path chemin vers le fichier source
* \return texture dont la mémoire à été alloué
*/
Texture* create_texture_from_file(const char* path);

/**
* \brief Créer une texture à partir d'un atlas
*
* \param atlas donnée de l'atlas
* \return texture dont la mémoire à été alloué
*/
Texture* create_texture_from_atlas(Atlas* atlas);

/**
* \brief Libère la mémoire de la texture en paramêtre
* \param t texture à libérer
*/
void free_texture(Texture* t);

/**
* \brief Lie au GPU la texture passer en paramêtre
*
* Lie la texture au GPU et l'active à l'index \a unit donné en paramêtre.
*
* \param t texture à lier
* \param unit index ou placer la texture
*/
void bind_texture(Texture* t, unsigned int unit);

/**
* \brief Dé-lie la texture passer en paramêtre du GPU
* \param t texture à dé-lier
* \param unit index de la texture à délier
*/
void unbind_texture(Texture* t, unsigned int unit);


#endif // TEXTURE_H
