#include <SDL.h>
#include <string>

#ifndef IMAGE_HPP
#define IMAGE_HPP

class Image {

public:
    
    int width {0};
    int height {0};
    SDL_Texture* texture;

    Image( std::string aPath ) {

        SDL_Surface* surface = IMG_Load( aPath.c_str() );

        if ( surface == NULL ) {

            SDL_Log( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
        }
        else {

            this->width = surface->w;
            this->height = surface->h;
            this->texture = SDL_CreateTextureFromSurface( gRenderer, surface );
            SDL_FreeSurface( surface );
        }
    }

    ~Image() {

        SDL_DestroyTexture( this->texture );
    }
};

#endif