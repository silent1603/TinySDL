#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include "Singleton.hpp"
namespace Tetris{
	class ResourceManager: Singleton <ResourceManager>
	{
		friend class Singleton<ResourceManager>;
	private:
		ResourceManager();
		~ResourceManager();
	public:
	};
}
#endif

