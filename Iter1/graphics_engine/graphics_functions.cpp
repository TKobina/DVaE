#include "graphics_engine.h"

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}

void processInput(GLFWwindow* window, Properties _p)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_p.polyfill = !_p.polyfill;
		switch (_p.polyfill)
		{
		case true:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case false:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		}
	}

}