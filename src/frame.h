#include <SDL.h>
#include <string>

#ifndef FRAME_H
#define FRAME_H

struct Frame {

    std::string         id {""};

    int                 x;
    int                 y;
    int                 width;
    int                 height;

    uint8_t             backgroundColorR {0};
    uint8_t             backgroundColorG {0};
    uint8_t             backgroundColorB {0};
    uint8_t             backgroundColorA {0};

    uint8_t             borderColorR {0};
    uint8_t             borderColorG {0};
    uint8_t             borderColorB {0};
    uint8_t             borderColorA {0};

    int                 imageClipX {0};
    int                 imageClipY {0};
    int                 imageClipWidth {0};
    int                 imageClipHeight {0};
    bool                imageClipRepeatX {true};
    bool                imageClipRepeatY {true};
    SDL_RendererFlip    imageClipFlip { SDL_FLIP_NONE };
    SDL_Texture*        imageTexture {NULL};

    int                 hitboxTop {0};
    int                 hitboxRight {0};
    int                 hitboxBottom {0};
    int                 hitboxLeft {0};
    uint8_t             hitboxColorR {0};
    uint8_t             hitboxColorG {0};
    uint8_t             hitboxColorB {0};
    uint8_t             hitboxColorA {0};

    int                 duration {1000};
};

#endif