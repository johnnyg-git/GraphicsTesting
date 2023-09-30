// GraphicsTesting.cpp : Defines the entry point for the application.
//

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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Create a Vertex Array Object (VAO) and a Vertex Buffer Object (VBO)
    /*GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);*/

    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO(vertices, sizeof(vertices));

    // Configure vertex attributes
    /*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0); */

    VAO.LinkVertexBuffer(VBO, 0);

    while (!glfwWindowShouldClose(window))
    {
        gameWindow->clearScreen();

        // Use the shader program
        defaultShader.Activate();

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
