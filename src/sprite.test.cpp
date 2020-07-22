#include <SDL.h>
#include "sprite.hpp"

int 
main( int argc, char* args[] ) {

    printf( "Test Sprite\n" );

    Sprite* sp = new Sprite( "images/walk.png", { .x=0, .y=0, .w=800, .h=795 }, 4, 4 );
    std::vector<Frame*> newFrames = sp->createFrames( 77, 88 );

    printf( "newFrames size: %d\n", newFrames.size() );
    printf( "newFrames[1]->x: %d\n", newFrames[1]->x );
    printf( "newFrames[2]->imageClipX: %d\n", newFrames[2]->imageClipX );

    return 0;
}