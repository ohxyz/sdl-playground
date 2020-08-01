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
#include "my_lib.h"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {


    printf( "fn %d", fn() );

    SDL_Log( "Test RandomObject" );

    if ( !game::init( {.x=500, .width=500, .height=500} ) ) {
        return 1;
    }

    auto ranger = new Object2D( 11, 55, 48, 64, "images/ranger.bmp" );

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

        SDL_SetRenderDrawColor( gRenderer, 128, 0, 0, 255 );

        helpers::fillCircle( 10, 10, 1, { 0, 0, 0, 255 } );

        // helpers::drawCircle( 20, 50, 50, { 0,0,0,255 });

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
