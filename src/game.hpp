#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifndef GAME_HPP
#define GAME_HPP

SDL_Renderer* gRenderer = NULL;

// float gScaleRatio = 1;
// int gScreenWidth;
// int gScreenHeight;

namespace game {

    SDL_Window* window = NULL;

    const char* platform = "";
    const int windowX = 1000;
    const int windowY = -2000;
    const int windowWidth = 360;
    const int windowHeight = 640;

    float scaleRatio = 1;
    int screenWidth;
    int screenHeight;

    bool
    isMobile() {

        return strcmp(platform, "Android") == 0;
    }

    bool
    isDesktop() {

        return strcmp(platform, "Windows") == 0;
    }

    bool
    init() {

        platform = SDL_GetPlatform();

        srand( time(NULL) );

        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

            SDL_Log( "SDL can't initialize! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }

        if ( IMG_Init( IMG_INIT_PNG ) < 0 ) {
            
            SDL_Log( "Error initializing SDL_image: %s\n", SDL_GetError() );
            return false;
        }

        window = SDL_CreateWindow(
            "SDL APP",
            windowX,
            windowY,
            windowWidth,
            windowHeight,
            SDL_WINDOW_SHOWN
        );

        if ( window == NULL ) {

            SDL_Log( "Window can't be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }

        gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );

        if ( gRenderer == NULL ) {

            SDL_Log( "Renderer can't be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }

        SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );

        // For mobile
        if ( isMobile() ) {

            SDL_DisplayMode displayMode;

            if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 ) {

                screenWidth = displayMode.w;
                screenHeight = displayMode.h;
                scaleRatio = float(screenWidth) / (float)windowWidth;

                SDL_RenderSetScale( gRenderer, scaleRatio, scaleRatio );
            }
        }

        return true;
    }

    void
    quit() {

        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
    }

}

#endif
