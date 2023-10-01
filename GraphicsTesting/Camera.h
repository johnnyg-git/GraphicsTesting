#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/common.hpp>

class Camera {
public:
	static glm::vec3 position;
	static glm::quat rotation;

	static float fieldOfView;
	static float aspectRatio;
	static float nearPlane;
	static float farPlane;

private:
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewProjectionMatrix;

public:
	static void Init(glm::vec3 pos, glm::quat rot, float fov, float ar, float np, float fp);

	static void UpdateViewMatrix();
	static void UpdateProjectionMatrix();

	static inline glm::mat4 GetViewMatrix() { return viewMatrix; }
	static inline glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	static inline glm::mat4 GetViewProjectionMatrix() { return viewProjectionMatrix; }
};