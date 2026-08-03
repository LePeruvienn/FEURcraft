#ifndef ATLAS_H
#define ATLAS_H

/**
 * \file atlas.h
 * \brief Atlas pour stocker plusieurs images sur la même images.
 *
 * Atlas représente les données CPU d'un texture atlas,
 * elle permet d'ajouter des images de tailles différents sur la même image.
 * On peut ensuite récupérer les UVs de ces images facilement.
 */

#include "image.h"
#include "texture_coord.h"

#include <stdbool.h>

#define ATLAS_MAX_IMAGE_AMOUNT 32

/**
* \brief Type représentant un Atlas d'image
*/
typedef struct Atlas Atlas;

struct Atlas
{
	unsigned int width;
	unsigned int height;
	unsigned int channels;

	unsigned int cursor_x;
	unsigned int cursor_y;
	unsigned int row_height;

	unsigned char* data;

	unsigned int images_amount;
	TextureCoords images_coords[ATLAS_MAX_IMAGE_AMOUNT];
};

/**
* \brief Créer un Atlas alloué sur le tas
* \param width Largeur de l'atlas
* \param height Longueur de l'atlas
* \param channels Nombre de canneaux de couleurs de l'atlas (RGB, RGBA, ...)
* \return pointeur vers un Atlas alloué
*/
Atlas* atlas_create(unsigned int width, unsigned int height,
                    unsigned int channels);

/**
* \brief Libére la mémoire de l'atlas en paramêtre
* \param atlas Atlas à libérer
*/
void atlas_free(Atlas* atlas);

/**
* \brief Ajoute une image à l'atlas
* \param atlas Atlas ou ajouter l'image
* \param img Image à ajouter
* \param uv_out Ou la fonction va écrire les coordonnées de texture sur l'atlas de l'image ajouter
* \return retourne \c true si l'image à pu être ajouter et \c false sinon.
*/
bool atlas_add_image(Atlas* atlas, Image* img, TextureCoords* uv_out);

/**
* \brief Permet de récupérer les coordonnées de texture sur l'Atlas d'une image
* \param atlas Atlas cible
* \param indx index de l'image qu'on veut récupérer
* \param uv_out Ou la fonction va écrire les coordonnées récupérer
* \return retourne \c true si les coordonnées on pu être trouver et \c false sinon.
*/
bool atlas_get_image_coords(Atlas* atlas, unsigned int index, TextureCoords* uv_out);

/**
* \brief Permet d'écrire le contenue de l'atlas dans une image
* \param atlas Atlas à écrire
* \param file_path chemin vers le fichier de sortie
*/
void atlas_write_image(Atlas* atlas, const char* file_path);

#endif // ATLAS_H
