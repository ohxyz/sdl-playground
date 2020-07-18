#include <SDL.h>
#include "game.hpp"
#include "game_runner.hpp"
#include "structs.hpp"

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

namespace event_handler {

    bool
    handleEventLoop( GameRunner* gameRunner ) {

        auto chicken = gameRunner->getChicken();
        auto restartButton = gameRunner->getRestartButton();

        SDL_Event event;

        while ( SDL_PollEvent( &event ) != 0 ) {

            if ( event.type == SDL_QUIT ) {

                return false;
            }
            else if ( event.type == SDL_FINGERUP ) {
            

            }
            else if ( event.type == SDL_FINGERDOWN ) {

                int x = event.tfinger.x * game::screenWidth / game::scaleRatio;
                int y = event.tfinger.y * game::screenHeight / game::scaleRatio;

                if ( restartButton->isWithinRect( x, y ) && restartButton->isVisible() ) {

                    gameRunner->init();
                }
            }
            else if ( event.type == SDL_FINGERMOTION ) {

                float dx = event.tfinger.dx * (float)game::screenWidth / game::scaleRatio;
                float dy = event.tfinger.dy * (float)game::screenHeight / game::scaleRatio;

                auto direction = helpers::getDirection( dx, dy, 10 );

                if ( direction == Direction::Up ) {
                    
                    SDL_Log( "up!" );

                    if ( !gameRunner->isFrozen() ) {
                         chicken->jump();
                    }
                } 
                else if ( direction == Direction::Down ) {
                    SDL_Log( "down!" );
                }
                else if ( direction == Direction::Left ) {
                    SDL_Log( "left!");
                }
                else if ( direction == Direction::Right ) {
                    SDL_Log( "right!" );
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

                    gameRunner->init();
                }
            }
            else if ( event.type == SDL_KEYDOWN ) {

                switch ( event.key.keysym.sym ) {

                case SDLK_r:
                    SDL_Log( "Restart!\n" );
                    gameRunner->init();
                    break;

                case SDLK_UP:
                case SDLK_w:
                    // SDL_Log( "key up!\n" );
                    if ( !gameRunner->isFrozen() ) chicken->jump();
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    // SDL_Log( "key down!\n" );
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    // SDL_Log( "key left!\n" );
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    // SDL_Log( "Right!\n" );
                    break;

                case SDLK_SPACE:
                    // SDL_Log( "SPACE!\n" );
                    break;

                // default:
                //     SDL_Log( "No move!" );
                }
            }
        }

        return true;
    }
}

#endif