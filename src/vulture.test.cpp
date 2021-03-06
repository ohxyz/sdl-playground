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

    if ( !game::init( {.x=500, .width=360, .height=600} ) ) {
        return 1;
    }

    Move move = { .direction=Direction::Left, .step=5, .interval=20 };
    auto vulture1 = new Vulture( 100, 50 );
    vulture1->setMovement( move );
    vulture1->startMove();

    auto obj = new Object2D( 100, 50, 40, 72, "images/obstacle-3.png" );
    obj->setHitboxColor( 0, 0, 0, 111 );
    
    if ( vulture1->collide( obj ) ) SDL_Log( "@@ COLLIDE!" );
    
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
        
        obj->render();
        vulture1->render();

        if ( vulture1->collide( obj ) ) SDL_Log( "@@ COLLIDE!" );

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
