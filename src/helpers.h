#include <string>
#include <SDL.h>

#ifndef HELPERS_H
#define HELPERS_H

bool initGame();

namespace helpers {

    SDL_Texture* loadTexture( std::string );
    bool collide( SDL_Rect&, SDL_Rect& );
}

#endif