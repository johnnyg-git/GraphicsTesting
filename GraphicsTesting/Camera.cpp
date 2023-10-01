#include "Camera.h"
Camera::Camera(glm::vec3 pos, glm::quat rot, float fov, float ar, float np, float fp)
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
