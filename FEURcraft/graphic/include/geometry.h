#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vertex.h"
#include "vertex_layout.h"

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
	void* vertices; // Peut contenir différent type de vertex
	size_t vertices_size;
	unsigned int vertices_amount;

	unsigned int* indices;
	unsigned int indices_amount;

	VertexLayout layout; // doit être corda avec les type de vertex dans le buffer
};

/**
* \brief Créer les données de vertex d'un cube
* \return geometry vertex du cube
*/
Geometry* create_cube();

/**
* \brief Créer les données de vertex d'une sphère
* \param R rayon de la sphère
* \param lat_amount nombre de sommet en latitude
* \param long_amount nombre de sommet en longitude
* \return geometry vertex de la sphère
*/
Geometry* create_sphere(float R, unsigned int lat_amount, unsigned int long_amount);

/**
* \brief Créer les données de vertex pour un ensemble de lignes
* \param vertices différent points des lignes
* \param size nombre de point total
* \return geometry vertex des lignes
*/
Geometry* create_line(Vertex* vertices, unsigned int size);

/**
* \brief libère la mémoire de la geometry passer en paramêtre
* \param m geometry à libérer
*/
void free_geometry(Geometry* g);

/**
* \brief charge les données de la geometry dans le GPU
* \param m geometry à charger
*/
void load_geometry_data(Geometry* g);

#endif // GEOMETRY_H
