#include "Input.h"

float Input::m_mouseX;
float Input::m_mouseY;
Window* Input::m_window;
std::unordered_set<int> Input::m_keysPressed;

void Input::Init(Window* window)
{
	m_window = window;
	glfwSetKeyCallback(window->GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(window->GetWindow(), CursorMoveCallback);
}

bool Input::IsKeyPressed(int key, bool reset)
{
	if(m_keysPressed.find(key) != m_keysPressed.end())
	{
		if (reset)
			m_keysPressed.erase(key);

		return true;
	}

	return false;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		m_keysPressed.insert(key);
	}
	else if (action == GLFW_RELEASE)
	{
		m_keysPressed.erase(key);
	}
}

void Input::CursorMoveCallback(GLFWwindow* window, double xPos, double yPos)
{
	m_mouseX = xPos;
	m_mouseY = yPos;
}

