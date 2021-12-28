/*
0. copy vertices array in a buffer for OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

1. set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

2. use shader program to render an object
	glUseProgram(shaderProgram);

3. draw the object
	someOpenGLFunctionThatDrawsOurTriangle();
*/
#pragma once
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics_engine_data.h"

//GLOBAL METHODS (graphics_engine_methods.cpp)
void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
void processInput(GLFWwindow* window);

//CLASS METHODS (graphics_engine.cpp)
class GraphicsEngine
{
private:
	int success;
	int logLength = 512;
	char infoLog[512];

	Properties properties;
	Shapes shapes;
	Shaders shaders;
	
	GLFWwindow* window;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	bool initialize_window();
	bool initialize_buffers();
	//bool initialize_vao();
	bool initialize_shaders();
	//bool fill_buffers();
	bool link_attributes();

public:
	//GraphicsEngine();
	bool initialize();
	int run();
};