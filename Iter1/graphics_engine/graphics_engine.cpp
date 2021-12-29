#include "graphics_engine.h"
GraphicsEngine::GraphicsEngine() 
{
	properties = std::make_shared<Properties>();
	shapes = std::make_shared<Shapes>();

}

bool GraphicsEngine::initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
	if (!initialize_window()) return false;

	shader = std::make_unique<Shader>(Shader(properties->vShaderFName, properties->fShaderFName));

	if (!initialize_buffers()) return false;

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "\nMaximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	return true;
}

bool GraphicsEngine::initialize_window()
{
	window = glfwCreateWindow(properties->window_width, properties->window_height, properties->name, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "\nFailed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "\nFailed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(properties->cornerX, properties->cornerY, properties->viewport_width, properties->viewport_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return true;
}

bool GraphicsEngine::initialize_buffers()
{	
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &EBO);

	//TEMP
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes->triangle_e), shapes->triangle_e, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes->rectangle), shapes->triangle_r,  GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapes->rectangle_indices), shapes->rectangle_indices, GL_STATIC_DRAW);
	
	return true;
}


int GraphicsEngine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window, *properties);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->use();

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}