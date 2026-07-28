#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vertex_layout.h"

#include "array_list.h"

#include <stddef.h>

/**
 * \file geometry.h
 * \brief Structure représentant les données d'un modèle 3D
 *
 * Le type `geometry` représente les données de \ref vertex alloué sur la RAM.
 * L'ensemble de ces vertex représente un modèle 3D.
 *
 * Chaque geometry peut avoir une structure de vertex différente (avec normal, sans normal).
 */

/**
* \brief Type représentant les données de vertex d'un modèle 3D.
*/
typedef struct Geometry Geometry;

struct Geometry
{
	ArrayList* vertices;
	ArrayList* indices;

	VertexLayout layout; // doit être corda avec les type de vertex dans le buffer
};

/**
* \brief Créer les données géométrique d'un modèle pour
* le type de Vertex du \ref VertexLayout
*
* \return geometry vertex du cube
*/
Geometry* geometry_create(const void* vertices_buffer, size_t vertices_amount,
                          const unsigned int* indices_buffer, size_t indices_amount,
                          VertexLayout layout);

/**
* \brief Créer les données de géomotrie d'un cube
* avec des vertices de \ref Vertex
*
* \return geometry vertex du cube
*/
Geometry* geometry_create_cube();

/**
* \brief Créer les données de géomotrie d'un cube
* avec des vertices de \ref VertexUV
*
* \return geometry vertex du cube
*/
Geometry* geometry_create_cube_UV();

/**
* \brief Créer les données de géomotrie d'un block
* avec des vertices de \ref VertexBlock
*
* \return geometry vertex d'un block
*/
Geometry* geometry_create_block();

/**
* \brief Créer les données de vertex d'une sphère
* \param R rayon de la sphère
* \param lat_amount nombre de sommet en latitude
* \param long_amount nombre de sommet en longitude
* \return geometry vertex de la sphère
*/
Geometry* geometry_create_sphere(float R, unsigned int lat_amount, unsigned int long_amount);

void geometry_add_array(Geometry* g, const ArrayList* vertices, const ArrayList* indices);


void geometry_add_buffer(Geometry* g, const void* vertices_buffer, size_t vertices_amount,
                         const unsigned int* indices_buffer, size_t indices_amount);

/**
* \brief libère la mémoire de la geometry passer en paramêtre
* \param g geometry à libérer
*/
void geometry_free(Geometry* g);

/**
* \brief charge les données de la geometry dans le GPU
* \param m geometry à charger
*/
void geometry_load_to_gpu(Geometry* g);

#endif // GEOMETRY_H
