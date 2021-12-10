#include "main.hpp"

#define PI 3.14159265358979323846
#define WIDTH 800
#define HEIGHT 600
#define FONT_SIZE 32

SDL_Renderer* g_renderer = nullptr;
SDL_Window* g_window = nullptr;
TTF_Font* g_font;
SDL_Color g_color;
SDL_Rect g_l_paddle,g_r_paddle,g_ball,g_score_board;


float velocityX,velocityY;
std::string g_score;
int g_l_score,g_r_scorer;
bool g_turn;
bool g_running{false};
int g_frameCount {0};
int g_timerFPS{0};
int g_lastFrame{0};
int g_lastTime{0};
int g_fps{0};

bool init();
bool loadMedia();
void loop();
void wrirte(std::string text, int x, int y);
void update();
void input();
void render();
void quit();

int main(int argv, char** argc)
{
   if(init())
   {
       if(loadMedia())
       {
           loop();
           quit();
       }
   }
   return 0;
}

bool init()
{
    bool success { true};
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Init Failed: "<< SDL_GetError() << '\n';
        success =false;
    }else{
        if(SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&g_window,&g_renderer) < 0)
        {
            std::cout << "Window and Render init failed: "<< SDL_GetError() << '\n';
            success = false;    
        }
        if(TTF_Init() < 0)
        {
            std::cout << "Font init falied: "<< TTF_GetError() << '\n'; 
            success = false;
        }
    }
    return success;
}

bool loadMedia()
{
    bool success {true};
    g_font = TTF_OpenFont("./resources/Font/GravityBold8.ttf",FONT_SIZE); 
    if(g_font == nullptr)
    {
        std::cout << "load Font Fail"<< TTF_GetError() << '\n';
    }
    return success;
}

void loop()
{

    g_running =true;
    g_color.r = g_color.b = g_color.g = 255;
    while (g_running)
    {
        g_lastFrame = SDL_GetTicks();
        if(g_lastFrame >= (g_lastTime+1000))
        {
            g_lastTime = g_lastFrame;
            g_fps = g_frameCount;
            g_frameCount = 0;
        }
        std::cout << "fps: "<< g_fps << '\n';
        update();
        input();
        render();
    }
    
}

void update()
{

}

void write(std::string text, int x ,int y)
{
    SDL_Surface *surface= nullptr;
    SDL_Texture *texture = nullptr;
    const char *t = text.c_str();
}

void input()
{
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            g_running = false;
        }
    }
    if(keystates[SDL_SCANCODE_ESCAPE]) g_running = false;
    if(keystates[SDL_SCANCODE_UP]) {}
    if(keystates[SDL_SCANCODE_DOWN]) {}
}

void render()
{
   
    SDL_RenderClear(g_renderer);
    g_frameCount++;
    g_timerFPS = SDL_GetTicks()-g_lastFrame;
    if(g_timerFPS < (1000/60))
    {   
        SDL_Delay((1000/60)-g_timerFPS);
    }
    SDL_SetRenderDrawColor(g_renderer,g_color.r,g_color.g,g_color.b,255);
    SDL_RenderPresent(g_renderer);
}



void quit()
{
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    g_renderer = nullptr;
    g_window = nullptr;
    TTF_CloseFont(g_font);
    g_font = nullptr;
    TTF_Quit();
    SDL_Quit();
}

