#pragma once

struct Properties
{
	//NOT CURRENTLY IN USE
	char const* name = "LearnOpenGL";
	int window_width = 800;
	int window_height = 600;
	int viewport_width = window_width;
	int viewport_height = window_height;
	int cornerX = 0;
	int cornerY = 0;
};

struct Shapes
{
	float triangle_e[9] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
};

struct Shaders
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
};