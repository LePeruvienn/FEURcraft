#version 330 core

layout(location = 0) in vec3 aVertexPosition;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;

out vec4 vColor;

void main()
{
	vColor = vec4(1.f, 0.f, 0.f, 1.f);

	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aVertexPosition, 1.0);
}
