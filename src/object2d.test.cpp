#include <SDL.h>
#include "object2d.hpp"

SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test" );

    Object2D* o = new Object2D( 0, 0, 10, 100, "bin/images/attack.bmp", 4, 4);

    o->initAnimation();

    return 0;
}