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
	bool polyfill = true;

	char const* vShaderFName = "graphics_engine/shader.vs";
	char const* fShaderFName = "graphics_engine/shader.fs";
};

struct Shapes
{
	float triangle_e[9] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	float triangle_r[9] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};


	float rectangle[12] = 
	{
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};

	unsigned int rectangle_indices[6] =
	{
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};
};

struct Shaders
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.25);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(1.0f, 0.5f, 0.2f, 0.25f);\n"
		"}\0";
};