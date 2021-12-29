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
#include <memory>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics_engine_data.h"
#include "shader.h"

//GLOBAL FUNCTIONS (graphics_functions.cpp)
void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
void processInput(GLFWwindow* window, Properties _p);

//CLASS METHODS (graphics_engine.cpp)
class GraphicsEngine
{
private:
	int success;
	int logLength = 512;
	char infoLog[512];

	//std::unique_ptr<Properties> properties;
	std::shared_ptr<Properties> properties;
	std::shared_ptr<Shapes> shapes;
	std::unique_ptr<Shader> shader;
	
	GLFWwindow* window;
	unsigned int VBOs[2];
	unsigned int VAOs[2];
	unsigned int EBO;

	bool initialize_window();
	bool initialize_buffers(); //VAO, VBA, EBO

public:
	GraphicsEngine();
	bool initialize();
	int run();
};