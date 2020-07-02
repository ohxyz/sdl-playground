#include "helpers.hpp"
#include <SDL_image.h>

extern SDL_Renderer* gRenderer;

SDL_Texture* loadTexture( std::string imagePath ) {

    SDL_Surface* surface = IMG_Load( imagePath.c_str() );

    if ( surface == NULL ) {

        printf( "Failed to load image. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface( gRenderer, surface );
    SDL_FreeSurface( surface );

    return texture;
}