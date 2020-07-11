#include <SDL.h>
#include "object_manager.hpp"
#include "helpers.h"
#include "utils.h"

SDL_Window* gWindow;
SDL_Surface* gWindowSurface;
SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    initGame();
    
    ObjectManager* om = new ObjectManager;

    Object2D* red = new Object2D( 50, 400, 55, 65, { .r=128, 0, 0, 150 } );
    Object2D* blue = new Object2D( 70, 466, 55, 65, { 0, 0, .b=128, 150 } );

    Object2D* green = new Object2D({ 

        .id = "green",
        .x = 80,
        .y = 90,
        .width = 55,
        .height = 65,
        .backgroundColorA = 50,
        .collisionTop = 10,
        .collisionRight = 10,
        .collisionBottom = 10,
        .collisionLeft = 10,
        .collisionColorA = 100
    });

    if ( om->collide( red, blue ) ) { 

        SDL_Log( "red x blue\n" ); 
    }

    if ( om->collide( blue, red ) ) { 

        SDL_Log( "blue x red\n" );
    }

    int shouldQuit = false;
    while ( !shouldQuit ) {

        // Event handling
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

        red->render();
        blue->render();
        green->render();

        // Update
        SDL_RenderPresent( gRenderer );

        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    return 0;
}