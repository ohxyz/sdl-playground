#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <string.h>

#ifndef HELPERS_HPP
#define HELPERS_HPP

extern SDL_Renderer* gRenderer;

namespace helpers {

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