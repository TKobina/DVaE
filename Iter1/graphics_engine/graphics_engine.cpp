#include "graphics_engine.h"
//===========================GRAPHICS ENGINE METHODS===============================
//GraphicsEngine::GraphicsEngine() {}

bool GraphicsEngine::initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!initialize_window()) return false;
	if (!initialize_buffers()) return false;
	if (!initialize_shaders()) return false;
	if (!link_attributes()) return false;
	return true;
}

bool GraphicsEngine::initialize_window()
{
	window = glfwCreateWindow(properties.window_width, properties.window_height, properties.name, NULL, NULL);

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

	glViewport(properties.cornerX, properties.cornerY, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return true;
}

bool GraphicsEngine::initialize_buffers()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(shapes.triangle_e), shapes.triangle_e, GL_STATIC_DRAW);
	return true;
}

bool GraphicsEngine::initialize_shaders()
{
	//VERTEX
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaders.vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, logLength, NULL, infoLog);
		std::cout << "\nERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
		std::cout << infoLog << std::endl;

		return false;
	}

	//FRAGMENT
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaders.fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, logLength, NULL, infoLog);
		std::cout << "\nERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
		std::cout << infoLog << std::endl;

		return false;
	}

	//PROGRAM
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, logLength, NULL, infoLog);
		std::cout << "\nERROR::SHADER::PROGRAM::LINKING_FAILED\n";
		std::cout << infoLog << std::endl;

		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}


//bool GraphicsEngine::fill_buffers() { return true; }

bool GraphicsEngine::link_attributes()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return true;
}

int GraphicsEngine::run()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


//==========================GLOBAL GRAPHICS METHODS================================
void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
