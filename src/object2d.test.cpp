#include <SDL.h>
#include <iostream>
#include "object2d.hpp"
#include "functional"

SDL_Renderer* gRenderer;

typedef int (*callback)(Object2D*);

Object2D* newO = new Object2D();

int 
fn( Object2D* obj ) {

    return obj->getCurrentFrame()->x;
}

int
call( callback f, Object2D* obj ) {

    if ( obj == NULL ) return 99;

    return f(obj);
}

void
handleClick() {

    std::cout << "click!" << std::endl;
}

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test" );

    Object2D* o = new Object2D( 1, 2, 3, 4 );
    o->onClick( handleClick );

    for ( int i = 0; i < 2; i++ ) {

        o->click();
    }

    return 0;
}