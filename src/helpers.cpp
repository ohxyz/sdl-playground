#include "helpers.h"
#include <SDL_image.h>
#include <time.h>

extern SDL_Window* gWindow;
extern SDL_Surface* gWindowSurface;
extern SDL_Renderer* gRenderer;

SDL_Texture* 
helpers::loadTexture( std::string imagePath ) {

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
helpers::collide( SDL_Rect& rect1, SDL_Rect& rect2 ) {

    if ( (rect1.x < rect2.x) && (rect1.x + rect1.w  < rect2.x) ) {
        printf( "Rect1 on LEFT side of Rect2\n" );
        return false;
    }
    else if ( (rect1.y < rect2.y) && (rect1.y + rect1.h < rect2.y) ) {
        printf( "Rect1 on UP side of Rect2\n" );
        return false;
    }
    else if (  rect1.y > (rect2.y + rect2.h) ) {
        printf( "Rect1 on DOWN side of Rect2\n" );
        return false;
    }
    else if ( rect1.x > (rect2.x + rect2.w) ) {
        printf( "Rect1 on RIGHT side of Rect2\n" );
        return false;
    }

    return true;
}

bool
initGame() {

    srand( time(NULL) );

    const int windowX = 1000;
    const int windowY = -2000;
    const int windowWidth = 360;
    const int windowHeight = 640;

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
        windowX,
        windowY,
        windowWidth,
        windowHeight,
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
