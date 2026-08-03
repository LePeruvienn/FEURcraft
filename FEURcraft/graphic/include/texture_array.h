#ifndef TEXTURE_ARRAY_H
#define TEXTURE_ARRAY_H

#include "image_array.h"

#include "glad/glad.h"

/**
 * \file texture_array.h
 * \brief Structure représentant les données d'une list ed texture charger dans le GPU
 * 
 * Structure ayant un rôle similaire à \ref Texture mais implémentant les contraintes
 * spécifique aux TextureArrays
 */

/**
* \brief Type représentant une liste de texture sur le GPU
*/
typedef struct TextureArray TextureArray;

struct TextureArray
{
	GLuint id;

	unsigned int width;
	unsigned int height;
	unsigned int layer_count;
};

/**
* \brief Créer une \ref TextureArray à partir de données brut CPU
* \param data pointeur vers les données brut CPU
* \param width largeur \b d'une \b image
* \param height hauteur \b d'une \b image
* \param channels nombre de canneaux de \b chaque \b image
* \param layer_count nombre de d'image totale dans la liste
* \return \ref TextureArray alloué sur le tas et le GPU
*/
TextureArray* texture_array_create(unsigned char* data,
                                   unsigned int width,
                                   unsigned int height,
                                   unsigned int channels,
                                   unsigned int layer_count);

/**
* \brief Créer une \ref TextureArray à partir d'une \ref ImageArray
* \param img_array Liste d'image à partir on veut créer notre \ref TextureArray
* \return \ref TextureArray alloué sur le tas et le GPU
*/
TextureArray* texture_array_create_from_img_array(ImageArray* img_array);

/**
* \brief Libère la mémoire du tas et du GPU de la \refTextureArrayCible
* \param tex_array \ref TextureArray cible
*/
void texture_array_free(TextureArray* tex_array);

/**
* \brief Permet de définir la \ref TextureArray actuelle comme celle utilisé pour le rendu
* \param tex_array \ref TextureArray cible
* \param unit à quelle emplacement la stocker
*/
void texture_array_bind(TextureArray* tex_array, unsigned int unit);

/**
* \brief Désaffecte la \ref TextureArray comme celle actuellement utilisé pour le rendu
*/
void texture_array_unbind();

#endif // TEXTURE_ARRAY_H
