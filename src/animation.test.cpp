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
#include "animations/chicken_skid.hpp"
#include "animations/vulture_fly.hpp"
#include "animations/bird_fly.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    // SDL_RENDERER_ACCELERATED
    // SDL_RENDERER_PRESENTVSYNC
    if ( !game::init( { .x=500, .width=800, .height=800, .rendererFlag=SDL_RENDERER_ACCELERATED } ) ) {
        return 1;
    }

    auto hurt = new ChickenHurtAnimation();
    hurt->start();
    hurt->setFrameDuration( 1000 );

    auto walk = new ChickenWalkAnimation( 0, 150 );
    walk->start(true);

    auto jump = new ChickenJumpAnimation( 200, 150 );
    jump->start( 100 );

    auto jumpFrames = jump->getFrames();

    for ( auto &f : jumpFrames ) { f->x = 99; }

    auto skid = new ChickenSkidAnimation( 0, 350 );
    // skid->setFrameDuration( 100 );
    skid->start(0);

    auto fly = new VultureFlyAnimation( 60, 250);
    fly->start( true );

    auto birdFly = new BirdFlyAnimation( 250, 250 );
    birdFly->start( true );

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
        
        // hurt->animate();
        // hurt->render();

        // walk->animate();
        // walk->render();

        jump->animate();
        jump->render();

        // skid->animate();
        // skid->render();

        // fly->animate();
        // fly->render();

        // birdFly->animate();
        // birdFly->render();

        // Update
        SDL_RenderPresent( gRenderer );

        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
