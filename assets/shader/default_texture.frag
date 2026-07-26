#version 330 core

uniform sampler2D uTexture;

in vec2 vVertexUV;
out vec4 fFragColor;

void main()
{
	vec4 texColor = texture(uTexture, vVertexUV);

	fFragColor = texColor;
}
