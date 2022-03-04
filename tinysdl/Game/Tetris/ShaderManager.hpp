#ifndef SHADERMANAGER_HPP
#define SHADERMAANGER_HPP
#include <vector>
#include <memory>
#include "Singleton.hpp"
#include "Shader.hpp"
namespace Tetris {
	class ShaderManager:Singleton<ShaderManager>
	{
		friend class Singleton<ShaderManager>;
	public:
		ShaderManager();
		~ShaderManager();
	private:
		std::vector<std::shared_ptr<Shader>> m_aShaders;
	};
}
#endif
