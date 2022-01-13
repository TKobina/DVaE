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

//Some of the code within the functions adapted from LearnOpenGL
//Joey DeVries
//https://github.com/JoeyDeVries/LearnOpenGL

#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//https://github.com/g-truc/glm/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics_engine_data.h"
#include "shader.h"

class GraphicsEngine
{
private:
	std::shared_ptr<Properties> properties;
	std::shared_ptr<Shapes> shapes;
	std::unique_ptr<Shader> shader;


	GLFWwindow* window;
	//unsigned int VBOs[2];
	//unsigned int VAOs[2];
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int texture1, texture2;

	bool initialize_window();
	bool initialize_buffers(); //VAO, VBA, EBO
	bool initialize_textures();
	bool set_texture_parameters(unsigned int _texture);

	static void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
	void processInput(GLFWwindow* window);

	void transform();
	void draw();

public:
	GraphicsEngine();
	bool initialize();
	int run();

};