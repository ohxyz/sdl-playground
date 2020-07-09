#include <SDL.h>

SDL_Window* gWindow;
SDL_Surface* gWindowSurface;
SDL_Renderer* gRenderer;

const int windowX = 100;
const int windowY = 100;
const int windowWidth = 360;
const int windowHeight = 640;

int main( int argc, char* args[] ) {

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

        SDL_Log( "SDL can't initialize! SDL_Error: %s", SDL_GetError() );
        return 1;
    }

    gWindow = SDL_CreateWindow(
        "SDL APP",
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if ( gWindow == NULL ) {

        SDL_Log( "Window can't be created! SDL_Error: %s", SDL_GetError() );
        return 1;
    }

    gWindowSurface = SDL_GetWindowSurface( gWindow );

    if ( gWindowSurface == NULL ) {

        SDL_Log( "Can't get surface from window! SDL_Error: %s", SDL_GetError() );
        return 1;
    }

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_PRESENTVSYNC );

    if ( gRenderer == NULL ) {

        SDL_Log( "Renderer can't be created! SDL_Error: %s", SDL_GetError() );
        return 1;
    }

    SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );

    SDL_Surface* imageSurface = SDL_LoadBMP( "ranger.bmp" );

    if ( imageSurface == NULL ) {

        SDL_Log( "Failed to load image. SDL Error: %s", SDL_GetError() );
    }
    
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface( gRenderer, imageSurface );
    SDL_FreeSurface( imageSurface );

    int shouldQuit = 0;
    while ( !shouldQuit ) {

        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 ) {

            if ( event.type == SDL_QUIT ) {

                shouldQuit = 1;
                break;
            }
            else if ( event.type == SDL_KEYDOWN ) {

                switch ( event.key.keysym.sym ) {

                case SDLK_r:
                    SDL_Log( "Restart!" );
                    break;

                case SDLK_w:
                    SDL_Log( "Up!" );
                    break;

                case SDLK_s:
                    SDL_Log( "Down!" );
                    break;

                case SDLK_a:
                    SDL_Log( "Left!" );
                    break;

                case SDLK_d:
                    SDL_Log( "Right!" );
                    break;
                }
            }
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        SDL_Rect clipRect = { 0, 0, 48, 64 };
        SDL_Rect targetRect = { 10, 10, 48, 64 };

        SDL_RenderCopy( 
            gRenderer, 
            imageTexture,
            &clipRect,
            &targetRect
        );

        // Update
        SDL_RenderPresent( gRenderer );

        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    SDL_DestroyRenderer( gRenderer );
    SDL_FreeSurface( gWindowSurface );
    SDL_DestroyWindow( gWindow );
    SDL_Quit();

    return 0;
}
