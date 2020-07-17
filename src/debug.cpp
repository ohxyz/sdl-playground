#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <iostream>
#include "random_object.hpp"
#include "game.hpp"
#include <vector>
#include "helpers.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    SDL_Log( "Test RandomObject" );

    if ( !game::init( {.x=500, .width=300, .height=400} ) ) {
        return 1;
    }

    std::vector<RandomObject*> ros;

    auto ranger = new Object2D( 11, 55, 48, 64, "images/ranger.bmp" );

    bool shouldQuit = false;
    
    while ( !shouldQuit ) {

        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 ) {

            if ( event.type == SDL_QUIT ) {

                shouldQuit = true;
                break;
            }
            else if ( event.type == SDL_FINGERUP ) {
            
            }
            else if ( event.type == SDL_FINGERDOWN ) {

                int x = event.tfinger.x * game::screenWidth / game::scaleRatio;
                int y = event.tfinger.y * game::screenHeight / game::scaleRatio;

                // SDL_Log( "@@ finger down %d, %d", x, y );

            }
            else if ( event.type == SDL_FINGERMOTION ) {

                // int x = event.tfinger.x * game::screenWidth / game::scaleRatio;
                // int y = event.tfinger.y * game::screenHeight / game::scaleRatio;

                // float dxf = event.tfinger.dx;
                // float dyf = event.tfinger.dy;

                float dx = event.tfinger.dx * (float)game::screenWidth / game::scaleRatio;
                float dy = event.tfinger.dy * (float)game::screenHeight / game::scaleRatio;

                auto direction = helpers::getDirection( dx, dy, 10 );

                if ( direction == Direction::Up ) SDL_Log( "up!" );
                else if ( direction == Direction::Down ) SDL_Log( "down!" );
                else if ( direction == Direction::Left ) SDL_Log( "left!");
                else if ( direction == Direction::Right ) SDL_Log( "right!" );
                // float r = (float)dy / (float)dx;

                // if ( dy > 0 && (r > 1.0 || r < -1.0) ) SDL_Log( "down!" );
                // else if ( dy < 0 && (r > 1.0 || r <= -1.0) ) SDL_Log( "up!" );
                // else if ( dx > 0 && (r > -1.0 && r <1.0) ) SDL_Log( "right!" );
                // else if ( dx < 0 && (r > -1.0 && r <1.0) ) SDL_Log( "left!" );

                // SDL_Log( "@@@ finger motion %f, %f, %f", dx, dy, r );

            }

        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        ranger->render();

        // Update
        SDL_RenderPresent( gRenderer );
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
