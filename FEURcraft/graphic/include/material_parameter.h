#ifndef MATERIAL_PARAMETER
#define MATERIAL_PARAMETER

#include "feur_types.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#include <endian.h>
#include <stdbool.h>

#define MAT_PARAM_MAX_STR_SIZE 128

typedef enum MaterialParameterType MaterialParameterType;

enum MaterialParameterType
{
	MAT_PARAM_BOOL,
	MAT_PARAM_FLOAT,
	MAT_PARAM_VEC2,
	MAT_PARAM_VEC3,
	MAT_PARAM_VEC4,
	MAT_PARAM_MAT4,
	MAT_PARAM_TEXTURE_UNIT
};

typedef union MaterialParameterValue MaterialParameterValue;

union MaterialParameterValue
{
	bool bool_val;
	float float_val;
	Vec2 vec2_val;
	Vec3 vec3_val;
	Vec4 vec4_val;
	Mat4 mat4_val;
	uint texture_unit_val;
};

typedef struct MaterialParameter MaterialParameter;

struct MaterialParameter
{
	char name[MAT_PARAM_MAX_STR_SIZE];
	MaterialParameterType type;
	MaterialParameterValue value;
};

void material_parameter_init(MaterialParameter* param, void* value, MaterialParameterType type);

void material_parameter_set_value(MaterialParameter* param);

#endif // MATERIAL_PARAMETER
