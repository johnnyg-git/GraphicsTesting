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
	wind->m_width = width;
	wind->m_height = height;
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

Window::Window(const char* title, int width, int height)
{
	m_title = title;
	m_width = width;
	m_height = height;
	backgroundColor = glm::vec4(0,0,0,1);
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

	if (!m_window) {
		glfwTerminate();
		std::cout << "Error: \nFailed to initalize window" << std::endl;
	}

	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetFramebufferSizeCallback(m_window, windowResizeCallback);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glDepthFunc(GL_LEQUAL);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

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
	deltaTime = currentTime - m_lastTime; m_lastTime = currentTime;

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
