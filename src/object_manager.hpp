#include "object2d.hpp"
#include "helpers.h"
#include "chicken.hpp"
#include "obstacle.hpp"
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
    std::vector<Obstacle*> mObstacles;

    int mTicksOfNewObstacle;
    int mTicksBeforeAddObstacle;
    int mLandStep;
    int mLandFrameDuration;
    int mChickenFrameDuration;
    bool mIsFrozen {false};

public:

    ObjectManager() {

        mSky = new Object2D( 0, 0, 360, 431, "images/sky.png" );
        mLand = new Land();
        mChicken = new Chicken();

        init();
    }

    ~ObjectManager() {

        delete mSky;
        delete mLand;
        delete mChicken;
        mObstacles.clear();
    }
    
    void
    init() {

        mLandStep = 5;
        mLandFrameDuration = 10;
        mChickenFrameDuration = 30;
        mTicksBeforeAddObstacle = 3000;

        mLand->init();
        mLand->setStep( mLandStep );
        mLand->setCurrentFrameDuration( mLandFrameDuration );

        mChicken->init();
        mChicken->setFrameDuration( mChickenFrameDuration );

        mObstacles.clear();

        mTicksOfNewObstacle = SDL_GetTicks();
        mIsFrozen = false;
    }

    void
    manageObstacles() {

        if ( mIsFrozen ) return;

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mTicksBeforeAddObstacle > mTicksOfNewObstacle ) {

            auto obstacle = new Obstacle();
            mObstacles.push_back( obstacle );
            obstacle->setStep( mLandStep );
            obstacle->setCurrentFrameDuration( mLandFrameDuration );

            obstacle = mObstacles[0];
            auto obstacleFrame = obstacle->getCurrentFrame();

            if ( obstacleFrame->x + obstacleFrame->width < 0 ) {

                mObstacles.erase( mObstacles.begin() );
                delete obstacle;
            }

            mTicksOfNewObstacle = currentTicks;
        }

        for ( auto obstacle : mObstacles ) {

            if ( collide(obstacle, mChicken) ) handleCollide();
        }
    }

    void
    handleCollide() {

        mChicken->hurt();
        mLand->setStep(0);
        for ( auto obstacle : mObstacles ) obstacle->setStep(0);
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

        manageObstacles();

        mSky->render();
        mLand->render();
        for ( auto obs : mObstacles ) obs->render();
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