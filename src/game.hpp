#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifndef GAME_HPP
#define GAME_HPP

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

const int gWindowX = 1000;
const int gWindowY = -2000;
const int gWindowWidth = 360;
const int gWindowHeight = 640;

float gScaleRatio = 1;
int gScreenWidth;
int gScreenHeight;

namespace game {

    const char* platform;

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

        gWindow = SDL_CreateWindow(
            "SDL APP",
            gWindowX,
            gWindowY,
            gWindowWidth,
            gWindowHeight,
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
        if ( isMobile() ) {

            SDL_DisplayMode displayMode;

            if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 ) {

                gScreenWidth = displayMode.w;
                gScreenHeight = displayMode.h;
                gScaleRatio = float(gScreenWidth) / (float)gWindowWidth;

                SDL_RenderSetScale( gRenderer, gScaleRatio, gScaleRatio );
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
