#ifndef BLOCK_FACE_H
#define BLOCK_FACE_H

// Définition des différents indices pour les faces des blocks

#include <stdint.h>

typedef uint8_t BlockFace;

enum
{
	BLOCK_FACE_FRONT = 0,
	BLOCK_FACE_BACK  = 1,
	BLOCK_FACE_TOP   = 2,
	BLOCK_FACE_BOT   = 3,
	BLOCK_FACE_LEFT  = 4,
	BLOCK_FACE_RIGHT = 5,

	BLOCK_FACE_COUNT
};

#endif // BLOCK_FACE_H
