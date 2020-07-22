#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "object2d.hpp"
#include "game.hpp"
#include "bird.hpp"
#include "spawner.hpp"
#include "structs.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Bird" );

    if ( !game::init( {.x=500, .width=360, .height=600} ) ) {
        return 1;
    }

    Move move = { .direction=Direction::Left, .step=5, .interval=20 };
    auto bird = new Bird( 100, 50 );
    bird->setMovement( move );
    bird->startMove();

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
                    bird->startMove();
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    bird->stopMove();
                    break;
                }
            }   
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );
        
        bird->render();

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
