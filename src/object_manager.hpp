#include "object2d.hpp"
#include "helpers.hpp"
#include "chicken.hpp"
#include <vector>
#include <SDL.h>
#include "scrollable.hpp"

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class ObjectManager {
    
    Scrollable* mDesert {NULL};
    Scrollable* mLand {NULL};
    Scrollable* mWaterTop {NULL};
    Scrollable* mWaterBody {NULL};
    Object2D* mRestartButton {NULL};
    Chicken* mChicken {NULL};
    std::vector<Object2D*> mObstacles;

    int mTicksOfNewObstacle;
    int mTicksBeforeAddObstacle;

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

        init();
    }

    ~ObjectManager() {

        delete mChicken;
        delete mLand;
        delete mWaterTop;
        delete mWaterBody;
        delete mDesert;
        mObstacles.clear();
    }
    
    void
    init() {

        mLandStep = 5;
        mLandInterval = 10;
        mChickenFrameDuration = 20;
        mTicksBeforeAddObstacle = 3000;
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

        mObstacles.clear();

        mTicksOfNewObstacle = SDL_GetTicks();
        mIsFrozen = false;
    }

    void
    manageObstacles() {

        if ( mIsFrozen ) return;

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mTicksBeforeAddObstacle > mTicksOfNewObstacle ) {

            auto obstacle = new Object2D( 360, 289, 40, 72, "images/obstacle-3.png" );

            obstacle->setMovement( { 
                .direction=Direction::Left, .step=mLandStep, .interval=mLandInterval
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
        mDesert->stopMove();
        mLand->stopMove();
        mWaterTop->stopMove();
        mWaterBody->stopMove();
        for ( auto obstacle : mObstacles ) obstacle->stopMove();
        mIsFrozen = true;
        mRestartButton->setShouldRender( true );
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

        mDesert->render();
        mLand->render();
        mWaterTop->render();
        mWaterBody->render();
        for ( auto obs : mObstacles ) obs->render();
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