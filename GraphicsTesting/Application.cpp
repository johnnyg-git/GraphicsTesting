#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Window.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Camera.h"

using namespace std;

bool goforwards;
bool gobackwards;
bool goright;
bool goleft;
bool goFast;

static double lastX = 0.0;
static double lastY = 0.0;
const double sensitivity = 0.05;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        goforwards = true;
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        goforwards = false;

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        gobackwards = true;
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        gobackwards = false;

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        goright = true;
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        goright = false;

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        goleft = true;
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        goleft = false;

    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
        goFast = true;
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        goFast = false;
}

static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {

    // Calculate the mouse movement since the last frame
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

    // Update the last mouse position for the next frame
    lastX = xpos;
    lastY = ypos;

    // Adjust camera's yaw and pitch based on mouse movement
    Camera::yaw += xoffset * sensitivity;
    Camera::pitch += yoffset * sensitivity;

    // Constrain pitch to avoid camera flipping
    if (Camera::pitch > 89.0) {
        Camera::pitch = 89.0;
    }
    if (Camera::yaw < -89.0) {
        Camera::yaw = -89.0;
    }
}

int main()
{
    Window* gameWindow = new Window("Title", 500, 500);
    GLFWwindow* window = gameWindow->getWindow();

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    Camera::Init(glm::vec3(0.0f, -0.5f, -2.0f), rotation2, 90, aspectRatio, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        gameWindow->clearScreen();

        defaultShader.Activate();

        aspectRatio = gameWindow->getWidth() / gameWindow->getHeight();

        glm::mat4 model = glm::mat4(1.0f);

        rotation += gameWindow->deltaTime * 30;
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0,1,0));

        Camera::UpdateViewMatrix();
        Camera::UpdateProjectionMatrix();
        glm::mat4 view = Camera::GetViewMatrix();
        glm::mat4 proj = Camera::GetProjectionMatrix();

        int modelLoc = glGetUniformLocation(defaultShader.GetRendererID(), "model");
        int viewLoc = glGetUniformLocation(defaultShader.GetRendererID(), "view");
        int projLoc = glGetUniformLocation(defaultShader.GetRendererID(), "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


        VAO.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        gameWindow->updateScreen();

        int mulitplier = goFast ? 2 : 1;

        if (goforwards) {
            Camera::position += glm::vec3(0, 0, 1 * gameWindow->deltaTime * mulitplier);
        }
        if (gobackwards) {
            Camera::position += glm::vec3(0, 0, -1 * gameWindow->deltaTime * mulitplier);
        }

        if (goright) {
            Camera::position += glm::vec3(-1 * gameWindow->deltaTime * mulitplier, 0, 0);
        }
        if (goleft) {
            Camera::position += glm::vec3(1 * gameWindow->deltaTime * mulitplier, 0, 0);
        }
    }

    glfwTerminate();
    return 0;
}
