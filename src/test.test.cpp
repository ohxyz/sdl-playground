#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "object2d.hpp"
#include "game.hpp"
#include "structs.hpp"

extern SDL_Renderer* gRenderer;

/* A basic setup of test 
 * Remove this comment block. So I know I'm not editing the original file!  
 */

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test Test!" );

    if ( !game::init( {.x=500, .width=800, .height=600} ) ) {
        return 1;
    }

    bool shouldQuit = false;
    
    while ( !shouldQuit ) {

        // Uint64 start = SDL_GetPerformanceCounter();

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
        
        // Update
        SDL_RenderPresent( gRenderer );

        // Uint64 end = SDL_GetPerformanceCounter();
        // float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        // float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        // float cappedElapsedMS = floor(16.666f - elapsedMS);
        // std::cout << "Current FPS: " << std::to_string( 1000.0f / cappedElapsedMS ) << std::endl;

        SDL_Delay( 10 );

    }

    game::quit();

    return 0;
}