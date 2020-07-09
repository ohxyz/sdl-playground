#include "object2d.hpp"
#include "helpers.h"
#include "chicken.hpp"
#include "land.hpp"
#include <vector>
#include <SDL.h>
#include <iostream>
#include "background.hpp"

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class ObjectManager {

    Background* mSky;
    Background* mStars;
    Background* mMountain;
    Land* mLand;
    Chicken* mChicken;
    std::vector<Object2D*> mObstacles;

    int mTicksOfNewObstacle;
    int mTicksBeforeAddObstacle;
    int mLandStep;
    
    unsigned int mLandFrameDuration;
    int mChickenFrameDuration;
    bool mIsFrozen {false};

public:

    ObjectManager() {

        mSky = new Background( 0, 0, 360, 431, "images/sky.png" );

        mStars = new Background( 
            0, 15, 540, 149, "images/stars.png",
            { .direction=Direction::Left, .step=1, .interval=10 }
        );

        mMountain = new Background( 
            0, 230, 960, 232, "images/mountain.png", 
            {.direction=Direction::Left, .step=2, .interval=10 } 
        );
        
        mLand = new Land();
        mChicken = new Chicken();

        init();
    }

    ~ObjectManager() {

        delete mSky;
        delete mStars;
        delete mMountain;
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

        mStars->setX( 0 );
        mStars->startMove();

        mMountain->setX( 0 );
        mMountain->startMove();

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

            auto obstacle = new Object2D( 360, 340, 40, 75, "images/obstacle-1.png" );

            obstacle->setMovement( { 
                .direction=Direction::Left, .step=mLandStep, .interval=mLandFrameDuration
            } );
            obstacle->setHitbox( 5, 5, 0, 5 );
            obstacle->startMove();
            mObstacles.push_back( obstacle );

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
        mMountain->stopMove();
        mStars->stopMove();
        for ( auto obstacle : mObstacles ) obstacle->stopMove();
        mIsFrozen = true;
    }

    bool
    collide( Object2D* obj1, Object2D* obj2 ) {

        SDL_Rect rect1 = obj1->getHitboxRect();
        SDL_Rect rect2 = obj2->getHitboxRect();

        return helpers::collide( rect1, rect2 );
    }

    void 
    run() {

        manageObstacles();

        mSky->render();
        mStars->render();
        mMountain->render();
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