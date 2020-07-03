#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "event_handlers.hpp"
#include "object2d.hpp"
#include "sprite.hpp"
#include <math.h>
#include "velo.hpp"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 700

using std::string;
using namespace event_handlers;

SDL_Window* gWindow;
SDL_Surface* gWindowSurface;
SDL_Renderer* gRenderer;


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

void h() {

    printf( "Done!\n" );
}

int
loop( Velo* hero ) {

    SDL_Event event;

    while ( SDL_PollEvent( &event ) != 0 ) {

        if ( event.type == SDL_QUIT ) {

            return false;
        }
        else if ( event.type == SDL_KEYDOWN ) {

            switch ( event.key.keysym.sym ) {

            case SDLK_w:
                SDL_Log( "Up!\n" );
                hero->resumeAnimation();
                break;

            case SDLK_s:
                SDL_Log( "Down!\n" );
                hero->stopAnimation();
                break;

            case SDLK_a:
                SDL_Log( "Left!\n" );
                break;

            case SDLK_d:
                SDL_Log( "Right!\n" );
                hero->walk();
                break;

            case SDLK_SPACE:
                SDL_Log( "SPACE!\n" );
                hero->jump();
                break;

            // default:
            //     SDL_Log( "No move!" );
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

    Object2D* ranger = new Object2D( 20, 0, 48, 64, "images/ranger.bmp" );

    SDL_Color backgroundColor = { .r=255, .g=255, .b=255, .a=128 };
    Object2D* white = new Object2D( 0, 0, 50, 80, backgroundColor );

    Object2D* counter = new Object2D( 50, 50, 128, 128 );
    Sprite* counterSprite = new Sprite( "images/numbers.png", { .x=0, .y=0, .w=512, .h=512 }, 4, 4 );
    std::vector<Frame> counterFrames = counterSprite->createFrames( {50, 50, 128, 128}, 500);
    counter->setFrames( counterFrames );
    counter->startAnimation();

    Velo* velo = new Velo();
    velo->walk();

    std::vector<Frame> redFrames = {
        
        { .x=50, .y=400, .width=55, .height=66, .backgroundColorA=134, .duration=3000 },
        { .x=50, .y=350, .width=55, .height=66, .backgroundColorA=134, .duration=2000 },
        { .x=50, .y=320, .width=55, .height=66, .backgroundColorA=134, .duration=1000 },
        { .x=50, .y=300, .width=55, .height=66, .backgroundColorA=134, .duration=500 },
        { .x=50, .y=330, .width=55, .height=66, .backgroundColorA=134, .duration=500 },
        { .x=50, .y=370, .width=55, .height=66, .backgroundColorA=134, .duration=1000 },
        { .x=50, .y=400, .width=55, .height=66, .backgroundColorA=134, .duration=2000 }
    };

    Object2D* red = new Object2D( redFrames );
    red->startAnimation( true );

    bool shouldQuit = false;

    while ( !shouldQuit ) {

        // Event handling
        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 ) {

            if ( event.type == SDL_QUIT ) {

                shouldQuit = true;
                break;
            }
            else if ( event.type == SDL_KEYDOWN ) {

                switch ( event.key.keysym.sym ) {

                case SDLK_w:
                    SDL_Log( "Up!\n" );
                    counter->resumeAnimation();
                    break;

                case SDLK_s:
                    SDL_Log( "Down!\n" );
                    counter->stopAnimation();
                    break;

                case SDLK_a:
                    SDL_Log( "Left!\n" );
                    break;

                case SDLK_d:
                    SDL_Log( "Right!\n" );
                    counter->startAnimation();
                    // velo->walk();
                    break;

                case SDLK_SPACE:
                    SDL_Log( "SPACE!\n" );
                    velo->jump();
                    break;

                // default:
                //     SDL_Log( "No move!" );
                }
            }
        }

        // Drawing 

        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        ranger->render();
        velo->render();
        white->render();
        counter->render();
        // red->render();

        // Update
        SDL_RenderPresent( gRenderer );


        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    // delete ranger;
    // delete o;

    SDL_DestroyRenderer( gRenderer );
    SDL_FreeSurface( gWindowSurface );
    SDL_DestroyWindow( gWindow );
    SDL_Quit();

    return 0;
}
