#include <string>
#include <SDL.h>

#ifndef ANIMATION_H
#define ANIMATION_H

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