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
	const char* m_title;
	float m_width;
	float m_height;
	float m_lastTime;

	GLFWwindow* m_window;

public:
	Window(const char* title, int width, int height);
	Window(const char* title, int width, int height, glm::vec4 backgroundColor);
	~Window();

	void clearScreen();
	void updateScreen();

	inline float getWidth() const { return m_width; }
	inline float getHeight() const { return m_height; }
	inline GLFWwindow* getWindow() const { return m_window; }

private:
	bool init();

	friend void errorCallback(int error, const char* description);
	friend void windowResizeCallback(GLFWwindow* window, int width, int height);
};