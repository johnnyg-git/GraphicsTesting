#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicsTesting.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

using namespace std;

int main()
{
    Window* gameWindow = new Window("Title", 500, 500);
    GLFWwindow* window = gameWindow->getWindow();

    Shader defaultShader("res/default.vert", "res/default.frag");

    // Define the vertices of the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1,0,0,
         0.5f, -0.5f, 0.0f, 0,1,0,
         0.0f,  0.5f, 0.0f, 0,0,1
    };

    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO(vertices, sizeof(vertices));

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

    float rotation = 0;

    while (!glfwWindowShouldClose(window))
    {
        gameWindow->clearScreen();

        // Use the shader program
        defaultShader.Activate();

        float aspectRatio = gameWindow->getWidth() / gameWindow->getHeight();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        rotation += gameWindow->deltaTime * 30;
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0,1,0));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(defaultShader.GetRendererID(), "model");
        int viewLoc = glGetUniformLocation(defaultShader.GetRendererID(), "view");
        int projLoc = glGetUniformLocation(defaultShader.GetRendererID(), "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // Bind the VAO
        //glBindVertexArray(VAO);

        VAO.Bind();

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        gameWindow->updateScreen();
    }

    glfwTerminate();
    return 0;
}
