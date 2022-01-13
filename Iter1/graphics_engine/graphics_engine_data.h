#pragma once

struct Properties
{
	//NOT CURRENTLY IN USE
	char const* name = "DVaE";
	int window_width = 800;
	int window_height = 600;
	int viewport_width = window_width;
	int viewport_height = window_height;
	int cornerX = 0;
	int cornerY = 0;
	bool polyfill = true;

	char const* vShaderFName = "graphics_engine/shader.vs";
	char const* fShaderFName = "graphics_engine/shader.fs";
	char const* textureFName1 = "resources/fern.jpg";
	char const* textureFName2 = "resources/sunrise.png";
};

struct Shapes
{
	float triangle_e[18] =
	{
		-0.5f, -0.5f, 0.0f, //1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, //0.0f, 1.0f, 0.1f,
		0.0f, 0.5f, 0.0f//, 0.0f, 0.0f, 1.0f
	};

	float triangle_r[18] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};


	float rectangle[32] = 
	{
		// positions // colors // texture coords
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f // top left
	};

	unsigned int rectangle_indices[6] =
	{
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};
};

/*
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
*/