#include <SDL.h>

#ifndef FRAME_H
#define FRAME_H

struct Frame {

    int x;
    int y;
    int width;
    int height;

    uint8_t backgroundColorR {0};
    uint8_t backgroundColorG {0};
    uint8_t backgroundColorB {0};
    uint8_t backgroundColorA {0};

    uint8_t borderColorR {0};
    uint8_t borderColorG {0};
    uint8_t borderColorB {0};
    uint8_t borderColorA {0};

    int imageClipX {0};
    int imageClipY {0};
    int imageClipWidth;
    int imageClipHeight;
    SDL_RendererFlip imageClipFlip { SDL_FLIP_NONE };
    SDL_Texture* imageTexture {NULL};

    int duration {1000};
};

#endif