#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifndef GAME_HPP
#define GAME_HPP

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

namespace game {

    bool
    init() {

        srand( time(NULL) );

        int windowX = 1000;
        int windowY = -2000;

        int windowWidth = 360;
        int windowHeight = 800;

        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

            SDL_Log( "SDL can't initialize! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }

        if ( IMG_Init( IMG_INIT_PNG ) < 0 ) {
            
            SDL_Log( "Error initializing SDL_image: %s\n", SDL_GetError() );
            return false;
        }

        gWindow = SDL_CreateWindow(
            "SDL APP",
            windowX,
            windowY,
            windowWidth,
            windowHeight,
            SDL_WINDOW_SHOWN
        );

        if ( gWindow == NULL ) {

            SDL_Log( "Window can't be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }

        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_PRESENTVSYNC );

        if ( gRenderer == NULL ) {

            SDL_Log( "Renderer can't be created! SDL_Error: %s\n", SDL_GetError() );
            return false;
        }

        SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );

        // For mobile
        const char* platform = SDL_GetPlatform();

        if ( strcmp(platform, "Android") == 0 ) {

            SDL_DisplayMode displayMode;

            if( SDL_GetCurrentDisplayMode(  0, &displayMode ) == 0 ) {

                int screenWidth = displayMode.w;
                float factor = float(screenWidth) / (float)windowWidth;
                SDL_RenderSetScale( gRenderer, factor, factor );
            }

        }

        return true;
    }

    void
    quit() {

        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( gWindow );
        SDL_Quit();
    }
}

#endif
