#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics_engine_data.h"
#include "shader.h"

class Escher 
{
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shapes> shapes;
	glm::mat4 model;

	std::vector<std::pair<int, glm::vec3>> objects; //holds coordinates for objects to be drawn

public:
	Escher(std::shared_ptr<Shader> _shader,
		std::shared_ptr<Shapes> _shapes);
	void escherize(unsigned int VAO);
};
