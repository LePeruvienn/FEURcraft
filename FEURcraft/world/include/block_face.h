#ifndef BLOCK_FACE_H
#define BLOCK_FACE_H

// Définition des différents indices pour les faces des blocks

#include <stdint.h>

typedef enum BlockFace BlockFace;

enum BlockFace
{
	BLOCK_FACE_FRONT = 0,
	BLOCK_FACE_BACK,
	BLOCK_FACE_TOP,
	BLOCK_FACE_BOT,
	BLOCK_FACE_LEFT,
	BLOCK_FACE_RIGHT,

	BLOCK_FACE_COUNT
};

#endif // BLOCK_FACE_H
