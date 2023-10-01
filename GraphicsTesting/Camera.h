#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/common.hpp>

class Camera {
public:
	glm::vec3 position;
	glm::quat rotation;

	float fieldOfView;
	float aspectRatio;
	float nearPlane;
	float farPlane;

private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewProjectionMatrix;

public:
	Camera(glm::vec3 pos, glm::quat rot, float fov, float ar, float np, float fp);

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	inline glm::mat4 GetViewMatrix() const { return viewMatrix; }
	inline glm::mat4 GetProjectionMatrix() const {return projectionMatrix; }
	inline glm::mat4 GetViewProjectionMatrix() const { return viewProjectionMatrix; }
};