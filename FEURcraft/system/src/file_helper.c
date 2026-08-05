#include "file_helper.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

void* file_read_bin(const char* path, size_t* out_size)
{
	if (path == NULL)
	{
		LOG_ERROR("Cannot read binary file, path is NULL");
		return NULL;
	}

	FILE* file = fopen(path, "rb");

	if (file == NULL)
	{
		LOG_ERROR("Failed to open binary file : %s", path);
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read binary file, fseek failed");
		return NULL;
	}

	long size = ftell(file);

	if (size <= 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read binary file, size is less or equal to 0");
		return NULL;
	}

	rewind(file);

	void* buf = malloc(size);

	if (buf == NULL)
	{
		fclose(file);
		LOG_ERROR("Cannot read binary file, failed to allocate buffer");
		return NULL;
	}

	size_t read_size = fread(buf, 1, size, file);

	fclose(file);

	if (read_size != (size_t)size)
	{
		free(buf);
		LOG_ERROR("Failed read all binary file content, read size and file size mismatch");
		return NULL;
	}

	if (out_size != NULL)
	{
		*out_size = (size_t)size;
	}

	return buf;
}

char* file_read_txt(const char* path)
{
	if (path == NULL)
	{
		LOG_ERROR("Cannot read text file, path is NULL");
		return NULL;
	}

	FILE* file = fopen(path, "rb");

	if (file == NULL)
	{
		LOG_ERROR("Failed to open text file : %s", path);
		return NULL;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read text file, fseek failed");
		return NULL;
	}

	long size = ftell(file);

	if (size <= 0)
	{
		fclose(file);
		LOG_ERROR("Cannot read text file, size is less or equal to 0");
		return NULL;
	}

	rewind(file);

	char* buf = malloc(size + 1);
	if (buf == NULL)
	{
		fclose(file);
		LOG_ERROR("Cannot read text file, malloc failed");
		return NULL;
	}

	size_t read_size = fread(buf, 1, size, file);

	fclose(file);

	if (read_size != (size_t) size)
	{
		free(buf);
		LOG_ERROR("Failed read all text file content, read size and file size mismatch");
		return NULL;
	}

	buf[size] = '\0';

	return buf;
}

void file_write_data(const char* path, void* buffer, size_t size)
{
	if (path == NULL || buffer == NULL)
	{
		LOG_ERROR("Cannot write data, path or buffer is NULL");
		return;
	}

	FILE* file = fopen(path, "wb");

	if (file == NULL)
	{
		LOG_ERROR("Failed to open file for writing : %s", path);
		return;
	}

	size_t written = fwrite(buffer, 1, size, file);
	
	fclose(file);

	if (written != size)
	{
		LOG_ERROR("Failed to write all data, written size and requested size mismatch");
	}
}

bool file_exists(const char* path)
{
	if (path == NULL)
	{
		LOG_WARNING("A NULL file path cannot exists");
		return false;
	}

	FILE* file = fopen(path, "r");

	if (file != NULL)
	{
		fclose(file);
		return true;
	}

	return false;
}

size_t file_get_size(const char* path)
{
	if (path == NULL)
	{
		LOG_ERROR("Cannot get file size, path is NULL");
		return 0;
	}

	FILE* file = fopen(path, "rb");

	if (file == NULL)
	{
		LOG_ERROR("Failed to open file to get size : %s", path);
		return 0;
	}

	if (fseek(file, 0, SEEK_END) != 0)
	{
		fclose(file);
		LOG_ERROR("Cannot get file size, fseek failed");
		return 0;
	}

	long size = ftell(file);
	
	fclose(file);

	if (size < 0)
	{
		LOG_ERROR("Cannot get file size, ftell failed");
		return 0;
	}

	return (size_t) size;
}

