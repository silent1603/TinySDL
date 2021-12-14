#include "main.hpp"

#define PI 3.14159265358979323846
#define WIDTH 800
#define HEIGHT 600
#define FONT_SIZE 32
#define SIZE 16
#define BALL_SPEED 16 
#define SPEED 9

SDL_Renderer* g_renderer = nullptr;
SDL_Window* g_window = nullptr;
TTF_Font* g_font;
SDL_Color g_color;
SDL_Rect g_l_paddle,g_r_paddle,g_ball,g_score_board;
Mix_Chunk* g_collision = nullptr;
Mix_Chunk* g_scoreBell = nullptr;
Mix_Chunk* g_endGame = nullptr;
Mix_Chunk* g_clcik = nullptr;
Mix_Music* g_music = nullptr;


float velocityX,velocityY;
std::string g_score;
int g_l_score,g_r_score;
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
void serve();
bool hasRectIntersection(const SDL_Rect& a,const SDL_Rect& b);

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
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags)&imgFlags))
        {
            std::cout << "Image init failed: "<< IMG_GetError() << '\n';
            success= false;
        }
        if(TTF_Init() < 0)
        {
            std::cout << "Font init failed: "<< TTF_GetError() << '\n'; 
            success = false;
        }
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0)
        {
            std::cout << "Mixer init failed: "<< Mix_GetError() << '\n';   
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
    //load audio
       //Load prompt texture

    // //Load music
    // gMusic = Mix_LoadMUS( "21_sound_effects_and_music/beat.wav" );
    // if( gMusic == NULL )
    // {
    //     printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    //     success = false;
    // }
    
    // //Load sound effects
    // gScratch = Mix_LoadWAV( "21_sound_effects_and_music/scratch.wav" );
    // if( gScratch == NULL )
    // {
    //     printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    //     success = false;
    // }
    
    // gHigh = Mix_LoadWAV( "21_sound_effects_and_music/high.wav" );
    // if( gHigh == NULL )
    // {
    //     printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    //     success = false;
    // }

    // gMedium = Mix_LoadWAV( "21_sound_effects_and_music/medium.wav" );
    // if( gMedium == NULL )
    // {
    //     printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    //     success = false;
    // }

    // gLow = Mix_LoadWAV( "21_sound_effects_and_music/low.wav" );
    // if( gLow == NULL )
    // {
    //     printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    //     success = false;
    // }

    //loadi image
    return success;
}

void loop()
{

    g_running =true;
    g_color.r = g_color.b = g_color.g = 255;
    g_l_score = g_r_score = 0;
    g_l_paddle.x =32;
    g_l_paddle.h = HEIGHT/4;
    g_l_paddle.w = 12;
    g_l_paddle.y = (HEIGHT/2)-g_l_paddle.h/2;

    g_r_paddle = g_l_paddle;
    g_r_paddle.x = WIDTH-g_r_paddle.w-32;
    
    g_ball.w = g_ball.h= SIZE;
    
    serve();

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
   
    
    if(hasRectIntersection(g_ball,g_r_paddle))
    {
        double rel = (g_r_paddle.y+(g_r_paddle.h/2)) - (g_ball.y+(SIZE/2));   
        double normalize = rel/(g_r_paddle.h/2);
        double bounce_angle = normalize * (5*PI/12);
        velocityX =  -BALL_SPEED*cos(bounce_angle);
        velocityY =  BALL_SPEED*-sin(bounce_angle);
    }

    if(hasRectIntersection(g_ball,g_l_paddle))
    {
        double rel = (g_l_paddle.y+(g_l_paddle.h/2)) - (g_ball.y+(SIZE/2));   
        double normalize = rel/(g_l_paddle.h/2);
        double bounce_angle = normalize * (5*PI/12);
        velocityX = BALL_SPEED*cos(bounce_angle);
        velocityY = BALL_SPEED*-sin(bounce_angle);
    }

    if(g_ball.y > g_r_paddle.y+(g_r_paddle.h/2))
    {
        g_r_paddle.y += SPEED;
    }

    if(g_ball.y < g_r_paddle.y+(g_r_paddle.h/2))
    {
        g_r_paddle.y -= SPEED;
    }

    if(g_ball.x <= 0)  {
        g_r_score++;
        serve();
    }

    if(g_ball.x+SIZE >= WIDTH) { 
        g_l_score++;
        serve();
    }

     if(g_ball.y <= 0 || g_ball.y+SIZE >= HEIGHT) velocityY = -velocityY;
    
    g_ball.x += velocityX;
    g_ball.y += velocityY;
    g_score = std::to_string(g_l_score)+ " "+std::to_string(g_r_score);

    if(g_l_paddle.y < 0){
        g_l_paddle.y = 0;
    }

    if(g_l_paddle.y+g_l_paddle.h> HEIGHT)
    {
        g_l_paddle.y = HEIGHT-g_l_paddle.h;
    }

    if(g_r_paddle.y < 0){
        g_r_paddle.y = 0;
    }
    
    if(g_r_paddle.y+g_r_paddle.h> HEIGHT)
    {
        g_r_paddle.y = HEIGHT-g_r_paddle.h;
    }

   

}

