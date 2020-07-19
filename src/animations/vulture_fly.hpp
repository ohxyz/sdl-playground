#include <string>
#include <iostream>
#include <vector>
#include "../frame.hpp"
#include "../animation.hpp"
#include "../sprite.hpp"

#ifndef ANIMATIONS_VULTURE_FLY_HPP
#define ANIMATIONS_VULTURE_FLY_HPP

class VultureFlyAnimation : public Animation {

    Sprite* mSprite;

public:

    VultureFlyAnimation( int aX=0, int aY=0 ) {

        mSprite = new Sprite( 
            "images/vulture/__vulture_face_one_flying.png",
            { .x=0, .y=0, .w=520, .h=511 }, 
            4,
            4
        );

        auto frames = mSprite->createFrames( aX, aY, 20 );

        for ( auto& frame : frames ) {

            frame.setHitbox( 30, 20, 45, 10 );
            frame.setHitboxColor( 0, 0, 0, 100 );
        }

        setFrames( frames );
    }

    ~VultureFlyAnimation() {

        delete mSprite;
    }
};

#endif