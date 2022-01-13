#include "graphics_engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

	if (!initialize_textures()) return false;
	
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "\nFailed to initialize GLAD" << std::endl;
		return false;
	}

	//glViewport(properties->cornerX, properties->cornerY, properties->viewport_width, properties->viewport_height);
	//glEnable(GL_DEPTH_TEST);
	return true;
}

bool GraphicsEngine::initialize_buffers()
{	
	//glGenVertexArrays(2, VAOs);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes->rectangle), shapes->rectangle, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapes->rectangle_indices), shapes->rectangle_indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	return true;
}

bool GraphicsEngine::initialize_textures()
{
	int width, height, nrChannels;
	unsigned char* data;

	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture1);
	set_texture_parameters(texture1);

	data = stbi_load(properties->textureFName1, &width, &height, &nrChannels, 0);

	if (!data)
	{
		std::cout << "\nFailed to load texture1";
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	//second texture
	glGenTextures(1, &texture2);
	set_texture_parameters(texture2);
	data = stbi_load(properties->textureFName2, &width, &height, &nrChannels, 0);

	if (!data)
	{
		std::cout << "\nFailed to load texture2";
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	shader->use();
	shader->setInt("texture1", 0);
	shader->setInt("texture2", 1);

	return true;
}

bool GraphicsEngine::set_texture_parameters(unsigned int _texture)
{
	glBindTexture(GL_TEXTURE_2D, _texture);

	//set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void GraphicsEngine::transform()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //translate view backward

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


}

void GraphicsEngine::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	shader->use();
	transform();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int GraphicsEngine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}


void GraphicsEngine::framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}

void GraphicsEngine::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		properties->polyfill = !properties->polyfill;
		switch (properties->polyfill)
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