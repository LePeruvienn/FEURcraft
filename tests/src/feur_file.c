#include "FEUR_Test/FEUR_Test.h"
#include "feur_file.h"
#include "feur_string.h"

#include <string.h>

FEUR_Test_Result Test_FeurFile_Create()
{
	const char* test_path = "assets/test_create.txt";
	FeurFile* file = feur_file_create(test_path);

	FEUR_TEST_ASSERT_NOT_NULL(file);
	FEUR_TEST_ASSERT_NOT_NULL(file->path);
	FEUR_TEST_ASSERT(file->status == FEUR_FILE_NOT_LOADED);
	FEUR_TEST_ASSERT(file->data == NULL);

	feur_file_free(file);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurFile_Create_Str()
{
	FeurString* my_str = feur_string_create_c_str("assets/test_create_str.txt");
	FEUR_TEST_ASSERT_NOT_NULL(my_str);

	FeurFile* file = feur_file_create_str(my_str);

	FEUR_TEST_ASSERT_NOT_NULL(file);
	FEUR_TEST_ASSERT_NOT_NULL(file->path);
	FEUR_TEST_ASSERT(file->status == FEUR_FILE_NOT_LOADED);
	FEUR_TEST_ASSERT(file->data == NULL);

	feur_file_free(file);
	feur_string_free(my_str);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurFile_Write_And_Exists()
{
	// IMPORTANT: Same place that the Write test !!
	const char* test_path = "tests/out/test_feur_file.txt";
	FeurFile* file = feur_file_create(test_path);

	const char* payload = "FeurTest123";
	size_t payload_size = strlen(payload);
	
	feur_file_write(file, (void*) payload, payload_size);

	FEUR_TEST_ASSERT(feur_file_exists(file) == true);

	feur_file_free(file);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurFile_Load_And_GetData()
{
	// IMPORTANT: Same place that the Write test !!
	const char* test_path = "tests/out/test_feur_file.txt";
	FeurFile* file = feur_file_create(test_path);

	const char* payload = "FeurTest123";
	size_t payload_size = strlen(payload);
	feur_file_write(file, (void*)payload, payload_size);

	feur_file_load(file);

	FEUR_TEST_ASSERT(file->status == FEUR_FILE_LOADED);
	FEUR_TEST_ASSERT_NOT_NULL(file->data);

	char* loaded_data = (char*)feur_file_get_data(file);
	FEUR_TEST_ASSERT_NOT_NULL(loaded_data);
	
	FEUR_TEST_ASSERT(strncmp(loaded_data, payload, payload_size) == 0);

	feur_file_free(file);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("FeurFile - Creation & Destruction");
	FEUR_Test_Add_Test("Creation via c_str", Test_FeurFile_Create);
	FEUR_Test_Add_Test("Creation via FeurString", Test_FeurFile_Create_Str);

	FEUR_Test_Add_Group("FeurFile - I/O et Acces Disque");
	FEUR_Test_Add_Test("Ecriture et Verification d'existence", Test_FeurFile_Write_And_Exists);
	FEUR_Test_Add_Test("Lecture et Verification des donnees", Test_FeurFile_Load_And_GetData);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}

