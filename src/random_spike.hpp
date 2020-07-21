#include <SDL.h>
#include "object2d.hpp"
#include <vector>
#include "helpers.hpp"
#include "image.hpp"
#include "utils.hpp"
#include "random_object.hpp"

#ifndef RANDOM_SPIKE_HPP
#define RANDOM_SPIKE_HPP

class RandomSpike : public RandomObject {

    static std::vector<Image*> mPrimarySpikeImages;
    static std::vector<Image*> mSecondarySpikeImages;

public:

    RandomSpike( int aX, int aY, float secondarySpikePercentage=0.5 )
    : RandomObject( 
        aX, 
        aY, 
        &mPrimarySpikeImages, 
        &mSecondarySpikeImages, 
        secondarySpikePercentage 
    ) {

    }

    static void
    init() {

        mPrimarySpikeImages = {
            new Image( "images/obstacles/obstacle-0-0.png" ),
            new Image( "images/obstacles/obstacle-0-1.png" ),
            new Image( "images/obstacles/obstacle-0-2.png" )
        };

        mSecondarySpikeImages = {
            new Image( "images/obstacles/obstacle-1-0.png" ),
            new Image( "images/obstacles/obstacle-1-1.png" ),
            new Image( "images/obstacles/obstacle-1-2.png" )
        };
    }

    static void
    destroy() {

        mPrimarySpikeImages.clear();
        mSecondarySpikeImages.clear();
    }
};

std::vector<Image*> RandomSpike::mPrimarySpikeImages = {};
std::vector<Image*> RandomSpike::mSecondarySpikeImages = {};

#endif