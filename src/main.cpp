#include <SDL.h>
#include <stdio.h>
#include "game_runner.hpp"
#include "game.hpp"
#include "event_handler.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    try {

        if ( !game::init( { .name="Chicken Jump" }) ) {
            return 1;
        }

        SDL_Log( "Platform: %s", game::platform );

        GameRunner* gr = new GameRunner;

        while ( event_handler::handleEventLoop( gr ) ) {

            // Drawing 
            // Green
            SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
            SDL_RenderClear( gRenderer );

            gr->run();

            // Update
            SDL_RenderPresent( gRenderer );

            // If delay by 1 ms, my laptop gives ci, ci, ci sound
            SDL_Delay( 5 );
        }

        game::quit();

    }
    catch ( const char* message ) {

        SDL_Log( "%s", message );
    }

    return 0;
}
