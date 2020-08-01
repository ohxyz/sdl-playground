#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "structs.hpp"

#ifndef HELPERS_HPP
#define HELPERS_HPP

extern SDL_Renderer* gRenderer;

namespace helpers {

    Direction
    getDirection( float distX, float distY, float min=1.0 ) {

        // SDL_Log( "@@ %f, %f, %f", distX, distY, min );

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
    collide( SDL_Rect rect1, SDL_Rect rect2 ) {

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

    // Note aX, aY are the coordinates of the container's top left point, not the center
    void
    fillCircle( int aX, int aY, int aRadius, SDL_Color aColor ) {

        SDL_SetRenderDrawColor( gRenderer, aColor.r, aColor.g, aColor.b, aColor.a );

        // center
        int cx = aX + aRadius;
        int cy = aY + aRadius;

        // line
        int lx1;
        int lx2;
        int ly;
        // horizontal width
        int hw;

        // Note dist starts with 1, for better rendering effect
        // Top and botttom lines(dots) are removed
        for ( int dist = 1; dist <= aRadius; dist ++ ) {

            hw = round( sqrt( pow( aRadius, 2 ) - pow( aRadius - dist, 2 ) ) );
            lx1 = cx - hw;
            lx2 = cx + hw;
            ly = aY + dist;

            SDL_RenderDrawLine( gRenderer, lx1, ly, lx2, ly );
        }

        for ( int dist = 1; dist < aRadius; dist ++ ) {

            hw = round( sqrt( pow( aRadius, 2 ) - pow( dist, 2 ) ) );
            lx1 = cx - hw;
            lx2 = cx + hw;
            ly = cy + dist;

            SDL_RenderDrawLine( gRenderer, lx1, ly, lx2, ly );
        }
    }

    void
    drawCircle( int aX, int aY, int aRadius, SDL_Color aColor ) {

        SDL_SetRenderDrawColor( gRenderer, aColor.r, aColor.g, aColor.b, aColor.a );

        // center
        int cx = aX + aRadius;
        int cy = aY + aRadius;

        // line
        int lx1;
        int lx2;
        int ly;
        // horizontal width
        int hw;

        // Note dist starts with 0, for better rendering effect
        // Top and bottom lines(dots) are kept
        for ( int dist = 0; dist < aRadius; dist ++ ) {

            hw = round( sqrt( pow( aRadius, 2 ) - pow( aRadius - dist, 2 ) ) );
            lx1 = cx - hw;
            lx2 = cx + hw;
            ly = aY + dist;

            SDL_RenderDrawPoint( gRenderer, lx1, ly );
            SDL_RenderDrawPoint( gRenderer, lx2, ly );
        }

        for ( int dist = 0; dist <= aRadius; dist ++ ) {

            hw = round( sqrt( pow( aRadius, 2 ) - pow( dist, 2 ) ) );
            lx1 = cx - hw;
            lx2 = cx + hw;
            ly = cy + dist;

            SDL_RenderDrawPoint( gRenderer, lx1, ly );
            SDL_RenderDrawPoint( gRenderer, lx2, ly );
        }
    }
}

#endif