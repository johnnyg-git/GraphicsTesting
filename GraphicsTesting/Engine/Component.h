#pragma once
#include <vector>
class Object;

class Component {
private:
	bool m_enabled;

	Object* m_parentObject;

public:
	std::vector<Component*>* GetChildren();

	void SetEnabled(bool enabled)
	{
		m_enabled = enabled;
	}

	bool GetEnabled() const
	{
		return m_enabled;
	}

	Object* GetParentObject() const
	{
		return m_parentObject;
	}

	virtual void Destroy()
	{
		delete this;
	}

	virtual void Start() = 0;
	virtual void Update() = 0;
};