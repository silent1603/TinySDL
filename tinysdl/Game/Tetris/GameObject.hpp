#ifndef SHADER_H
#define SHADER_h
#include "Shader.hpp"
namespace Tetris {
	class GameObject
	{
	public:
		GameObject();
		GameObject(Shader* shader);
		GameObject(GameObject& object);
		virtual void update() = 0;
		virtual void render() = 0;
		inline bool isActive() { return m_isActive;}
		inline bool setShader(Shader* shader) { m_shader = shader; }
		virtual ~GameObject();
	protected:
		Shader* m_shader;
		bool m_isActive;
	};
}
#endif

