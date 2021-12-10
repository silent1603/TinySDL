#include "GameObject.hpp"

namespace tinysdl{
    GameObject::GameObject():m_width{0},m_height{0},m_texture{nullptr}
    {

    }   
    GameObject::GameObject(const std::string& path)
    {
        loadFromFile(path);
    }
    GameObject::~GameObject()
    {
        free();
    
    }
    bool GameObject::loadFromFile(const std::string& path)
    {
        free();
        SDL_Texture* newTexture =nullptr;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if(loadedSurface == nullptr)
        {
            std::cout << "Unable to load image :" << path.c_str() << " ! SDL_image Error: "<<IMG_GetError() << '\n';
        }else{
            SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
            newTexture = SDL_CreateTextureFromSurface(tinysdl::g_renderer,loadedSurface);
            if(newTexture == nullptr)
            {
                 std::cout <<  "Unable to create texture from "<< path.c_str() <<  "SDL Error: " << SDL_GetError() <<'\n';  
            }else{
                m_width = loadedSurface->w;
                m_height = loadedSurface->h;
            }
            SDL_FreeSurface(loadedSurface);
        }
        m_texture = newTexture;
        return m_texture != nullptr;
    }

    void GameObject::render(int x , int y)
    {
        SDL_Rect renderQuad = {x,y,m_width,m_height};
        SDL_RenderCopy(tinysdl::g_renderer,m_texture,nullptr,&renderQuad);
    }

    void GameObject::free()
    {
        if(m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;   
            m_height = 0;
            m_width = 0;     
        }
    }

    int GameObject::getWidth()
    {
        return m_width;
    }
    int GameObject::getHeight()
    {
        return m_height;
    }
}