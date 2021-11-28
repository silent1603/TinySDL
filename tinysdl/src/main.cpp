#include "main.hpp"

int windowWidth = 1280,
    windowHeight = 720;

int main(int argc, char *argv[])
{
    // ...
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL count not initialize 1 SDL_Error : \n" << SDL_GetError() << '\n';
    }else{
        window = SDL_CreateWindow("Screen",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: "<< SDL_GetError()  << '\n';
        }else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface,nullptr,SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}