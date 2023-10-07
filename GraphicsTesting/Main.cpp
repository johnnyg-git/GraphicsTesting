#include "Renderer/Renderer.h"

#include <iostream>

int main()
{
	Window* gameWindow = new Window("Graphics Testing", 500, 500);
	GLFWwindow* window = gameWindow->GetWindow();

	Input::Init(gameWindow);

	while (!glfwWindowShouldClose(window))
	{
		gameWindow->ClearWindow();

		if(Input::IsKeyPressed(GLFW_KEY_W, false))
		{
			std::cout << "W is pressed" << std::endl;
		}

		gameWindow->UpdateWindow();
	}

	return 0;
}