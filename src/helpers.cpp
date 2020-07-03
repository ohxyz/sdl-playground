#include "helpers.h"
#include <SDL_image.h>

extern SDL_Window* gWindow;
extern SDL_Surface* gWindowSurface;
extern SDL_Renderer* gRenderer;

SDL_Texture* 
loadTexture( std::string imagePath ) {

    SDL_Surface* surface = IMG_Load( imagePath.c_str() );

    if ( surface == NULL ) {

        printf( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface( gRenderer, surface );
    SDL_FreeSurface( surface );

    return texture;
}

bool
initGame() {

    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 700;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

        printf( "SDL can't initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    if ( IMG_Init( IMG_INIT_PNG ) < 0 ) {
        
        printf( "Error initializing SDL_image: %s\n", SDL_GetError() );
        return false;
    }

    gWindow = SDL_CreateWindow(
        "SDL APP",
        1000,
        -2000,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if ( gWindow == NULL ) {

        printf( "Window can't be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    gWindowSurface = SDL_GetWindowSurface( gWindow );

    if ( gWindowSurface == NULL ) {

        printf( "Can't get surface from window! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    // SDL_FillRect( gWindowSurface, NULL, SDL_MapRGB(gWindowSurface->format, 0, 128, 0) );
    // SDL_UpdateWindowSurface( gWindow );

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

    if ( gRenderer == NULL ) {

        printf( "Renderer can't be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );

    return true;
}
