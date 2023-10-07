﻿#include <glm/glm.hpp>
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

// Vertices coordinates
float lightVertices[] =
{
    -0.1f, -0.1f,  0.1f, 
    -0.1f, -0.1f, -0.1f, 
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f, 
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f, 
     0.1f,  0.1f,  0.1f
};

// Indices for vertices order
unsigned int lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

// Vertices coordinates
float vertices[] =
{ //     COORDINATES     /        COLORS          /  NORMALS       //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 -0.8f, 0.5f,  0.0f, // Left Side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.5f, -0.8f, // Non-facing side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.5f, -0.8f, // Non-facing side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.0f, 0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.8f, 0.5f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.8f, 0.5f,  0.0f, // Right side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.8f, 0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.5f,  0.8f, // Facing side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
unsigned int indices[] =
{
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};

float planeVertices[] = 
{
    -1.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    1.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
};

unsigned int planeIndices[] = 
{
	0, 1, 2,
    3, 4, 5
};

int mainOld()
{
    Window* gameWindow = new Window("Title", 500, 500);
    GLFWwindow* window = gameWindow->getWindow();

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::mat4 lightPos = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 3.0f, 0.0f));

    Shader defaultShader("res/default.vert", "res/default.frag");

    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO(vertices, sizeof(vertices));
    ElementBuffer EBO(indices, sizeof(indices));

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 9 * sizeof(float), 0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));

    float rotation = 0;

    VAO.Unbind();

    VertexArray planeVAO;
    planeVAO.Bind();

    VertexBuffer planeVBO(planeVertices, sizeof(planeVertices));
    ElementBuffer planeEBO(planeIndices, sizeof(planeIndices));

    planeVAO.LinkAttrib(planeVBO, 0, 3, GL_FLOAT, 9 * sizeof(float), 0);
    planeVAO.LinkAttrib(planeVBO, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    planeVAO.LinkAttrib(planeVBO, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));

    planeVAO.Unbind();

    Shader lightShader("res/light.vert", "res/light.frag");
    VertexArray lightVAO;
    lightVAO.Bind();

    VertexBuffer lightVBO(lightVertices, sizeof(lightVertices));
    ElementBuffer lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
    lightVAO.Unbind();

    float aspectRatio = gameWindow->getWidth() / gameWindow->getHeight();
    Camera::Init(gameWindow, glm::vec3(0.0f, .5f, -2.0f), 0,0, 90, aspectRatio, 0.1f, 100.0f);

    defaultShader.Activate();
    glUniform4f(glGetUniformLocation(defaultShader.GetRendererID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(defaultShader.GetRendererID(), "lightPos"), 1.0f, 3.0f, 0.0f);
    lightShader.Activate();
    glUniform4f(glGetUniformLocation(lightShader.GetRendererID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    while (!glfwWindowShouldClose(window))
    {
        gameWindow->clearScreen();

        defaultShader.Activate();

        aspectRatio = gameWindow->getWidth() / gameWindow->getHeight();

        glm::mat4 model = glm::mat4(1.0f);

        rotation += gameWindow->deltaTime * 30;
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0,1,0));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

        Camera::UpdateViewMatrix();
        Camera::UpdateProjectionMatrix();
        Camera::UpdateViewProjectionMatrix();

        Camera::UpdateShader(&defaultShader, "viewProj");

        int modelLoc = glGetUniformLocation(defaultShader.GetRendererID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(defaultShader.GetRendererID(), "camPos"), Camera::position.x, Camera::position.y, Camera::position.z);

        VAO.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        planeVAO.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();

        Camera::UpdateShader(&lightShader, "viewProj");

        int modelLoc2 = glGetUniformLocation(lightShader.GetRendererID(), "model");
        glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(lightPos));

        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        gameWindow->updateScreen();

        glm::vec3 front;
        front.x = cos(glm::radians(Camera::yaw) * cos(glm::radians(Camera::pitch)));
        front.y = sin(glm::radians(Camera::pitch));
        front.z = sin(glm::radians(Camera::yaw)) * cos(glm::radians(Camera::pitch));
        front = glm::normalize(front);

        glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), front));
        glm::vec3 up = glm::cross(front, right);

        int mulitplier = goFast ? 2 : 1;

        if (goforwards) {
            Camera::position += gameWindow->deltaTime * mulitplier* front;
        }
        if (gobackwards) {
            Camera::position += gameWindow->deltaTime * mulitplier * -front;
        }

        if (goright) {
            Camera::position += gameWindow->deltaTime * mulitplier * -right;
        }
        if (goleft) {
            Camera::position += gameWindow->deltaTime * mulitplier* right;
        }
    }

    glfwTerminate();
    return 0;
}