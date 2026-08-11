#ifndef CHUNK_MESHING_H
#define CHUNK_MESHING_H

#include "chunk.h"

#include "geometry.h"
#include "mesh.h"

/**
 * \file chunk_meshing.h
 * \brief Gère la génération des données géométrique d'un chunk
 */

/**
 * \brief Génère les données géméotrique d'un chunk
 * \param chunk \ref Chunk auquel on veut générer la géométrie
 * \return Donnés gémoetrique stocker dans un pointeur \ref Geometry alloué
 */
Geometry* chunk_geometry_create(const Chunk* chunk);

Mesh* chunk_mesh_create(const Chunk* chunk);

#endif // CHUNK_MESHING_H
