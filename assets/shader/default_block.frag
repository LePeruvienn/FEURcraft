#version 330 core

uniform sampler2DArray uTextureArray;

in vec2 vVertexUV;
flat in uint vVertexLayerIndex;

out vec4 fFragColor;

void main()
{
	// ça c'est vraiment juste pour le test
	vec4 texColor = texture(uTextureArray, vec3(vVertexUV, vVertexLayerIndex));

	fFragColor = texColor;
}
