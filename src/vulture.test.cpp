#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "object2d.hpp"
#include "game.hpp"
#include "vulture.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Vulture" );

    if ( !game::init( {.x=500, .width=800, .height=600} ) ) {
        return 1;
    }

    auto vulture = new Vulture( 600, 400 );

    vulture->startMove();

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

                case SDLK_UP:
                case SDLK_w:
                    vulture->startMove();
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    vulture->stopMove();
                    break;
                }
            }   
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );
        
        vulture->render();

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
