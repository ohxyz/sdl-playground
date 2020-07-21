#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "object2d.hpp"
#include "game.hpp"
#include "vulture.hpp"
#include "spawner.hpp"
#include "structs.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Vulture" );

    if ( !game::init( {.x=500, .width=800, .height=600} ) ) {
        return 1;
    }

    Move move = { .direction=Direction::Left, .step=5, .interval=20 };
    auto vulture1 = new Vulture( 700, 50 );
    vulture1->setMovement( move );
    vulture1->startMove();

    Spawner<Vulture>* vm = new Spawner<Vulture>( {800, 800}, {10, 15, 20}, {1, 5, 333} );
    vm->setObjectMovement( move );
    vm->setSpawnInterval( 2000 );
    vm->start();

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
                    vulture1->startMove();
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    vulture1->stopMove();
                    break;
                }
            }   
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );
        
        vulture1->render();
        vm->spawn();
        vm->render();

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
