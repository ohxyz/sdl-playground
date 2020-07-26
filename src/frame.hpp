#include <SDL.h>
#include <string>
#include "game.hpp"
#include "structs.hpp"
#include "image.hpp"

#ifndef FRAME_HPP
#define FRAME_HPP

extern SDL_Renderer* gRenderer;

class Frame {

public:

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

    Frame() {

        
    }

    Frame( int aX, int aY, int aW, int aH, SDL_Texture* aTexture ) {

        this->x = aX;
        this->y = aY;
        this->width = aW;
        this->height = aH;
        this->imageTexture = aTexture;

        this->imageClipWidth = aW;
        this->imageClipHeight = aH;
    }

    void 
    renderBorder() {

        auto rect = getRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            this->borderColorR, 
            this->borderColorG, 
            this->borderColorB,
            this->borderColorA 
        );
        SDL_RenderDrawRect( gRenderer, &rect );
    }
    
    void
    renderBackground() {

        auto rect = getRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            this->backgroundColorR, 
            this->backgroundColorG, 
            this->backgroundColorB, 
            this->backgroundColorA
        );
        SDL_RenderFillRect( gRenderer, &rect );
    }

    void 
    renderHitbox() {

        auto rect = getHitboxRect();
        SDL_SetRenderDrawColor( 
            gRenderer,
            this->hitboxColorR, 
            this->hitboxColorG, 
            this->hitboxColorB,
            this->hitboxColorA 
        );
        SDL_RenderFillRect( gRenderer, &rect );
    }

    void 
    renderImage() {

        if ( this->imageTexture == NULL ) {
            return;
        }

        int targetWidth = this->imageClipWidth > this->width  
                        ? this->width 
                        : this->imageClipWidth;

        int targetHeight = this->imageClipHeight > this->height
                         ? this->height
                         : this->imageClipHeight;

        SDL_Rect clipRect = {
            this->imageClipX,
            this->imageClipY,
            targetWidth,
            targetHeight
        };

        SDL_Rect targetRect = {
            this->x,
            this->y,
            targetWidth,
            targetHeight
        };

        while ( true ) {

            // Repeat on x-axis
            while ( true ) {

                SDL_RenderCopyEx( 
                    gRenderer, 
                    this->imageTexture,
                    &clipRect,
                    &targetRect,
                    0, 
                    NULL, 
                    this->imageClipFlip
                );

                if ( !this->imageClipRepeatX ) {
                    break;
                }

                targetRect.x += this->imageClipWidth;

                if ( targetRect.x > this->x + this->width ) {
                    break;
                }

                if ( targetRect.x + this->imageClipWidth > this->x + this->width ) {
                    targetRect.w = this->x + this->width - targetRect.x;
                    clipRect.w = targetRect.w;
                }
                else {
                    targetRect.w = this->imageClipWidth;
                }
            }

            if ( !this->imageClipRepeatY ) {
                break;
            }

            // Repeat on y-axis
            // Reset
            targetRect.x = this->x;
            targetRect.w = targetWidth;
            clipRect.w = targetWidth;

            targetRect.y += this->imageClipHeight;

            if ( targetRect.y > this->y + this->height ) {
                break;
            }

            if ( targetRect.y + this->imageClipHeight > this->y + this->height ) {
                targetRect.h = this->y + this->height - targetRect.y;
                clipRect.h = targetRect.h;
            }
            else {
                targetRect.h = this->imageClipHeight;
            }
        }
    }

    bool
    isWithinRect( int aX, int aY ) {

        return ( aX >= this->x && aX <= this->x + this->width
            && aY >= this->y && aY <= this->y + this->height
        );
    }

    SDL_Rect
    getRect() {

        SDL_Rect rect = { this->x, this->y, this->width, this->height };

        return rect;
    }

    SDL_Rect
    getHitboxRect() {

        SDL_Rect rect = {
            this->x + this->hitboxLeft,
            this->y + this->hitboxTop,
            this->width - this->hitboxRight - this->hitboxLeft,
            this->height - this->hitboxBottom - this->hitboxTop
        };

        return rect;
    }

    void
    setHitbox( int aTop, int aRight, int aBottom, int aLeft ) {

        this->hitboxTop = aTop;
        this->hitboxRight = aRight;
        this->hitboxBottom = aBottom;
        this->hitboxLeft = aLeft;
    }

    void
    setHitboxColor( int aR, int aG, int aB, int aA ) {

        this->hitboxColorR = aR;
        this->hitboxColorG = aG;
        this->hitboxColorB = aB;
        this->hitboxColorA = aA;
    }


    // Not tested
    void
    move( Direction aDirection, int aStep ) {

        if ( aDirection == Direction::None || aStep == 0 ) return;

        switch ( aDirection ) {

        case Direction::Up:
            this->y -= aStep;
            break;

        case Direction::Right:
            this->x += aStep;
            break;

        case Direction::Down:
            this->y += aStep;
            break;

        case Direction::Left:
            this->x -= aStep;
            break;

        case Direction::None:
            break;
        }
    }
};

#endif