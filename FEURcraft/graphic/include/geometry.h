#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "mesh.h"
#include "glad/glad.h"

/**
 * \file geometry.h
 * \brief Structure représentant les données d'un modèle 3D charger dans le GPU.
 *
 * Le type `geometry` permet de faire le lien entre l'espace mémoire alloué
 * d'un modèle 3D et le code C.
 *
 * Lors de la création d'une géométrie à l'aide d'un type \ref mesh,
 * les données de l'objet 3D sont envoyer au GPU et les géométrie stock
 * les indices associées au buffer GPU du modèle.
 *
 * Ensuite à l'aide de la géométrie, nous pouvons alors lié le modèle au GPU
 * a tout moment afin de pouvoir en déssiner le modèle de différente façon,
 * mais aussi de pouvoir lui lié des shaders ou des textures.
 */

/**
* \brief Type représentant les données d'un modèle 3D sur le GPU
*/
typedef struct geometry* geometry;

/**
* \brief Créer une nouvelle géométrie à partir du modèle en paramêtre.
* \param m mesh du modèle
* \return nouvelle géométrie alloué
*/
geometry create_geometry(mesh m);

/**
* \brief Créer une nouvelle géométrie de cube
* \return nouvelle géométrie alloué
*/
geometry create_cube_geometry();

/**
* \brief Créer une nouvelle géométrie de sphère
* \param R rayon de la sphère
* \param lat_amount nombre de sommet en latitude
* \param long_amount nombre de sommet en longitude
* \return nouvelle géométrie alloué
*/
geometry create_sphere_geometry(float R, unsigned int lat_amount, unsigned int long_amount);

/**
* \brief libère la mémoire de la géométrie en passer en paramêtre
* \param g géométrie à libérer
*/
void free_geometry(geometry g);

/**
* \brief Lie les données de la géométrie au GPU
* \param g géométrie à lié
*/
void bind_geometry(geometry g);

/**
* \brief dé lie les données de la géométrie du GPU
* \param g géométrie à dé-lié
*/
void unbind_geometry(geometry g);

/**
* \brief Déssine la géométrie actuelle en faisant un appel GPU
* \param g géométrie à déssiner
* \param mode mode de déssin
*/
void draw_geometry(geometry g, GLenum mode);

/**
* \brief fait un appel GPU pour déssiner plusieurs instance la géométrie
*
* \attention ne pas oublier de lié un buffer d'instance avant d'appeler cette méthode.
*
* \param g géométrie à déssiner
* \param mode mode de déssin
* \param amount nombre d'instance à déssiner
*/
void draw_geometry_instanced(geometry g, GLenum mode, unsigned int amount);

#endif // GEOMETRY_H
