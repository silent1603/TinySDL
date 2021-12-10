#include "main.hpp"

int windowWidth = 1280,
    windowHeight = 720;
bool init();
bool loadMedia();
void close();
void update();

enum gKeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow =nullptr;



SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gCurrentTexture = nullptr;
SDL_Texture* loadTexture(std::string path);
SDL_Texture* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];


SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image ! " << path.c_str() <<"SDL_image Error: "<< IMG_GetError() << '\n'; 
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool init()
{
    bool success =true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL count not initialize 1 SDL_Error : \n" << SDL_GetError() << '\n';
        success = false;
    }else{
        gWindow = SDL_CreateWindow("Screen",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
        if(gWindow == nullptr)
        {
            std::cout << "Window could not be created! SDL_Error: "<< SDL_GetError()  << '\n';
            success = false;
        }else{
            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
            if(gRenderer == nullptr)
            {
                 std::cout << "Renderer cound not be created! SDL_Error: "<< SDL_GetError() << '\n';
            }else{
                int imgFlags = IMG_INIT_PNG;
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
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

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT] = loadTexture( "./resources/Pirate Bomb/Sprites/1-Player-Bomb Guy/1-Idle/1.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == nullptr )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadTexture( "./resources/Pirate Bomb/Sprites/1-Player-Bomb Guy/2-Run/12.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == nullptr )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadTexture( "./resources/Pirate Bomb/Sprites/1-Player-Bomb Guy/8-Dead Hit/6.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == nullptr )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadTexture( "./resources/Pirate Bomb/Sprites/1-Player-Bomb Guy/10-Door In/1.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == nullptr )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadTexture( "./resources/Pirate Bomb/Sprites/1-Player-Bomb Guy/9-Dead Ground/4.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == nullptr )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_DestroyTexture( gKeyPressSurfaces[ i ] );
		gKeyPressSurfaces[ i ] = nullptr;
	}
    gCurrentTexture =nullptr;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    gRenderer =nullptr;
    gWindow = nullptr;
    IMG_Quit();
    SDL_Quit();
}

void update()
{
    bool quit = false;
    SDL_Event e;
    gCurrentTexture = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    while (!quit)
    {
        while (SDL_PollEvent(&e) != NULL)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                        //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                        gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                        std::cout << "up" << '\n';
                        break;

                    case SDLK_DOWN:
                        gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                        std::cout << "down" << '\n';
                        break;

                    case SDLK_LEFT:
                        gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                        std::cout << "left" << '\n';
                        break;

                    case SDLK_RIGHT:
                        gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                        std::cout << "right" << '\n';
                        break;

                    default:
                        gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                        break;
                }
            }
        }
        SDL_Rect character;
        int w , h;
        SDL_QueryTexture(gCurrentTexture,nullptr,nullptr,&w,&h);
        character.x = windowWidth/2;
        character.y = windowHeight/2;
        character.w = w;
        character.h = h;

        SDL_RenderClear(gRenderer);
        //SDL_RenderSetViewport(gRenderer,&character);
        SDL_RenderCopy(gRenderer,gCurrentTexture,nullptr,&character);
        SDL_RenderPresent(gRenderer);
    }
    
}

int main(int argc, char *argv[])
{

    if(!init()){
        std::cout << "Failed to initialize" << '\n';
    }else {
        if(!loadMedia()){
            std::cout << "Failed to load media!" << '\n';
        }else{
            update();
            close();
        }
    }

    return 0;
}