#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec2 aVertexUV;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;

out vec2 vVertexUV;

void main()
{
	vVertexUV = aVertexUV;

	gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aVertexPosition, 1.0);
}
