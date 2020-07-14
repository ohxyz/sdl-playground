#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "object_manager.hpp"
#include "helpers.hpp"
#include "game.hpp"

extern SDL_Renderer* gRenderer;

int 
main( int argc, char* args[] ) {

    if ( !game::init() ) {
        return 1;
    }

    SDL_Log( "Platform: %s", game::platform );

    ObjectManager* om = new ObjectManager;

    auto chicken = om->getChicken();
    auto restartButton = om->getRestartButton();

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

                if ( !om->isFrozen() ) {

                     chicken->jump();
                     break;
                }

                int x = event.tfinger.x * game::screenWidth / game::scaleRatio;
                int y = event.tfinger.y * game::screenHeight / game::scaleRatio;

                // SDL_Log( "Touch X: %d, Y: %d", x, y );

                if ( restartButton->isWithinRect( x, y ) && restartButton->isVisible() ) {

                    om->init();
                }
            }
            else if ( event.type == SDL_MOUSEBUTTONUP ) {

                if ( !game::isDesktop() ) break;

                int x, y;
                SDL_GetMouseState( &x, &y );

                // SDL_Log( "Click X: %d, Y: %d", x, y );

                if ( restartButton->isWithinRect( x, y )
                        && restartButton->isVisible()
                        && SDL_BUTTON(SDL_BUTTON_LEFT) ) {

                    om->init();
                }
            }
            else if ( event.type == SDL_KEYDOWN ) {

                switch ( event.key.keysym.sym ) {

                case SDLK_r:
                    SDL_Log( "Restart!\n" );
                    om->init();
                    break;

                case SDLK_w:
                    SDL_Log( "Up!\n" );
                    break;

                case SDLK_s:
                    SDL_Log( "Down!\n" );
                    break;

                case SDLK_a:
                    SDL_Log( "Left!\n" );
                    break;

                case SDLK_d:
                    // SDL_Log( "Right!\n" );
                    break;

                case SDLK_SPACE:
                    // SDL_Log( "SPACE!\n" );
                    if ( !om->isFrozen() ) chicken->jump();
                    break;

                // default:
                //     SDL_Log( "No move!" );
                }
            }
        }

        // Drawing 
        // Green
        SDL_SetRenderDrawColor( gRenderer, 0, 128, 0, 255 );
        SDL_RenderClear( gRenderer );

        om->run();

        // Update
        SDL_RenderPresent( gRenderer );

        // Delay by some time to avoid high CPU usage
        // If by 1 ms, my laptop gives ci, ci, ci sound
        SDL_Delay(5);
    }

    game::quit();

    return 0;
}
