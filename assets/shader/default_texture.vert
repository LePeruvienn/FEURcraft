#version 330 core

layout(location = 0) in vec3 aVertexPosition;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;

out vec3 vVertexPosition;

void main()
{
	vVertexPosition = aVertexPosition;

	// En fait j'ai un bug je crois dans le format de mes matrices,
	// ce qui fait que je doit faire les multipliation à l'envers,
	// mais en fait je comprend pas le bug, force à vous 🫡
	//
	// gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aVertexPosition, 1.0); // PAS OK

	gl_Position = vec4(aVertexPosition, 1.f) * uModelMatrix * uViewMatrix * uProjMatrix; // OK!
}
