#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/common.hpp>
#include "Shader.h"

class Camera {
public:
	static glm::vec3 position;
	static float yaw;
	static float pitch;

	static float fieldOfView;
	static float aspectRatio;
	static float nearPlane;
	static float farPlane;

private:
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewProjectionMatrix;

public:
	static void Init(glm::vec3 pos, float pitch, float yaw, float fov, float ar, float np, float fp);

	static void UpdateViewMatrix();
	static void UpdateProjectionMatrix();
	static void UpdateViewProjectionMatrix();
	static void UpdateShader(Shader* shader, const char* uniform);

	static inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	static inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	static inline glm::mat4 GetViewProjectionMatrix() { return viewProjectionMatrix; }
};