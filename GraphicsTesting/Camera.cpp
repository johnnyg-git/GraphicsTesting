#include "Camera.h"

glm::vec3 Camera::position;
glm::quat Camera::rotation;
float Camera::fieldOfView;
float Camera::aspectRatio;
float Camera::nearPlane;
float Camera::farPlane;

glm::mat4 Camera::viewMatrix;
glm::mat4 Camera::projectionMatrix;
glm::mat4 Camera::viewProjectionMatrix;

void Camera::Init(glm::vec3 pos, glm::quat rot, float fov, float ar, float np, float fp)
{
	position = pos;
	rotation = rot;
	fieldOfView = fov;
	aspectRatio = ar;
	nearPlane = np;
	farPlane = fp;

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}


void Camera::UpdateViewMatrix()
{
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -position);
	viewMatrix = rotationMatrix * translationMatrix;
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::UpdateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
	viewProjectionMatrix = projectionMatrix * viewMatrix;
}
