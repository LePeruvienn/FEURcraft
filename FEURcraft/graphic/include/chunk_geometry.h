#ifndef CHUNK_GEOMETRY_H
#define CHUNK_GEOMETRY_H

#include "geometry.h"
#include "chunk.h"

/**
 * \file chunk_geometry.h
 * \brief Gère la génération des données géométrique d'un chunk
 */

/**
 * \brief Génère les données géméotrique d'un chunk
 * \param chunk \ref Chunk auquel on veut générer la géométrie
 * \return Donnés gémoetrique stocker dans un pointeur \ref Geometry alloué
 */
Geometry* chunk_geometry_create(const Chunk* chunk);

#endif // CHUNK_GEOMETRY_H
