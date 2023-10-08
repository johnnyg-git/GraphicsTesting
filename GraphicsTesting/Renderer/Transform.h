#pragma once

#include <glm/glm.hpp>

class Transform
{
private:
	bool m_regenerateMatrix;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	glm::mat4 m_localToWorldMatrix;
	glm::mat4 m_worldToLocalMatrix;

public:
	Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	void Translate(glm::vec3 translation);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);

	glm::mat4 GetLocalToWorldMatrix();
	glm::mat4 GetWorldToLocalMatrix();

private:
	void UpdateLocalToWorldMatrix();
	void UpdateWorldToLocalMatrix();
};
