#include "feur_file.h"
#include "feur_string.h"
#include "file_helper.h"

#include "error_checker.h"
#include "ptr_helper.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

FeurFile* feur_file_create(const char* file_path)
{
	CHECK_IS_NULL_RET(file_path, "Cannot create file from a NULL filepath", NULL);

	FeurFile* file = malloc(sizeof(struct FeurFile));

	CHECK_IS_NULL_RET(file, "Failed to malloc FeurFile", NULL);

	file->path = feur_string_create_c_str(file_path);

	if (file->path == NULL)
	{
		LOG_ERROR("Failed to copy filepath");
		feur_file_free(file);
		return NULL;
	}
	
	file->status = FEUR_FILE_NOT_LOADED;
	file->data = NULL;
	file->size = 0;

	return file;
}

FeurFile* feur_file_create_str(const FeurString* file_path)
{
	CHECK_IS_NULL_RET(file_path, "Cannot create file from a NULL filepath", NULL);

	return feur_file_create(file_path->c_str);
}

void feur_file_free(FeurFile* file)
{
	CHECK_IS_NULL_RET(file, "Cannot free a NULL FeurFile", );

	FREE_PTR_NOT_NULL(file->path, feur_string_free);
	FREE_PTR_NOT_NULL(file->data, free);

	free(file);
}

static size_t get_file_size_from_fd(FILE* fd)
{
	long start_cur_pos = ftell(fd);

	CHECK_COND_RET(start_cur_pos >= 0, "Failed to get cursor pos", 0);

	CHECK_COND_RET(fseek(fd, 0, SEEK_END) == 0,
		"Failed to go at the end of the file", 0);

	long length = ftell(fd);

	CHECK_COND_RET(fseek(fd, start_cur_pos, SEEK_SET) == 0,
		"Failed to to go back at file start pos", 0);

	CHECK_COND_RET(length >= 0, "Failed to get file size", 0);

	return (size_t) length;
}

void feur_file_load(FeurFile* file)
{
	CHECK_IS_NULL_RET(file, "Cannot load a NULL FeurFile", );

	if (file->data != NULL)
	{
		LOG_WARNING("Loading FeurFile that was already loaded.");
		free(file->data);
		file->data = NULL;
		file->size = 0;
	}

	FILE *fd = fopen(file->path->c_str, "rb");

	CHECK_IS_NULL_RET(fd, "Failed to open FeurFile cannot load.", );

	size_t file_size = get_file_size_from_fd(fd);

	if (file_size == 0)
	{
		LOG_WARNING("Loaded an empty file");
		fclose(fd);
		file->status = FEUR_FILE_LOADED;
		return;
	}

	file->data = malloc(file_size + 1);

	if (file->data == NULL)
	{
		LOG_ERROR("Failed to malloc FeurFile data");
		fclose(fd);
		return;
	}

	size_t read_bytes = fread(file->data, 1, file_size, fd);

	fclose(fd);

	if(read_bytes != file_size)
	{
		LOG_ERROR("Failed to read all data from FeurFile");
		free(file->data);
		file->data = NULL;
		return;
	}

	// Just in case it's text data
	((char*) file->data)[file_size] = '\0';

	file->status = FEUR_FILE_LOADED;
	file->size = file_size;
}

void feur_file_write(FeurFile* file, void* data, size_t size)
{
	CHECK_IS_NULL_RET(file, "Cannot write a NULL FeurFile", );
	CHECK_IS_NULL_RET(data, "Cannot write NULL data", );

	FILE *fd = fopen(file->path->c_str, "wb");
	CHECK_IS_NULL_RET(fd, "Failed to open FeurFile for writing", );

	size_t written = fwrite(data, 1, size, fd);

	CHECK_COND(written == size, "Failed to write all data to FeurFile");

	fclose(fd);
}

void* feur_file_get_data(FeurFile* file)
{
	CHECK_IS_NULL_RET(file, "Cannot get data from FeurFile", NULL);

	if (file->status == FEUR_FILE_LOADED)
	{
		CHECK_IS_NULL_WARN(file->data, "FeurFile loaded but the data is NULL");
		return file->data;
	}

	CHECK_COND(file->data == NULL, "FeurFile is not loaded but the data is not NULL");

	feur_file_load(file);

	CHECK_COND_RET(file->status == FEUR_FILE_LOADED, "Failed to load FeurFile.", NULL);

	CHECK_COND_WARN(file->data == NULL , "Getting empty data from a FeurFile");

	return file->data;
}

size_t feur_file_get_size(const FeurFile* file)
{
	CHECK_IS_NULL_RET(file,
		"Cannot get file size of a NULL FeurFile", 0);

	if (file->status == FEUR_FILE_LOADED)
	{
		return file->size;
	}

	return file_get_size(file->path->c_str);
}

bool feur_file_exists(const FeurFile* file)
{
	CHECK_IS_NULL_RET(file,
		"Tried to check if file exists with a NULL FeurFile*", false);

	return file_exists(file->path->c_str);
}

