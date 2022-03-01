#ifndef APP_H
#define APP_H
#include "Log.hpp"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

namespace Tetris
{
    class App
    {
    private:
        std::string m_strTitle;
        int m_iWidth;
        int m_iHeight;
        SDL_GLContext m_glContext;
        SDL_Window* m_sdl2Window;
        bool m_isRunning = false;
    public:
        App(/* args */);
        App(std::string title, int width, int height);
        bool init();
        void update();
        void clean();
        ~App();
    };
}
#endif