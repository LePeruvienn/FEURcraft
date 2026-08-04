#include "FEUR_Test/FEUR_Test.h"

#include "feur_string.h"
#include <string.h>

FEUR_Test_Result Test_FeurString_Create()
{
	FeurString* string = feur_string_create(5);

	FEUR_TEST_ASSERT_NOT_NULL(string);
	FEUR_TEST_ASSERT_NOT_NULL(string->c_str);
	FEUR_TEST_ASSERT(string->length == 0);
	FEUR_TEST_ASSERT(string->capacity >= 5); 
	FEUR_TEST_ASSERT(string->c_str[0] == '\0');
	FEUR_TEST_ASSERT(string->is_static == false);

	feur_string_free(string);
	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurString_create_c_str()
{
	FeurString* string = feur_string_create_c_str("Hello");

	FEUR_TEST_ASSERT_NOT_NULL(string);
	FEUR_TEST_ASSERT_NOT_NULL(string->c_str);
	FEUR_TEST_ASSERT(string->length == 5);
	FEUR_TEST_ASSERT(strcmp(string->c_str, "Hello") == 0);

	feur_string_free(string);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurString_Create_From()
{
	FeurString* base = feur_string_create_c_str("Hello World!");
	
	FeurString* sub = feur_string_create_from(base, 6, 10);

	FEUR_TEST_ASSERT_NOT_NULL(sub);
	FEUR_TEST_ASSERT(sub->length == 5);
	FEUR_TEST_ASSERT(strcmp(sub->c_str, "World") == 0);

	feur_string_free(base);
	feur_string_free(sub);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurString_Set()
{
	FeurString* string = feur_string_create(10);
	
	feur_string_set_c_str(string, "Test", 0);
	FEUR_TEST_ASSERT(string->length == 4);
	FEUR_TEST_ASSERT(strcmp(string->c_str, "Test") == 0);

	feur_string_set_c_str(string, "Feur", 0);
	FEUR_TEST_ASSERT(string->length == 4);
	FEUR_TEST_ASSERT(strcmp(string->c_str, "Feur") == 0);

	feur_string_free(string);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurString_Append()
{
	FeurString* str1 = feur_string_create_c_str("Hello");
	
	feur_string_append_str(str1, " World");
	FEUR_TEST_ASSERT(str1->length == 11);
	FEUR_TEST_ASSERT(strcmp(str1->c_str, "Hello World") == 0);

	FeurString* str2 = feur_string_create_c_str("!");
	feur_string_append(str1, str2);
	FEUR_TEST_ASSERT(str1->length == 12);
	FEUR_TEST_ASSERT(strcmp(str1->c_str, "Hello World!") == 0);

	feur_string_free(str1);
	feur_string_free(str2);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurString_Equal()
{
	FeurString* s1 = feur_string_create_c_str("abc");
	FeurString* s2 = feur_string_create_c_str("abc");
	FeurString* s3 = feur_string_create_c_str("abcd");
	FeurString* s4 = feur_string_create_c_str("abx");

	FEUR_TEST_ASSERT(feur_string_equal(s1, s1) == true);
	FEUR_TEST_ASSERT(feur_string_equal(s1, s2) == true);
	FEUR_TEST_ASSERT(feur_string_equal(s1, s3) == false);
	FEUR_TEST_ASSERT(feur_string_equal(s1, s4) == false);

	feur_string_free(s1);
	feur_string_free(s2);
	feur_string_free(s3);
	feur_string_free(s4);

	return FEUR_Test_Success;
}

FEUR_Test_Result Test_FeurString_AutoResize()
{
	FeurString* string = feur_string_create(2);
	size_t initial_capacity = string->capacity;

	const char* long_text = "Ceci est un texte beaucoup trop long pour la capacite initiale.";
	feur_string_append_str(string, long_text);

	FEUR_TEST_ASSERT(string->length == strlen(long_text));
	FEUR_TEST_ASSERT(string->capacity > initial_capacity);
	FEUR_TEST_ASSERT(strcmp(string->c_str, long_text) == 0);

	feur_string_free(string);

	return FEUR_Test_Success;
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Group("Création");
	FEUR_Test_Add_Test("Création basique", Test_FeurString_Create);
	FEUR_Test_Add_Test("Création depuis char*", Test_FeurString_create_c_str);
	FEUR_Test_Add_Test("Création sous-chaîne", Test_FeurString_Create_From);

	FEUR_Test_Add_Group("Manipulation");
	FEUR_Test_Add_Test("Modification (Set)", Test_FeurString_Set);
	FEUR_Test_Add_Test("Concaténation (Append)", Test_FeurString_Append);
	FEUR_Test_Add_Test("Comparaison (Equal)", Test_FeurString_Equal);

	FEUR_Test_Add_Group("Gestion Mémoire");
	FEUR_Test_Add_Test("Redimensionnement Auto", Test_FeurString_AutoResize);

	FEUR_Test_Run();
	FEUR_Test_End();

	return 0;
}
