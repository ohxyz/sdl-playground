#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <string.h>
#include "structs.hpp"

#ifndef HELPERS_HPP
#define HELPERS_HPP

extern SDL_Renderer* gRenderer;

namespace helpers {

    Direction
    getDirection( float distX, float distY, float min=1.0 ) {

        SDL_Log( "@@ %f, %f, %f", distX, distY, min );

        if ( distX < min && distY < min && distX > -min && distY > -min ) return Direction::None;

        float r = distY / distX;

        if ( distY > 0 && (r > 1.0 || r < -1.0) ) return Direction::Down;
        if ( distY < 0 && (r > 1.0 || r <= -1.0) ) return Direction::Up;
        if ( distX > 0 && (r > -1.0 && r <1.0) ) return Direction::Right;
        if ( distX < 0 && (r > -1.0 && r <1.0) ) return Direction::Left;

        return Direction::None;
    }

    SDL_Texture* 
    loadTexture( std::string imagePath ) {

        SDL_Surface* surface = IMG_Load( imagePath.c_str() );

        if ( surface == NULL ) {

            SDL_Log( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
            return NULL;
        }
        
        SDL_Texture* texture = SDL_CreateTextureFromSurface( gRenderer, surface );
        SDL_FreeSurface( surface );

        return texture;
    }

    bool
    collide( SDL_Rect& rect1, SDL_Rect& rect2 ) {

        if ( (rect1.x < rect2.x) && (rect1.x + rect1.w  < rect2.x) ) {

            return false;
        }
        else if ( (rect1.y < rect2.y) && (rect1.y + rect1.h < rect2.y) ) {

            return false;
        }
        else if (  rect1.y > (rect2.y + rect2.h) ) {

            return false;
        }
        else if ( rect1.x > (rect2.x + rect2.w) ) {

            return false;
        }

        return true;
    }
}

#endif