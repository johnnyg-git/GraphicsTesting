#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Callbacks
static void WindowErrorCallback(int error, const char* description);
static void WindowResizeCallback(GLFWwindow* window, int width, int height);

// Window class
// This class is used to create a window and handle the window's events
class Window {
public:
	// Background color of the window, set when cleared
	glm::vec4 backgroundColor;
private:
	// Title of the window, set at construction
	const char* m_title;
	// Delta time of the window, updated every frame
	double m_deltaTime;
	// Width and height of the window, set at construction
	float m_width, m_height;
	// Last time the window was updated
	float m_lastTime;

	// Pointer to the GLFWWindow instance
	GLFWwindow* m_window;

public:
	// Constructors and destructor
	Window(const char* title, int width, int height);
	Window(const char* title, int width, int height, glm::vec4 backgColor);
	~Window();

	// Clears the window, clears color and depth buffer and fills with backgroundColor
	void ClearWindow() const;
	// Updates the window, swaps buffers and polls events
	void UpdateWindow();

	// Getters
	inline double GetDeltaTime() const { return m_deltaTime; }
	inline float GetWidth() const { return m_width; }
	inline float GetHeight() const { return m_height; }
	inline GLFWwindow* GetWindow() const { return m_window; }

private:
	// Initializes the window
	bool Init();

	// Friends
	friend void WindowErrorCallback(int error, const char* description);
	friend void WindowResizeCallback(GLFWwindow* window, int width, int height);
};
