#include "Window.hpp"
#include <SDL2/SDL_image.h>

namespace tinysdl{
    SDL_Renderer* g_renderer = nullptr; 
    SDL_Window* g_window = nullptr;

    Window::Window(int x ,int y,int width , int height ,const std::string& name): m_x(x),m_y(y), m_width(width),m_height(height),m_title(name),m_is_running(false)
    {

    }

    Window::~Window()
    {
       quit();
    }

    bool Window::init()
    {
        bool success = true;
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cout << " SDL count not initlize ! SDL_Error: " << SDL_GetError() << '\n';
            success = false;
        }else{
            g_window = SDL_CreateWindow(m_title.c_str(),m_x,m_y,m_width,m_height,SDL_WINDOW_SHOWN);
            if(g_window == nullptr)
            {
                std::cout << "Window could not be created! SDL_Error: "<< SDL_GetError()  << '\n';
                success = false;
            }else{
                g_renderer = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
                if(g_renderer == nullptr)
                {
                    std::cout << "Renderer cound not be created! SDL_Error: "<< SDL_GetError() << '\n';
                }
                else{
                    int imgFlags = IMG_INIT_PNG;
                    SDL_SetRenderDrawColor(g_renderer,0xFF,0xFF,0xFF,0xFF);
                    if(!(IMG_Init(imgFlags)) & imgFlags)
                    {
                       std::cout << "SDL image could not inittialize ? SDL_image Error: %s\n" << IMG_GetError() << '\n';
                       success =false;
                    }
                }
 
            }
        }
        return success;
    }

    void Window::update()
    {
        SDL_Event e;
        while(m_is_running)
        {
            while(SDL_PollEvent(&e) != NULL)
            {
                if(e.type == SDL_QUIT)
                {
                    m_is_running = false;
                }else if(e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        /* code */
                        m_is_running = false;
                        break;
                    
                    }
                }
            }
            SDL_RenderClear(g_renderer);
            SDL_RenderPresent(g_renderer);
        }
    }

    void Window::quit()
    {
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        g_renderer = nullptr;
        g_window = nullptr;
        IMG_Quit();
        SDL_Quit();
    }

    bool loadMedia()
    {
        bool success = true;
        return success;
    }
}