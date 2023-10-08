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
	Mesh mesh("res/teapot.obj");

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 monkeyPos = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 3.0f, 10.0f),
										 glm::vec3(0.0f, 0.0f, 0.0f),
										 glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f),
															 500.0f / 500.0f,
															 0.1f,
															 100.0f);

	Mesh monkey("res/monkey.obj");

	Transform monkeyTransform(glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	while (!glfwWindowShouldClose(window))
	{
		gameWindow->ClearWindow();

		if(gameWindow->IsKeyPressed(GLFW_KEY_W, false))
		{
			std::cout << "W is pressed" << std::endl;
		}

		defaultShader.Use();

		defaultShader.SetMatrix4fv("model", glm::value_ptr(model));
		defaultShader.SetMatrix4fv("view", glm::value_ptr(view));
		defaultShader.SetMatrix4fv("projection", glm::value_ptr(projection));

		defaultShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		defaultShader.SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
		defaultShader.SetBool("useTexture", false);

		mesh.Render(defaultShader);

		monkeyTransform.Rotate(glm::vec3(0.0f, 10.0f * gameWindow->GetDeltaTime(), 0.0f));
		glm::mat4 matrix = monkeyTransform.GetLocalToWorldMatrix();
		defaultShader.SetMatrix4fv("model", glm::value_ptr(matrix));
		defaultShader.SetVec3("objectColor", 0.0f, 0.0f, 1.0f);
		monkey.Render(defaultShader);

		gameWindow->UpdateWindow();
	}

	delete gameWindow;

	return 0;
}