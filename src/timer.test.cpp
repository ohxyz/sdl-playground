#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "object2d.hpp"
#include "game.hpp"
#include "structs.hpp"
#include "timer.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Timer" );

    if ( !game::init( {.x=500, .width=800, .height=600} ) ) {
        return 1;
    }

    Timer* timer = new Timer( 1000 );

    timer->start();

    bool shouldQuit = false;
    
    while ( !shouldQuit ) {

        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 ) {

            if ( event.type == SDL_QUIT ) {

                shouldQuit = true;
                break;
            }

            if ( event.type == SDL_KEYDOWN ) {

                switch ( event.key.keysym.sym ) {

                case SDLK_UP:
                case SDLK_w:
                    SDL_Log( "Key up!" );
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    SDL_Log( "Key down!" );
                    break;
                }
            }   
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        if ( timer->isTimeOut() ) {

            SDL_Log( "@@ time out!" );

            timer->reset();
        }
        
        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay( 10 );
    }

    game::quit();

    return 0;
}