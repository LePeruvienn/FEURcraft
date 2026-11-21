#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include "image_array.h"

#include "shader_program.h"

ImageArray* asset_load_image_array(const char* file_path);

ShaderProgram* asset_load_shader_program(const char* file_path);

#endif // ASSET_LOADER_H
