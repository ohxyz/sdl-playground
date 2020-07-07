#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "object2d.hpp"
#include "sprite.hpp"
#include <math.h>
#include "velo.hpp"
#include "object_manager.hpp"
#include "helpers.h"

SDL_Window* gWindow;
SDL_Surface* gWindowSurface;
SDL_Renderer* gRenderer;


int 
main( int argc, char* args[] ) {

    if ( !initGame() ) {
        return 1;
    }

    ObjectManager* om = new ObjectManager;

    SDL_Color backgroundColor = { .r=255, .g=255, .b=255, .a=128 };
    Object2D* white = new Object2D( 0, 0, 50, 80, backgroundColor );

    Object2D* counter = new Object2D( 50, 50, 128, 128 );
    Sprite* counterSprite = new Sprite( "images/numbers.png", { .x=0, .y=0, .w=512, .h=512 }, 4, 4 );
    std::vector<Frame> counterFrames = counterSprite->createFrames( {50, 50, 128, 128}, 1000);
    counter->setAnimationFrames( counterFrames );
    counter->startAnimation();

    auto chicken = om->getChicken();

    // auto ranger = new Object2D( 10, 10, 170, 222, "images/ranger.bmp", { 0, 0, 48, 64} );

    bool shouldQuit = false;
    while ( !shouldQuit ) {

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
                    // counter->startAnimation();
                    chicken->walk();
                    break;

                case SDLK_SPACE:
                    SDL_Log( "SPACE!\n" );
                    chicken->jump();
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

        // white->render();
        // counter->render();
        // ranger->render();
        om->run();

        // Update
        SDL_RenderPresent( gRenderer );

        // velo->render();
        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    // delete ranger;

    SDL_DestroyRenderer( gRenderer );
    SDL_FreeSurface( gWindowSurface );
    SDL_DestroyWindow( gWindow );
    SDL_Quit();

    return 0;
}
