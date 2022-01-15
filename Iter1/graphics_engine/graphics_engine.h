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

#include "camera.h"
#include "escher.h"
#include "graphics_engine_data.h"
#include "shader.h"

class GraphicsEngine
{
private:
	std::shared_ptr<Properties> properties;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shapes> shapes;
	std::unique_ptr<Escher> escher;
	std::unique_ptr<Camera> camera;

	GLFWwindow* window;

	//unsigned int VBOs[2];
	//unsigned int VAOs[2];
	float deltaTime, lastFrame; 
	unsigned int VAO, VBO, EBO;
	unsigned int texture1, texture2;
	glm::mat4 model, view, projection;

	bool initialize();
	bool initialize_window();
	bool initialize_shader();
	bool initialize_buffers(); //VAO, VBA, EBO
	bool initialize_textures();
	bool set_texture_parameters(unsigned int _texture);

	void update_projection();
	void update_view();
	void draw();

	static void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
	static void mouse_callback(GLFWwindow* window, double _xpos, double _ypos);
	static void scroll_callback(GLFWwindow* window, double _xoffset, double _yoffset);
	void processInput(GLFWwindow* window);

public:
	GraphicsEngine();
	~GraphicsEngine();
	int run();
};