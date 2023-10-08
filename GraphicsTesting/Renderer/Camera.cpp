#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::map<GLFWwindow*, Camera*> Camera::s_cameras;

void CameraResizeCallback(GLFWwindow* window, int width, int height) {
	if(Camera::s_cameras.find(window) != Camera::s_cameras.end()) 
	{
		Camera* cam = Camera::s_cameras[window];
		cam->SetAspectRatio((float)width / (float)height);
		cam->UpdateProjectionMatrix();
	}
}

Camera::Camera(Window* renderWindow, glm::vec3 pos, glm::vec3 rot, float fov, float aspectRatio, float nearPlane, float farPlane) 
	: m_transform(pos, rot, glm::vec3(1.0f)), m_fieldOfView(fov), m_aspectRatio(aspectRatio), m_nearPlane(nearPlane), m_farPlane(farPlane), m_renderWindow(renderWindow) 
{
	s_cameras.insert(std::pair<GLFWwindow*, Camera*>(m_renderWindow->GetWindow(), this));
	m_renderWindow->AddResizeCallback(CameraResizeCallback);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

Camera::~Camera() {
	m_renderWindow->RemoveResizeCallback(CameraResizeCallback);
}

void Camera::UpdateViewMatrix() {
	viewMatrix = glm::lookAt(m_transform.GetPosition(), m_transform.GetPosition() + m_transform.GetForward(), m_transform.GetUp());
}

void Camera::UpdateProjectionMatrix() {
	projectionMatrix = glm::perspective(glm::radians(m_fieldOfView), m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::UpdateShader(Shader* shader, const char* viewUniform, const char* projectionUniform, const char* viewLocationUniform) {
	shader->Use();
	shader->SetMatrix4fv(viewUniform, glm::value_ptr(viewMatrix));
	shader->SetMatrix4fv(projectionUniform, glm::value_ptr(projectionMatrix));

	if(viewLocationUniform != "")
	{
		shader->SetVec3(viewLocationUniform, m_transform.GetPosition().x, m_transform.GetPosition().y, m_transform.GetPosition().z);
	}
}
