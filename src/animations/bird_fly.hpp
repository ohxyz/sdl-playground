#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../animation.hpp"
#include "../sprite.hpp"

#ifndef ANIMATIONS_BIRD_FLY_HPP
#define ANIMATIONS_BIRD_FLY_HPP

class BirdFlyAnimation : public Animation {

    Sprite* mSprite;

public:

    BirdFlyAnimation( int aX=0, int aY=0 ) {

        mSprite = new Sprite( 
            "images/bird/__red_flying_bird_3_flying.png",
            { .x=0, .y=0, .w=492, .h=223 }, 
            4,
            2
        );

        auto frames = mSprite->createFrames( aX, aY, 20 );

        for ( auto frame : frames ) {

            frame->setHitboxRect( 50, 25, 40, 25 );
            frame->setHitboxColor( 0, 0, 0, 100 );
        }

        setFrames( frames );
    }

    ~BirdFlyAnimation() {

        delete mSprite;
    }

};

#endif