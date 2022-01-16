#include "graphics_engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GraphicsEngine::GraphicsEngine()
{
	srand(static_cast<unsigned>(time(0)));
	properties = std::make_shared<Properties>();
	shapes = std::make_shared<Shapes>();
	camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f));
	camera->lastX = properties->window_width / 2;
	camera->lastY = properties->window_height / 2;
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	deltaTime = 0.0f;
	lastFrame = 0.0f;

	initialize();
}

GraphicsEngine::~GraphicsEngine()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	//glfwDestroyWindow(window);
}

bool GraphicsEngine::initialize()
{
	if (!initialize_window()) return false;
	if (!initialize_shader()) return false;
	if (!initialize_buffers()) return false;
	if (!initialize_textures()) return false;
	
	escher = std::make_unique<Escher>(shader, shapes);
	return true;
}

bool GraphicsEngine::initialize_window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(properties->window_width, properties->window_height, properties->name, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "\nFailed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "\nFailed to initialize GLAD" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

bool GraphicsEngine::initialize_buffers()
{	
	//glGenVertexArrays(2, VAOs);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(shapes->rectangle), shapes->rectangle, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes->cube), shapes->cube, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shapes->rectangle_indices), shapes->rectangle_indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return true;
}

bool GraphicsEngine::initialize_shader()
{
	shader = std::make_shared<Shader>(Shader(properties->vShaderFName, properties->fShaderFName));

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

void GraphicsEngine::update_projection()
{
	projection = glm::perspective(
		glm::radians(camera->Zoom), (float)properties->window_width / (float)properties->window_height,
		0.1f, 100.0f);

	shader->setMat4("projection", projection);
}

void GraphicsEngine::update_view()
{
	view = camera->GetViewMatrix();
	shader->setMat4("view", view);
}

void GraphicsEngine::draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	shader->use();
	update_projection();
	update_view();
	escher->draw(VAO);

}

int GraphicsEngine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}

//CALLBACK AND INPUT PROC'ING FUNCTIONS
void GraphicsEngine::framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	GraphicsEngine* GE = (GraphicsEngine*)glfwGetWindowUserPointer(window);
	glViewport(0, 0, _width, _height);
}

void GraphicsEngine::mouse_callback(GLFWwindow* window, double _xpos, double _ypos)
{
	GraphicsEngine* GE = (GraphicsEngine *)glfwGetWindowUserPointer(window);

	float xpos = static_cast<float>(_xpos);
	float ypos = static_cast<float>(_ypos);

	float xoffset = _xpos - GE->camera->lastX;
	float yoffset = GE->camera->lastY - _ypos; // reversed since y-coordinates go from bottom to top

	GE->camera->lastX = _xpos;
	GE->camera->lastY = _ypos;

	GE->camera->ProcessMouseMovement(xoffset, yoffset);
}

void GraphicsEngine::scroll_callback(GLFWwindow* window, double _xoffset, double _yoffset)
{
	GraphicsEngine* GE = (GraphicsEngine*)glfwGetWindowUserPointer(window);	
	float zoom = GE->camera->Zoom - float(_yoffset);
	if (zoom < 1.0f) 
		zoom = 1.0f;
	if (zoom > 45.0f) 
		zoom = 45.0f;
	GE->camera->Zoom = zoom;
}

void GraphicsEngine::processInput(GLFWwindow* window)
{
	GraphicsEngine* GE = (GraphicsEngine*)glfwGetWindowUserPointer(window);

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

	//movement
	float deltaTime = GE->deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(UPWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWNWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFTWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHTWARD, deltaTime);
}