#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GraphicsTesting.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Camera.h"

using namespace std;

int main()
{
    Window* gameWindow = new Window("Title", 500, 500);
    GLFWwindow* window = gameWindow->getWindow();

    Shader defaultShader("res/default.vert", "res/default.frag");

    // Vertices coordinates
    float vertices[] =
    {
        -1.0f,1.0f,0.0f, 1, 1, 1,
        -1.0f,-1.0f,0.0f, 1, 1, 1,
        1.0f,1.0f,0.0f, 1, 1, 1,
        1.0f,-1.0f,0.0f, 1, 1, 1,
        -1.0f,1.0f,-1.0f, 1, 1, 1,
        -1.0f,-1.0f,-1.0f, 1, 1, 1,
        1.0f,1.0f,-1.0f, 1, 1, 1,
        1.0f,-1.0f,-1.0f, 1, 1, 1
    };

    // Indices for vertices order
    unsigned int indices[] =
    {
        0, 2, 3, 0, 3, 1,
        2, 6, 7, 2, 7, 3,
        6, 4, 5, 6, 5, 7,
        4, 0, 1, 4, 1, 5,
        0, 4, 6, 0, 6, 2,
        1, 5, 7, 1, 7, 3,
    };

    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO(vertices, sizeof(vertices));
    ElementBuffer EBO(indices, sizeof(indices));

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

    float rotation = 0;

    VAO.Unbind();

    glm::quat rotation2 = glm::quatLookAt(glm::normalize(-glm::vec3(0.0f, -0.5f, -2.0f)), glm::vec3(0, 1, 0));
    float aspectRatio = gameWindow->getWidth() / gameWindow->getHeight();
    Camera cam(glm::vec3(0.0f, -0.5f, -2.0f), rotation2, 90, aspectRatio, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        gameWindow->clearScreen();

        // Use the shader program
        defaultShader.Activate();

        aspectRatio = gameWindow->getWidth() / gameWindow->getHeight();

        glm::mat4 model = glm::mat4(1.0f);

        rotation += gameWindow->deltaTime * 30;
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0,1,0));

        cam.UpdateViewMatrix();
        cam.UpdateProjectionMatrix();
        glm::mat4 viewProj = cam.GetViewProjectionMatrix();

        int modelLoc = glGetUniformLocation(defaultShader.GetRendererID(), "model");
        int viewLoc = glGetUniformLocation(defaultShader.GetRendererID(), "viewProj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewProj));

        // Bind the VAO
        //glBindVertexArray(VAO);

        VAO.Bind();

        // Draw the triangle
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        gameWindow->updateScreen();
    }

    glfwTerminate();
    return 0;
}
