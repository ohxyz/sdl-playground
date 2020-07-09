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

    auto chicken = om->getChicken();

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

                case SDLK_r:
                    SDL_Log( "Restart!\n" );
                    om->init();
                    break;

                case SDLK_w:
                    SDL_Log( "Up!\n" );
                    break;

                case SDLK_s:
                    SDL_Log( "Down!\n" );
                    break;

                case SDLK_a:
                    SDL_Log( "Left!\n" );
                    break;

                case SDLK_d:
                    // SDL_Log( "Right!\n" );
                    break;

                case SDLK_SPACE:
                    // SDL_Log( "SPACE!\n" );
                    if ( !om->isFrozen() ) chicken->jump();
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

        om->run();

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
