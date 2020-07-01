#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "event_handlers.hpp"
#include "object2d.hpp"
#include "sprite.hpp"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 700

using std::string;
using namespace event_handlers;

SDL_Window* gWindow;
SDL_Surface* gWindowSurface;
SDL_Renderer* gRenderer;

Sprite* walkSprite;
std::vector<Frame> walkFrames;

Sprite* jumpSprite;
std::vector<Frame> jumpFrames;

bool
init() {

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

SDL_Surface* 
loadSurface( string path ) {

    SDL_Surface* surface = SDL_LoadBMP( path.c_str() );

    if ( surface == NULL ) {

        printf( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }

    return surface;
}


int
loop( Object2D* obj ) {

    SDL_Event event;

    while ( SDL_PollEvent( &event ) != 0 ) {

        if ( event.type == SDL_QUIT ) {

            return false;
        }
        else if ( event.type == SDL_KEYDOWN ) {

            switch ( event.key.keysym.sym ) {

            case SDLK_w:
                SDL_Log( "Up!\n" );
                obj->resumeAnimation();
                break;

            case SDLK_s:
                SDL_Log( "Down!\n" );
                obj->stopAnimation();
                break;

            case SDLK_a:
                SDL_Log( "Left!\n" );
                obj->setFrames( jumpFrames );
                obj->startAnimation( 50 );
                break;

            case SDLK_d:
                SDL_Log( "Right!\n" );
                obj->setFrames( walkFrames );
                obj->startAnimation( 50 );
                break;

            default:
                SDL_Log( "No move!" );
            }
        }
    }

    return true;
}

int 
main( int argc, char* args[] ) {

    if ( !init() ) {

        return 1;
    }

    // Image2
    SDL_Surface* imageSurface2 = loadSurface( "images/avatar.bmp" );
    SDL_Texture* imageTexture2 = SDL_CreateTextureFromSurface( gRenderer, imageSurface2 );
    SDL_FreeSurface( imageSurface2 );

    SDL_Rect imageRect2;

    imageRect2.x = 300;
    imageRect2.y = 100;
    imageRect2.w = 48;
    imageRect2.h = 32;

    int ticksStart2 = SDL_GetTicks();
    int ticksNow2;

    Object2D* ranger = new Object2D( 20, 0, 48, 64, "images/ranger.bmp" );
    
    walkSprite = new Sprite( "images/walk.png", { .x=0, .y=0, .w=800, .h=795 }, 4, 4, SDL_FLIP_HORIZONTAL );
    walkFrames = walkSprite->createFrames( {50, 350, 200, 199} );

    jumpSprite = new Sprite( "images/jump.png", { .x=0, .y=0, .w=800, .h=596 }, 4, 3, SDL_FLIP_HORIZONTAL );
    jumpFrames = jumpSprite->createFrames( {50, 350, 200, 199} );

    Object2D* o = new Object2D( 50, 350, 200, 199 );
    o->setFrames( walkFrames );
    o->startAnimation( 50 );

    SDL_Color backgroundColor = { .r=255, .g=255, .b=255, .a=128 };
    Object2D* white = new Object2D( 0, 0, 50, 80, backgroundColor );

    Object2D* counter = new Object2D( 50, 50, 128, 128 );
    Sprite* counterSprite = new Sprite( "images/numbers.png", { .x=0, .y=0, .w=512, .h=512 }, 4, 4 );
    std::vector<Frame> counterFrames = counterSprite->createFrames( {50, 50, 128, 128} );
    counter->setFrames( counterFrames );
    counter->startAnimation( 1000 );

    std::vector<Frame> redFrames = {

        { .x=50, .y=250, .width=30, .height=20, .backgroundColorR=100, .backgroundColorG=0, .backgroundColorB=0, .backgroundColorA=255 },
        { .x=60, .y=250, .width=30, .height=20, .backgroundColorR=0, .backgroundColorG=100, .backgroundColorB=0, .backgroundColorA=255 },
        { .x=70, .y=250, .width=30, .height=20, .backgroundColorR=0, .backgroundColorG=0, .backgroundColorB=100, .backgroundColorA=255 }
    };

    // red->setFrames( redFrames );
    Object2D* red = new Object2D( redFrames );
    red->startAnimation( 1000, true );

    while ( loop( o ) ) {

        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        ranger->render();
        o->render();
        white->render();
        counter->render();
        red->render();


        // imageRect2
        ticksNow2 = SDL_GetTicks();

        if ( (ticksNow2 - ticksStart2) > 1000 ) {

            imageRect2.y += 5;
            ticksStart2 = ticksNow2;
        }

        SDL_RenderCopyEx( gRenderer, imageTexture2, NULL, &imageRect2, -15, NULL, SDL_FLIP_NONE );

        // Update
        SDL_RenderPresent( gRenderer );

        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    // delete ranger;
    // delete o;

    SDL_DestroyTexture( imageTexture2 );

    SDL_DestroyRenderer( gRenderer );
    SDL_FreeSurface( gWindowSurface );
    SDL_DestroyWindow( gWindow );
    SDL_Quit();

    return 0;
}
