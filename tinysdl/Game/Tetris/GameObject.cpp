#include "GameObject.hpp"

namespace Tetris {
	GameObject::GameObject() :
		m_shader{ nullptr },
		m_isActive{ nullptr } 
	{

	}

	GameObject::GameObject(Shader* shader):
		m_shader{shader}
	{

	}

	GameObject::GameObject(GameObject& object):
		m_shader{object.m_shader},
		m_isActive{object.m_isActive}
	{

	}
	GameObject::~GameObject()
	{
	}
}
