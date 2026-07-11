#ifndef VERTEX_H
#define VERTEX_H

#include "vec3.h"

/**
 * \file vertex.h
 * \brief Fichier contenant les différent structure de vertex utilisable
 */

/**
 * \brief Type pour les vertex avec position et couleur,
 */
typedef struct vertex vertex;

struct vertex
{
	vec3 pos;
};

#endif // VERTEX_H
