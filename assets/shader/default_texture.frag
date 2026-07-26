#version 330 core

uniform sampler2D uTexture;

in vec3 vVertexPosition;
out vec4 fFragColor;

void main()
{
	// ça c'est vraiment juste pour le test
	vec4 texColor = texture(uTexture, vVertexPosition.xy);

	fFragColor = texColor;
}
