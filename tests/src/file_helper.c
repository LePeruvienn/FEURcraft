#include "FEUR_Test/FEUR_Test.h"
#include "file_helper.h"

#include <string.h>
#include <stdlib.h>

static const char* TEST_TXT_PATH = "tests/out/test_helper.txt";
static const char* TEST_BIN_PATH = "tests/out/test_helper.bin";

static int bin_data[] = { 0, 1, 0, 1, 0, 0, 0, 1, 1};
const char* txt_data = "Hello from FEUR_Test!";

FEUR_Test_Result Test_FileHelper_WriteData()
{

	size_t txt_size = strlen(txt_data);
	file_write_data(TEST_TXT_PATH, (void*)txt_data, txt_size);

	size_t bin_size = sizeof(bin_data);
	file_write_data(TEST_BIN_PATH, (void*) bin_data, bin_size);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FileHelper_Exists()
{
	FEUR_TEST_ASSERT(file_exists(TEST_TXT_PATH) == true);
	FEUR_TEST_ASSERT(file_exists(TEST_BIN_PATH) == true);
	FEUR_TEST_ASSERT(file_exists(NULL) == false);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FileHelper_GetSize()
{
	const char* txt_data = "Hello from FEUR_Test!";
	size_t txt_size = strlen(txt_data);
	
	FEUR_TEST_ASSERT(file_get_size(TEST_TXT_PATH) == txt_size);
	FEUR_TEST_ASSERT(file_get_size(TEST_BIN_PATH) == sizeof(bin_data));

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FileHelper_ReadTxt()
{
	char* text = file_read_txt(TEST_TXT_PATH);

	FEUR_TEST_ASSERT_NOT_NULL(text);
	
	FEUR_TEST_ASSERT(strcmp(text, "Hello from FEUR_Test!") == 0);

	free(text);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FileHelper_ReadBin()
{
	size_t out_size = 0;
	
	void* buffer = file_read_bin(TEST_BIN_PATH, &out_size);

	FEUR_TEST_ASSERT_NOT_NULL(buffer);
	FEUR_TEST_ASSERT(out_size == sizeof(bin_data));

	int* int_buffer = (int*) buffer;

	for (unsigned int i = 0; i < sizeof(bin_data) / sizeof(int); ++i)
	{
		FEUR_TEST_ASSERT(int_buffer[i] == bin_data[i])
	}

	free(buffer);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("File Helper");
	
	FEUR_Test_Add_Test("Ecriture des fichiers de test", Test_FileHelper_WriteData);
	FEUR_Test_Add_Test("Verification d'existence", Test_FileHelper_Exists);
	FEUR_Test_Add_Test("Recuperation des tailles", Test_FileHelper_GetSize);
	FEUR_Test_Add_Test("Relecture de fichier Texte", Test_FileHelper_ReadTxt);
	FEUR_Test_Add_Test("Relecture de fichier Binaire", Test_FileHelper_ReadBin);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
