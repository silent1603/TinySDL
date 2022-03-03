#ifndef SHADER_H
#define SHADER_h
#include "Shader.hpp"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
protected:
	Shader* m_shader;
	bool m_isActive;
};
#endif

