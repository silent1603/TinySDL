#include "App.hpp"

namespace Tetris
{
#define MIN_SIZE_WIDTH 600
#define MIN_SIZE_HEIGHT 400
    App::App(/* args */) : m_strTitle("Tetris"),
                           m_iWidth(800),
                           m_iHeight(600)
    {
    }

    App::~App()
    {
    }

    App::App(std::string title, int width, int height) : m_strTitle(title),
                                                         m_iWidth(width),
                                                         m_iHeight(height)
    {
    }

    bool App::init()
    {
        // initiate SDL

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            TETRIS_ERROR("SDL init failed");
            return false;
        }

        // set OpenGL attributes
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        // set profile contetnt for opengl

        SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);

        std::string glsl_version = "#version 330";
#ifdef __APPLE__
        // GL 4.1 Core + GLSL 410
        glsl_version = "#version 410";
        SDL_GL_SetAttribute( // required on Mac OS
            SDL_GL_CONTEXT_FLAGS,
            SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif __linux__
        // GL 4.3 Core + GLSL 430
        glsl_version = "#version 430";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#elif _WIN32
        // GL 3.3 + GLSL 330
        glsl_version = "#version 330";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif

        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

       m_sdl2Window = SDL_CreateWindow(
            m_strTitle.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_iWidth,
            m_iHeight,
            window_flags);

        SDL_SetWindowMinimumSize(m_sdl2Window, MIN_SIZE_WIDTH, MIN_SIZE_HEIGHT);

        m_glContext = SDL_GL_CreateContext(m_sdl2Window);
        if (m_glContext == nullptr)
        {
            TETRIS_ERROR("Can't init GLContent");
        }
        SDL_GL_MakeCurrent(m_sdl2Window, m_glContext);

        // enable VSync
        SDL_GL_SetSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            TETRIS_ERROR("Couldn't initialize glad");
            return false;
        }


        glViewport(0, 0, m_iWidth, m_iHeight);
        

        glClearColor(0.0f, 0.0f,0.0f, 0.0f);

        return true;
    }

    void App::update()
    {
        m_isRunning = true;
        SDL_Event e;
        while (m_isRunning)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    m_isRunning = false;
                }
                else {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        m_isRunning = false;
                        break;
                    default:
                        break;
                    }
                }
                if (e.type == SDL_WINDOWEVENT)
                {
                    switch (e.window.event)
                    {
                    case SDL_WINDOWEVENT_RESIZED:
                        m_iWidth = e.window.data1;
                        m_iHeight = e.window.data2;
                        TETRIS_INFO( m_iWidth);
                        TETRIS_INFO( m_iHeight);
                        SDL_SetWindowSize(m_sdl2Window, m_iWidth, m_iHeight);
                        break;
                    default:
                        break;
                    }
                }
            }


            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            SDL_GL_SwapWindow(m_sdl2Window);
        }
    }

    void App::clean()
    {

        SDL_GL_DeleteContext(m_glContext);
        SDL_DestroyWindow(m_sdl2Window);
        SDL_Quit();
    }
}