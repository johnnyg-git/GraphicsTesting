#include "Renderer/Renderer.h"

#include <iostream>
#include <ranges>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	Window* gameWindow = new Window("Graphics Testing", 500, 500);
	GLFWwindow* window = gameWindow->GetWindow();

	Shader defaultShader("res/default.vert", "res/default.frag");
	Mesh teapot("res/teapot.obj");
	Transform teapotTransform(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	Mesh monkey("res/monkey.obj");
	Transform monkeyTransform(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	Camera camera(gameWindow, glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 180.0f, 0.0f), 45.0f, 500.0f / 500.0f, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		gameWindow->ClearWindow();

		if(gameWindow->IsKeyPressed(GLFW_KEY_W, false))
		{
			std::cout << "W is pressed" << std::endl;
		}

		defaultShader.Use();

		glm::mat4 teapotMatrix = teapotTransform.GetLocalToWorldMatrix();
		defaultShader.SetMatrix4fv("model", glm::value_ptr(teapotMatrix));
		camera.UpdateShader(&defaultShader, "view", "projection");

		defaultShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		defaultShader.SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
		defaultShader.SetBool("useTexture", false);

		teapot.Render(defaultShader);

		monkeyTransform.Rotate(glm::vec3(0.0f, 10.0f * gameWindow->GetDeltaTime(), 0.0f));
		glm::mat4 monkeyMatrix = monkeyTransform.GetLocalToWorldMatrix();
		defaultShader.SetMatrix4fv("model", glm::value_ptr(monkeyMatrix));
		defaultShader.SetVec3("objectColor", 0.0f, 0.0f, 1.0f);
		monkey.Render(defaultShader);

		gameWindow->UpdateWindow();
	}

	delete gameWindow;

	return 0;
}