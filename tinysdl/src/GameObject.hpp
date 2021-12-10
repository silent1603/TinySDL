#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Window.hpp"
#include <SDL2/SDL_image.h>

namespace tinysdl{
    
    class GameObject{
        private:
        int m_width;
        int m_height;
        SDL_Texture* m_texture;
        public:
        GameObject();
        GameObject(const std::string& path);
        ~GameObject();
        bool loadFromFile(const std::string& path);
        void free();
        void render(int x ,int y);
        int getWidth();
        int getHeight();
    };
}
#endif