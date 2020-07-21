#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "random_object.hpp"
#include "game.hpp"
#include <vector>
#include "helpers.hpp"
#include "object_manager.hpp"
#include "chicken.hpp"

extern SDL_Renderer* gRenderer;

void
handleCollide() {

    SDL_Log( "Collide!" );
}

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test ObjectManager" );

    if ( !game::init( {.x=500, .width=500, .height=500} ) ) {
        return 1;
    }

    RandomObject::init();

    auto ranger = new Object2D( 11, 55, 48, 64, "images/ranger.bmp" );

    Move movement = { .direction=Direction::Left, .step=5, .interval=20 };
    auto om = new ObjectManager<RandomObject>( 400, 100 );
    om->setMovement( movement );
    om->setSpawnInterval( 1000 );

    bool shouldQuit = false;
    
    while ( !shouldQuit ) {

        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 ) {

            if ( event.type == SDL_QUIT ) {

                shouldQuit = true;
                break;
            }
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        ranger->render();
        // om->run( ranger, handleCollide);
        om->move();
        // for ( auto& obj : *om->getObjects() ) {

        //     if ( obj->collide( ranger ) ) { SDL_Log( "cOLLIDE!" ); om->stopMove(); }
        // }

        om->render();
        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
