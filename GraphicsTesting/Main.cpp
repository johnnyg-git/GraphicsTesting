#include "Renderer/Renderer.h"

int main()
{
	Window* gameWindow = new Window("Graphics Testing", 500, 500);
	GLFWwindow* window = gameWindow->GetWindow();

	while (!glfwWindowShouldClose(window))
	{
		gameWindow->ClearWindow();

		gameWindow->UpdateWindow();
	}

	return 0;
}