bool hasRectIntersection(const SDL_Rect& a,const SDL_Rect& b){
    if( (a.x <= (b.x+b.w) && (a.x+a.w) >= b.x) &&
        ((a.y <= (b.y+b.h) && (a.y+a.h)>= b.y)))
    {
        return true;
    }
    return false;
}

void write(std::string text, int x ,int y)
{
    SDL_Surface *surface= nullptr;
    SDL_Texture *texture = nullptr;
    const char *t = text.c_str();
    surface = TTF_RenderText_Solid(g_font,t,g_color);
    texture = SDL_CreateTextureFromSurface(g_renderer,surface);
    g_score_board.w = surface->w;
    g_score_board.h = surface->h;
    g_score_board.x = x-g_score_board.w;
    g_score_board.y = y-g_score_board.h;
    SDL_FreeSurface(surface);
    surface =nullptr;
    SDL_RenderCopy(g_renderer,texture,nullptr,&g_score_board);
    SDL_DestroyTexture(texture);
    texture =nullptr;
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
    if(keystates[SDL_SCANCODE_UP]) {g_l_paddle.y -= SPEED;}
    if(keystates[SDL_SCANCODE_DOWN]) {g_l_paddle.y += SPEED;}
}

void render()
{
    SDL_SetRenderDrawColor(g_renderer,0x00,0x00,0x00,255);
    SDL_RenderClear(g_renderer);
    g_frameCount++;
    g_timerFPS = SDL_GetTicks()-g_lastFrame;
    if(g_timerFPS < (1000/60))
    {   
        SDL_Delay((1000/60)-g_timerFPS);
    }


    SDL_SetRenderDrawColor(g_renderer,g_color.r,g_color.g,g_color.b,255);
    SDL_RenderFillRect(g_renderer,&g_l_paddle);
    SDL_RenderFillRect(g_renderer,&g_r_paddle);
    SDL_RenderFillRect(g_renderer,&g_ball);
    write(g_score,WIDTH/2+FONT_SIZE,FONT_SIZE*2);
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
   //Free the sound effects
    // Mix_FreeChunk( gScratch );
    // Mix_FreeChunk( gHigh );
    // Mix_FreeChunk( gMedium );
    // Mix_FreeChunk( gLow );
    // gScratch = NULL;
    // gHigh = NULL;
    // gMedium = NULL;
    // gLow = NULL;
    
    // //Free the music
    // Mix_FreeMusic( gMusic );
    //gMusic = NULL;

    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void serve()
{
    g_l_paddle.y = g_r_paddle.y = (HEIGHT/2)-(g_l_paddle.h/2);
    if(g_turn)
    {
        g_ball.x = g_l_paddle.x + (g_l_paddle.w*4);
        velocityX = BALL_SPEED/2;
    }else{
        g_ball.x = g_r_paddle.x-(g_r_paddle.w*4);
        velocityX = -BALL_SPEED/2;
    }
    velocityY = 0;
    g_ball.y = HEIGHT/2-(SIZE/2);
    g_turn = !g_turn;
}

//  switch( e.key.keysym.sym )
//                         {
//                             //Play high sound effect
//                             case SDLK_1:
//                             Mix_PlayChannel( -1, gHigh, 0 );
//                             break;
                            
//                             //Play medium sound effect
//                             case SDLK_2:
//                             Mix_PlayChannel( -1, gMedium, 0 );
//                             break;
                            
//                             //Play low sound effect
//                             case SDLK_3:
//                             Mix_PlayChannel( -1, gLow, 0 );
//                             break;
                            
//                             //Play scratch sound effect
//                             case SDLK_4:
//                             Mix_PlayChannel( -1, gScratch, 0 );
//                             break;
//                               case SDLK_9:
//                             //If there is no music playing
//                             if( Mix_PlayingMusic() == 0 )
//                             {
//                                 //Play the music
//                                 Mix_PlayMusic( gMusic, -1 );
//                             }
//                             //If music is being played
//                             else
//                             {
//                                 //If the music is paused
//                                 if( Mix_PausedMusic() == 1 )
//                                 {
//                                     //Resume the music
//                                     Mix_ResumeMusic();
//                                 }
//                                 //If the music is playing
//                                 else
//                                 {
//                                     //Pause the music
//                                     Mix_PauseMusic();
//                                 }
//                             }
//                             break;
                            
//                             case SDLK_0:
//                             //Stop the music
//                             Mix_HaltMusic();
//                             break;
//                         }
//                     }
//SDL_Surface* loadedSurface = IMG_Load( path.c_str() );