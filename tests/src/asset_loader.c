#include "FEUR_Test/FEUR_Test.h"

#include "asset_loader.h"

#include <stdlib.h>


FEUR_Test_Result Test_Asset()
{
	const char* asset_path = "assets/textures/pumpkin_block.fasset";

	ImageArray* asset = asset_load_image_array(asset_path);
}

int main()
{
	FEUR_Test_Init();

	FEUR_Test_Add_Test("Test Asset",  Test_Asset);

	FEUR_Test_Run();

	FEUR_Test_End();

	return 0;
}
