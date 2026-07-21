#version 330 core

layout(location = 0) in vec3 aVertexPosition;

out vec4 vColor;

void main()
{
	vColor = vec4(1.f, 0.f, 0.f, 1.f);

	gl_Position = vec4(aVertexPosition, 1.f);
}
