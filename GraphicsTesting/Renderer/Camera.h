#pragma once
#include <map>

#include "Window.h"
#include "Transform.h"
#include "Shader.h"

static void CameraResizeCallback(GLFWwindow* window, int width, int height);

class Camera {
private:
	float m_fieldOfView;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;

	Window* m_renderWindow;
	Transform m_transform;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	static std::map<GLFWwindow*, Camera*> s_cameras;

public:
	Camera(Window* renderWindow, glm::vec3 pos, glm::vec3 rot, float fov, float aspectRatio, float nearPlane, float farPlane);
	~Camera();

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	void UpdateShader(Shader* shader, const char* viewUniform, const char* projectionUniform, const char* viewLocationUniform = "");

	inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }

	inline Transform* GetTransform() { return &m_transform; }
	inline Window* GetRenderWindow() { return m_renderWindow; }
	inline float GetFieldOfView() { return m_fieldOfView; }
	inline float GetAspectRatio() { return m_aspectRatio; }
	inline float GetNearPlane() { return m_nearPlane; }
	inline float GetFarPlane() { return m_farPlane; }

	inline void SetFieldOfView(float fov) { m_fieldOfView = fov; UpdateProjectionMatrix(); }
	inline void SetAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; UpdateProjectionMatrix(); }
	inline void SetNearPlane(float nearPlane) { m_nearPlane = nearPlane; UpdateProjectionMatrix(); }
	inline void SetFarPlane(float farPlane) { m_farPlane = farPlane; UpdateProjectionMatrix(); }

private:
	friend void CameraResizeCallback(GLFWwindow* window, int width, int height);
};