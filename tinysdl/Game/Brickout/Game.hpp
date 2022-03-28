#ifndef GAME_HPP
#define GAME_HPP
#include <glad/glad.h>
#include <sdl2/SDL.h>
namespace Brickout{

    enum class GameState{
        GAME_WIN,
        GAME_MENU,
        GAME_ACTIVE
    };

    class Game{
        public:
        GameState meGameStaste;
        int miWidth, miHeight;
        bool  mbKeys[1024];
        ~Game();
        Game(int width, int height);
        void Init();
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
    };
}
#endif