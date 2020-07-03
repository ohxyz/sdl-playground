#include <string>
#include <SDL.h>

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation {

public:
    Animation();
    ~Animation();
    void init();
    void start();
    void stop();

private:

    bool mIsInitialized = false;
    SDL_Texture* mTexture;
};

#endif