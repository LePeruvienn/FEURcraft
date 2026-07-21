#include "vertex_layout.h"
#include "vertex.h"
#include "gl_debug.h"

#include "glad/glad.h"

#include <stddef.h>
#include <stdbool.h>

void vertex_layout_init(VertexLayout* layout, VertexAttribute attributes[],
                        unsigned int attribute_amount, GLsizei stride)
{
	if (attribute_amount > MAX_VERTEX_ATTRIBUTE_AMOUNT)
	{
		LOG_ERROR("To many vertex layout attributes for custom layout.");
		return;
	}

	layout->attribute_amount = attribute_amount;
	layout->stride = stride;

	for (unsigned int i = 0; i < attribute_amount; ++i)
	{
		layout->attributes[i] = attributes[i];
	}

	return;
}

void vertex_layout_init_default(VertexLayout* layout)
{
	layout->stride = sizeof(Vertex);
	layout->attribute_amount = 1;

	VertexAttribute* attr = layout->attributes;

	attr[0].id = VERTEX_ATTR_POSITION;
	attr[0].size = 3;
	attr[0].type = GL_FLOAT;
	attr[0].normalized = GL_FALSE;
	attr[0].offset = offsetof(Vertex, pos);
	attr[0].divisor = 0;
}

void vertex_layout_make_VAO(VertexLayout* layout)
{
	for (unsigned int i = 0; i < layout->attribute_amount; ++i)
	{
		VertexAttribute* attr = &layout->attributes[i];

		bool is_int_type = (attr->type == GL_INT   || attr->type == GL_UNSIGNED_INT   ||
		                    attr->type == GL_SHORT || attr->type == GL_UNSIGNED_SHORT ||
		                    attr->type == GL_BYTE  || attr->type == GL_UNSIGNED_BYTE  );

		// Special attribute setter for integer types
		if(is_int_type && attr->normalized == false)
		{
			GL_CALL(glVertexAttribIPointer(
				attr->id, attr->size,
				attr->type, layout->stride,
				(void*)attr->offset));
		}
		else
		{
			GL_CALL(glVertexAttribPointer(
				attr->id, attr->size,
				attr->type, attr->normalized,
				layout->stride, (void*)attr->offset));
		}
		
		GL_CALL(glEnableVertexAttribArray(attr->id));

		if (attr->divisor != 0)
		{
			GL_CALL(glVertexAttribDivisor(attr->id, attr->divisor));
		}
	}
}

