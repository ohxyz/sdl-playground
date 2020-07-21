#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "random_spike.hpp"
#include "game.hpp"
#include <vector>
#include "helpers.hpp"
#include "spawner.hpp"

extern SDL_Renderer* gRenderer;

void
handleCollide() {

    SDL_Log( "Collide!" );
}

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Spawner" );

    if ( !game::init( {.x=500, .width=500, .height=500} ) ) {
        return 1;
    }

    RandomSpike::init();

    auto ranger = new Object2D( 11, 55, 48, 64, "images/ranger.bmp" );

    Move movement = { .direction=Direction::Left, .step=5, .interval=20 };
    auto om = new Spawner<RandomSpike>( {400, 400}, {40, 50, 10}, {1, 5, 300} );
    om->setObjectMovement( movement );
    om->setSpawnInterval( 1000 );
    om->start();

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
        om->spawn();
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
