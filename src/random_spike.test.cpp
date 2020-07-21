#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "random_spike.hpp"
#include "game.hpp"
#include <vector>

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    try {

        SDL_Log( "Test RandomSpike" );

        if ( !game::init( {.x=500, .width=800, .height=600} ) ) {
            return 1;
        }

        // std::vector<RandomObject*> ros;

        // for ( int i = 0; i < 5; i ++ ) {

        //     for ( int j = 0; j < 3; j ++ ) {

        //         auto ro = new RandomObject( 50 + 120*i, 100 + 100*j );
        //         ros.push_back( ro );
        //     }
        // }

        RandomSpike::init();


        auto random = new RandomSpike( 100, 450 );
        // auto random2 = new RandomObject( 700, 550, 0.5 );
        // random2->setMovement( {
        //     .direction=Direction::Left, .step=10, .interval=100
        // } );
        // random2->startMove();

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

            random->render();
            // random2->render();

            // Update
            SDL_RenderPresent( gRenderer );
            SDL_Delay(5);
        }

        game::quit();

    }
    catch (const char* message ) {

        std::cerr << message << std::endl;
    }

    return 0;
}
