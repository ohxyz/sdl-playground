#include <SDL.h>

#ifndef FRAME_H
#define FRAME_H

struct Frame {

    int x;
    int y;
    int width;
    int height;

    int imageClipX {0};
    int imageClipY {0};
    int imageClipWidth;
    int imageClipHeight;
    SDL_RendererFlip imageClipFlip { SDL_FLIP_NONE };

    int backgroundColorR {0};
    int backgroundColorG {0};
    int backgroundColorB {0};
    int backgroundColorA {0};

    SDL_Texture* imageTexture {NULL};
};

#endif