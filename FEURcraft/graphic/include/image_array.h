#ifndef IMAGE_ARRAY_H
#define IMAGE_ARRAY_H

#include "image.h"

#include <stdbool.h>
#include <stddef.h>

/**
 * \file image_array.h
 * \brief Permet de stocker une liste d'image de même taille et cannaux.
 *
 * Structure de données représetant une list d'image de même taille et de même canneaux.
 * Elle est surtout utilisé pour représenter les donnes CPU/RAM d'une \ref TextureArray
 */

/**
* \brief Liste d'image de même taille et canneaux
*/
typedef struct ImageArray ImageArray;

struct ImageArray
{
	// theses are the param for a single image !
	unsigned int width;
	unsigned int height;
	unsigned int channels;

	unsigned int img_count;
	unsigned int img_max_count;

	unsigned char* data;
};

/**
* \brief Créer une liste d'image vide
* \param width largeur \b des \b images de la liste
* \param height longeur \b des \b images de la liste
* \param channels nombre de canneaux \b des \b images de la liste
* \return Pointeur vers une \ref ImageArray alloué sur le tas
*/
ImageArray* image_array_create(unsigned int width, unsigned int height,
                               unsigned int channels);

/**
* \brief Libère la mémoire de l' \ref ImageArray en paramêtre
* \param tex_array \ref ImageArray cible 
*/
void image_array_free(ImageArray* tex_array);

/**
* \brief Ajoute une image à l' \ref ImageArray
* \warning L'image ajouter doit avoir les même dimension et le même nombre de canneaux que la ImageArray.
* \param tex_array \ref ImageArray cible 
* \param img \ref Image à ajouter
* \return \c -1 si l'image n'as pas pu être ajouter, sinon l'index de l'image. 
*/
int image_array_add_image(ImageArray* tex_array, Image* img);

#endif // IMAGE_ARRAY_H
