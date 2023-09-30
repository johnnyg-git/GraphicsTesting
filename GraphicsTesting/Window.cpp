#include "Window.h"
#include <iostream>

void errorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, (float)width, (float)height);
	Window* wind = (Window*)glfwGetWindowUserPointer(window);
	wind->width = width;
	wind->height = height;
}

Window::Window(const char* title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->backgroundColor = glm::vec4(0,0,0,1);
	if (!init()) {
		glfwTerminate();
	}
}

Window::Window(const char* title, int width, int height, glm::vec4 backgroundColor)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->backgroundColor = backgroundColor;
	if (!init()) {
		glfwTerminate();
	}
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		glfwTerminate();
		std::cout << "Error: \nFailed to initalize window" << std::endl;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	return true;
}

void Window::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
}

void Window::updateScreen()
{
	double currentTime = glfwGetTime(); 
	deltaTime = currentTime - lastTime; lastTime = currentTime;

	glfwPollEvents();
	glfwSwapBuffers(window);
}
