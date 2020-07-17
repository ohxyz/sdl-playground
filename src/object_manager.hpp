#include "object2d.hpp"
#include "helpers.hpp"
#include "chicken.hpp"
#include <vector>
#include <SDL.h>
#include "scrollable.hpp"
#include "random_object.hpp"

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class ObjectManager {
    
    Scrollable* mDesert {nullptr};
    Scrollable* mLand {nullptr};
    Scrollable* mWaterTop {nullptr};
    Scrollable* mWaterBody {nullptr};
    Object2D* mRestartButton {nullptr};
    Chicken* mChicken {nullptr};

    std::vector<RandomObject*> mRandomSpikes;

    int mTicksOfNewSpike;
    int mTicksBeforeAddSpike;

    int mLandStep;
    unsigned int mLandInterval;

    int mChickenFrameDuration;
    bool mIsFrozen {false};

public:

    ObjectManager() {

        mDesert = new Scrollable( 
            0, 0, 676, 380, "images/desert.png",
            {.direction=Direction::Left, .step=1, .interval=10 }
        );

        mLand = new Scrollable(
            0, 360, 360, 150, "images/land.png", { 0, 0, 90, 135 },
            {.direction=Direction::Left, .step=2, .interval=10 }
        );
        
        mWaterTop = new Scrollable(
            0, 440, 360, 45, "images/water-top.png", { 0, 0, 60, 45 },
            {.direction=Direction::Left, .step=1, .interval=20 }
        );

        mWaterBody = new Scrollable(
            0, 485, 360, 999, "images/water-body.png", { 0, 0, 60, 60 },
            {.direction=Direction::Left, .step=1, .interval=20 }
        );

        mChicken = new Chicken();
        mRestartButton = new Object2D( 120, 400, 120, 120, "images/restart.png" );

        RandomObject::init();
        init();
    }

    ~ObjectManager() {

        delete mChicken;
        delete mLand;
        delete mWaterTop;
        delete mWaterBody;
        delete mDesert;
        mRandomSpikes.clear();
    }
    
    void
    init() {

        mLandStep = 5;
        mLandInterval = 10;
        mChickenFrameDuration = 20;
        mTicksBeforeAddSpike = 3000;
        mRestartButton->setShouldRender( false );

        mDesert->setX( 0 );
        mDesert->startMove();
        
        mLand->setX( 0 );
        mLand->setMovementStep( mLandStep );
        mLand->setMovementInterval( mLandInterval );
        mLand->startMove();

        mWaterTop->setX( 0 );
        mWaterTop->startMove();

        mWaterBody->setX( 0 );
        mWaterBody->startMove();

        mChicken->init();
        mChicken->setFrameDuration( mChickenFrameDuration );

        mRandomSpikes.clear();

        mTicksOfNewSpike = SDL_GetTicks();
        mIsFrozen = false;
    }

    void manageSpikes() {

        if ( mIsFrozen ) return;

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mTicksBeforeAddSpike > mTicksOfNewSpike ) {

            auto spike = new RandomObject( 360, 362 );

            spike->setMovement( { 
                .direction=Direction::Left, .step=mLandStep, .interval=mLandInterval
            } );

            spike->startMove();
            mRandomSpikes.push_back( spike );

            spike = mRandomSpikes[0];

            if ( spike->getX() + spike->getWidth() < 0 ) {

                mRandomSpikes.erase( mRandomSpikes.begin() );
                delete spike;
            }

            mTicksOfNewSpike = currentTicks;
        }

        for ( auto &spike : mRandomSpikes ) {

            if ( spike->collide( mChicken ) ) handleCollide();
        }
    }

    void
    handleCollide() {

        mChicken->hurt();
        mDesert->stopMove();
        mLand->stopMove();
        mWaterTop->stopMove();
        mWaterBody->stopMove();
        for ( auto &ro : mRandomSpikes ) ro->stopMove();
        mIsFrozen = true;
        mRestartButton->setShouldRender( true );
    }

    void 
    run() {

        manageSpikes();

        mDesert->render();
        mLand->render();
        mWaterTop->render();
        mWaterBody->render();
        for ( auto &spike: mRandomSpikes ) spike->render();
        mChicken->render();
        mRestartButton->render();
    }

    Chicken*
    getChicken() { return mChicken; }

    Object2D*
    getRestartButton() { return mRestartButton; }

    bool
    isFrozen() { return mIsFrozen; }
};

#endif