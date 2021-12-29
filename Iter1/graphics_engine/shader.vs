#version 330 core
layout (location = 0) in vec3 aPos; //position has attribute position 0

out vec3 vertexColor; //send color output to fragment shader

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vertexColor = vec3(0.5, 0.0, 0.0);
}