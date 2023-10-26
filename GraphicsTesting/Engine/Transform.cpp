#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: m_position(position), m_rotation(rotation), m_scale(scale)
{
	m_regenerateMatrix = true;
}

glm::vec3 Transform::GetPosition() const
{
	return m_position;
}

glm::vec3 Transform::GetRotation() const
{
	return m_rotation;
}

glm::vec3 Transform::GetScale() const
{
	return m_scale;
}

glm::vec3 Transform::GetForward() const
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    return glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

glm::vec3 Transform::GetUp() const
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    return glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

glm::vec3 Transform::GetRight() const
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    return glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void Transform::SetPosition(glm::vec3 position)
{
	m_position = position;
	m_regenerateMatrix = true;
}

void Transform::SetRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
	m_regenerateMatrix = true;	
}

void Transform::SetScale(glm::vec3 scale)
{
	m_scale = scale;
	m_regenerateMatrix = true;
}

void Transform::Translate(glm::vec3 translation)
{
	m_position += translation;
	m_regenerateMatrix = true;
}

void Transform::Rotate(glm::vec3 rotation)
{
	m_rotation += rotation;
	m_regenerateMatrix = true;
}

void Transform::Scale(glm::vec3 scale)
{
	m_scale *= scale;
	m_regenerateMatrix = true;
}

glm::mat4 Transform::GetLocalToWorldMatrix()
{
	if(m_regenerateMatrix) 
	{
		UpdateLocalToWorldMatrix();
		UpdateWorldToLocalMatrix();
		m_regenerateMatrix=false;
	}

	return m_localToWorldMatrix;
}

glm::mat4 Transform::GetWorldToLocalMatrix()
{
	if(m_regenerateMatrix) 
	{
		UpdateLocalToWorldMatrix();
		UpdateWorldToLocalMatrix();
		m_regenerateMatrix=false;
	}

	return m_worldToLocalMatrix;
}

void Transform::UpdateLocalToWorldMatrix()
{
	glm::mat4 model = glm::mat4(1.0f); // Initialize an identity matrix

    // Apply translation
    model = glm::translate(model, m_position);

    // Apply rotation (in Euler angles)
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Apply scale
    model = glm::scale(model, m_scale);

	m_localToWorldMatrix = model;
}

void Transform::UpdateWorldToLocalMatrix()
{
	m_worldToLocalMatrix = glm::inverse(m_localToWorldMatrix);
}
