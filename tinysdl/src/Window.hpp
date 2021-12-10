#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
namespace tinysdl{
    extern SDL_Renderer* g_renderer;
    extern SDL_Window* g_window;
    class Window{
        private:
        int m_width;
        int m_height;
        int m_x;
        int m_y;
        std::string m_title;
        bool m_is_running;
        public: 
        Window(int x = 0,int y = 0,int width = 800 , int height  = 600 ,const std::string& name = "window");
        ~Window();
        bool init();
        void update();
        void quit();
        bool loadMedia();
    };
}
#endif