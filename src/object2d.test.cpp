#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "object2d.hpp"
#include "game.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Object2D" );

    if ( !game::init( {.x=500, .width=800, .height=600} ) ) {
        return 1;
    }

    Obstacle::init();
    
    auto obstacle = new Object2D( 700, 0, 40, 72, "images/obstacle-3.png" );

    obstacle->setMovement( {.direction=Direction::Left, .step=1, .interval=20} );
    obstacle->startMove();

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
        
        obstacle->render();

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
