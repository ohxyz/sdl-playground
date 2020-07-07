#include "object2d.hpp"
#include "helpers.h"
#include "chicken.hpp"
#include "cactus.hpp"
#include "land.hpp"
#include <vector>
#include <SDL.h>
#include <iostream>

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class ObjectManager {

    Object2D* mSky;
    Land* mLand;
    Chicken* mChicken;
    std::vector<Cactus*> mCactuses;

    int mTicksOfNewCactus;
    int mTicksBeforeAddCactus;
    int mLandStep;
    int mLandFrameDuration;
    int mChickenFrameDuration;
    bool mIsFrozen {false};

public:

    ObjectManager() {

        mSky = new Object2D( 0, 0, 360, 470, "images/sky.png" );
        mLand = new Land();
        mChicken = new Chicken();

        init();        
    }

    ~ObjectManager() {

        delete mSky;
        delete mLand;
        delete mChicken;
        for ( auto c : mCactuses ) delete c;
    }
    
    void
    init() {

        mLandStep = 5;
        mLandFrameDuration = 10;
        mChickenFrameDuration = 30;
        mTicksBeforeAddCactus = 3000;

        mLand->init();
        mLand->setStep( mLandStep );
        mLand->setCurrentFrameDuration( mLandFrameDuration );

        mChicken->init();
        mChicken->setFrameDuration( mChickenFrameDuration );

        mCactuses.clear();

        mTicksOfNewCactus = SDL_GetTicks();
        mIsFrozen = false;
    }

    void
    manageCactuses() {

        if ( mIsFrozen ) return;

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mTicksBeforeAddCactus > mTicksOfNewCactus ) {

            auto cactus = new Cactus();
            mCactuses.push_back( cactus );
            cactus->setStep( mLandStep );
            cactus->setCurrentFrameDuration( mLandFrameDuration );

            cactus = mCactuses[0];
            auto cactusFrame = cactus->getCurrentFrame();

            if ( cactusFrame->x + cactusFrame->width < 0 ) {

                mCactuses.erase( mCactuses.begin() );
                delete cactus;
            }

            mTicksOfNewCactus = currentTicks;
        }

        for ( auto cactus : mCactuses ) {

            if ( collide(cactus, mChicken) ) handleCollide();
        }
    }

    void
    handleCollide() {

        mChicken->hurt();
        mLand->setStep(0);
        for ( auto cactus : mCactuses ) cactus->setStep(0);
        mIsFrozen = true;
    }

    bool
    collide( Object2D* obj1, Object2D* obj2 ) {

        SDL_Rect rect1 = obj1->getCurrentHitboxRect();
        SDL_Rect rect2 = obj2->getCurrentHitboxRect();

        return helpers::collide( rect1, rect2 );
    }

    void 
    run() {

        manageCactuses();

        mSky->render();
        mLand->render();
        for ( auto c : mCactuses ) c->render();
        mChicken->render();
    }

    Chicken*
    getChicken() {

        return mChicken;
    }

    bool
    isFrozen() {

        return mIsFrozen;
    }
};

#endif