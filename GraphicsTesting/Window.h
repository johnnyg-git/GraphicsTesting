#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

static void errorCallback(int error, const char* description);
static void windowResizeCallback(GLFWwindow* window, int width, int height);

class Window {
public:
	glm::vec4 backgroundColor;
	float deltaTime;
private:
	const char* title;
	float width;
	float height;
	float lastTime;

	GLFWwindow* window;

public:
	Window(const char* title, int width, int height);
	Window(const char* title, int width, int height, glm::vec4 backgroundColor);
	~Window();

	void clearScreen();
	void updateScreen();

	inline float getWidth() { return width; }
	inline float getHeight() { return height; }
	inline GLFWwindow* getWindow() { return window; }

private:
	bool init();

	friend void errorCallback(int error, const char* description);
	friend void windowResizeCallback(GLFWwindow* window, int width, int height);
};