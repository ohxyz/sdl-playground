#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "bird.hpp"
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

    Move movement = { .direction=Direction::Left, .step=5, .interval=20 };
    auto om = new Spawner<Bird>( 400, 400 );
    om->setObjectMovement( movement );
    // om->setSpawnInterval( 1000 );
    // om->startAutoSpawn();

    Timer* timer = new Timer();
    timer->start( 1000 );

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

        if ( timer->isTimeOut() ) {
        
            om->spawn();
            timer->reset();
        }


        om->renderObjects();
        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(10);
    }

    game::quit();

    return 0;
}
