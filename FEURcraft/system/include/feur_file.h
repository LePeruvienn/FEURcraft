#ifndef FEUR_FILE_H
#define FEUR_FILE_H

#include "feur_string.h"

#include <stdbool.h>
#include <stddef.h>

typedef enum FeurFileStatus FeurFileStatus;

enum FeurFileStatus
{
	FEUR_FILE_LOADED,
	FEUR_FILE_NOT_LOADED
};

typedef struct FeurFile FeurFile;

struct FeurFile
{
	FeurString* path;
	FeurFileStatus status;

	void* data;
	size_t size;
};

FeurFile* feur_file_create(const char* file_path);
FeurFile* feur_file_create_str(const FeurString* file_path);

void feur_file_free(FeurFile* file);

void feur_file_load(FeurFile* file);
void feur_file_write(FeurFile* file, void* data, size_t size);

void* feur_file_get_data(FeurFile* file);

bool feur_file_exists(const FeurFile* file);

size_t feur_file_get_size(const FeurFile* file);

#endif // FEUR_FILE_H
