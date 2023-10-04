#include "Camera.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

glm::vec3 Camera::position;
float Camera::yaw;
float Camera::pitch;
float Camera::fieldOfView;
float Camera::aspectRatio;
float Camera::nearPlane;
float Camera::farPlane;

glm::mat4 Camera::viewMatrix;
glm::mat4 Camera::projectionMatrix;
glm::mat4 Camera::viewProjectionMatrix;

void Camera::Init(glm::vec3 pos, float pit, float ya, float fov, float ar, float np, float fp)
{
	position = pos;
	fieldOfView = fov;
	aspectRatio = ar;
	nearPlane = np;
	farPlane = fp;
	pitch = pit;
	yaw = ya;

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}


void Camera::UpdateViewMatrix()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	// Calculate the right and up vectors
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), front));
	glm::vec3 up = glm::cross(front, right);

	// Create the view matrix
	glm::mat4 rotationMatrix = glm::lookAt(position, position + front, up);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -position);
	viewMatrix = rotationMatrix * translationMatrix;
}

void Camera::UpdateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
}

void Camera::UpdateViewProjectionMatrix()
{
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::UpdateShader(Shader* shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->GetRendererID(), uniform), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
}
