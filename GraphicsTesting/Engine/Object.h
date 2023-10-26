#pragma once

class Component;

class Object {
private:
	bool m_enabled;

	Object* m_parentObject;
	std::vector<Object*> m_children;
	std::vector<Component*> m_components;
};
