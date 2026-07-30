#include "FEUR_Test/FEUR_Test.h"
#include "chunk.h"
#include "vec3i.h"

#include <string.h>

FEUR_Test_Result Test_Chunk_Pos_Valid()
{
	FEUR_TEST_ASSERT(chunk_is_pos_valid(VEC3I_ZERO));
	FEUR_TEST_ASSERT(chunk_is_pos_valid(VEC3I(CHUNK_LENGTH - 1, CHUNK_HEIGHT - 1, CHUNK_LENGTH - 1)));

	FEUR_TEST_ASSERT(chunk_is_pos_valid(VEC3I(-1, 0, 0)) == false);
	FEUR_TEST_ASSERT(chunk_is_pos_valid(VEC3I(0, -5, 0)) == false);

	FEUR_TEST_ASSERT(chunk_is_pos_valid(VEC3I(CHUNK_LENGTH, 0, 0)) == false);
	FEUR_TEST_ASSERT(chunk_is_pos_valid(VEC3I(0, CHUNK_HEIGHT, 0)) == false);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Chunk_Index_Roundtrip()
{
	Vec3i original_pos = VEC3I(5, 128, 7);
	
	size_t index = chunk_block_index(original_pos);
	Vec3i converted_pos = chunk_block_pos(index);

	FEUR_TEST_ASSERT(original_pos.x == converted_pos.x);
	FEUR_TEST_ASSERT(original_pos.y == converted_pos.y);
	FEUR_TEST_ASSERT(original_pos.z == converted_pos.z);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Chunk_Set_Get()
{
	Chunk chunk = CHUNK_EMPTY;
	Vec3i pos = VEC3I(2, 64, 8);
	
	Block test_block;
	memset(&test_block, 1, sizeof(Block));

	chunk_set_block(&chunk, test_block, pos);
	Block retrieved_block = chunk_get_block_from_pos(&chunk, pos);

	FEUR_TEST_ASSERT(memcmp(&test_block, &retrieved_block, sizeof(Block)) == 0);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Chunk_Del()
{
	Chunk chunk = CHUNK_EMPTY;
	Vec3i pos = VEC3I(10, 20, 5);
	
	Block test_block;
	memset(&test_block, 1, sizeof(Block));

	Block empty_block;
	memset(&empty_block, 0, sizeof(Block));

	chunk_set_block(&chunk, test_block, pos);
	chunk_del_block(&chunk, pos);

	Block retrieved_block = chunk_get_block_from_pos(&chunk, pos);

	FEUR_TEST_ASSERT(memcmp(&retrieved_block, &empty_block, sizeof(Block)) == 0);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_Chunk_Fill()
{
	Chunk chunk = CHUNK_EMPTY;

	Block test_block;
	memset(&test_block, 42, sizeof(Block));

	chunk_fill_all(&chunk, test_block);

	Block start = chunk_get_block_from_index(&chunk, 0);
	Block middle = chunk_get_block_from_index(&chunk, CHUNK_SIZE / 2);
	Block end = chunk_get_block_from_index(&chunk, CHUNK_SIZE - 1);

	FEUR_TEST_ASSERT(memcmp(&start, &test_block, sizeof(Block)) == 0);
	FEUR_TEST_ASSERT(memcmp(&middle, &test_block, sizeof(Block)) == 0);
	FEUR_TEST_ASSERT(memcmp(&end, &test_block, sizeof(Block)) == 0);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_TEST_LOG("Début des tests du système de Chunk !");

	FEUR_Test_Add_Group("Chunk - Coordonnées et Indexation");
	FEUR_Test_Add_Test("Validité des positions", Test_Chunk_Pos_Valid);
	FEUR_Test_Add_Test("Conversion Index <-> Position", Test_Chunk_Index_Roundtrip);

	FEUR_Test_Add_Group("Chunk - Manipulation des Blocs");
	FEUR_Test_Add_Test("Set et Get Block", Test_Chunk_Set_Get);
	FEUR_Test_Add_Test("Suppression de Block (Del)", Test_Chunk_Del);
	FEUR_Test_Add_Test("Remplissage global (Fill)", Test_Chunk_Fill);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}

