#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics_engine_data.h"
#include "shader.h"

struct EscherNode
{
	EscherNode(){}
	size_t ID = 0;
	size_t type = 0;
	glm::vec3 location;
	float angle = 0.0;
	float scale = 1.0;
	glm::vec3 color;
	float alpha;
};

struct EscherEdge
{

};

class Escher 
{
private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shapes> shapes;
	glm::mat4 model;

	std::vector<std::shared_ptr<EscherNode>> objects; //holds coordinates for objects to be drawn

public:
	void add_node(std::shared_ptr<EscherNode> _en);
	Escher(std::shared_ptr<Shader> _shader, std::shared_ptr<Shapes> _shapes);
	void draw(unsigned int VAO);
};
