#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "game.hpp"
#include "animation.hpp"
#include "animations/chicken_hurt.hpp"
#include "animations/chicken_walk.hpp"
#include "animations/chicken_jump.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    if ( !game::init() ) {
        return 1;
    }

    auto hurt = new ChickenHurtAnimation();
    hurt->start();
    hurt->setFrameDuration( 1000 );

    auto walk = new ChickenWalkAnimation( 0, 150 );
    walk->start(true);

    auto jump = new ChickenJumpAnimation( 200, 150 );
    jump->start( true );

    auto jumpFrames = jump->getFrames();

    for ( auto &f : *jumpFrames ) { f.x = 50; }

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
        
        hurt->animate();
        hurt->renderCurrentFrame();

        walk->animate();
        walk->renderCurrentFrame();

        jump->animate();
        jump->renderCurrentFrame();

        // Update
        SDL_RenderPresent( gRenderer );

        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
