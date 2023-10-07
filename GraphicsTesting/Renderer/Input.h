#pragma once
#include <unordered_map>
#include <unordered_set>

#include "Window.h"


class Input
{
public:
	static void Init(Window* window);

	static bool IsKeyPressed(int key, bool reset = true);
	static float GetMouseX() { return m_mouseX; }
	static float GetMouseY() { return m_mouseY; }

private:
	static float m_mouseX, m_mouseY;
	static Window* m_window;
	static std::unordered_set<int> m_keysPressed;

	static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void CursorMoveCallback(GLFWwindow* window, double xPos, double yPos);
};