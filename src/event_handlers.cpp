#include <SDL.h>
#include "event_handlers.hpp"

void 
event_handlers::handleEventLoopFinish( SDL_Window* window ) {

    SDL_DestroyWindow( window );
    SDL_Quit();
}

void
event_handlers::handleKeyDown(SDL_Event event) {

    switch ( event.key.keysym.sym ) {

        case SDLK_a:
            SDL_Log( "Left!\n" );
            break;

        case SDLK_w:
            SDL_Log( "Up!\n" );
            break;

        case SDLK_s:
            SDL_Log( "Down!\n" );
            break;

        case SDLK_d:
            SDL_Log( "Right!\n" );
            break;

        default:
            SDL_Log( "No move!" );
    }
}

