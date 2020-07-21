#include "object2d.hpp"
#include "helpers.hpp"
#include "chicken.hpp"
#include <SDL.h>
#include "scrollable.hpp"
#include "random_object.hpp"
#include "object_manager.hpp"

#ifndef GAME_RUNNER_HPP
#define GAME_RUNNER_HPP

void f1() { SDL_Log( "collide!" ); }

class GameRunner {
    
    Scrollable* mDesert {nullptr};
    Scrollable* mLand {nullptr};
    Scrollable* mWaterTop {nullptr};
    Scrollable* mWaterBody {nullptr};
    Object2D* mRestartButton {nullptr};
    Chicken* mChicken {nullptr};

    ObjectManager<RandomObject>* mSpikeManager {nullptr};
    Move mSpikeMovement;
    int mSpikeSpawnInterval;

    int mLandStep;
    unsigned int mLandInterval;

    int mChickenFrameDuration;
    bool mIsFrozen {false};

public:

    GameRunner() {

        mDesert = new Scrollable( 
            0, 0, 676, 380, "images/desert.png",
            {.direction=Direction::Left, .step=1, .interval=10 }
        );

        mLand = new Scrollable(
            0, 360, 360, 150, "images/land.png", { 0, 0, 90, 135 },
            {.direction=Direction::Left, .step=5, .interval=10 }
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

        mSpikeManager = new ObjectManager<RandomObject>( 360, 362 );

        RandomObject::addPrimaryImage( new Image( "images/obstacles/obstacle-0-0.png" ) );
        RandomObject::addPrimaryImage( new Image( "images/obstacles/obstacle-0-1.png" ) );
        RandomObject::addPrimaryImage( new Image( "images/obstacles/obstacle-0-2.png" ) );
        RandomObject::addSecondaryImage( new Image( "images/obstacles/obstacle-1-0.png" ) );
        RandomObject::addSecondaryImage( new Image( "images/obstacles/obstacle-1-1.png" ) );
        RandomObject::addSecondaryImage( new Image( "images/obstacles/obstacle-1-2.png" ) );

        init();
    }

    ~GameRunner() {

        delete mChicken;
        delete mLand;
        delete mWaterTop;
        delete mWaterBody;
        delete mDesert;
        delete mSpikeManager;
    }
    
    void
    init() {

        mLandStep = 5;
        mLandInterval = 10;
        mChickenFrameDuration = 20;

        mSpikeMovement = { .direction=Direction::Left, .step=mLandStep, .interval=mLandInterval };
        mSpikeSpawnInterval = 3000;
        
        mRestartButton->setShouldRender( false );

        mDesert->setX( 0 );
        mDesert->startMove();
        
        mLand->setX( 0 );
        mLand->setMovement( mSpikeMovement );
        mLand->startMove();

        mWaterTop->setX( 0 );
        mWaterTop->startMove();

        mWaterBody->setX( 0 );
        mWaterBody->startMove();

        mChicken->init();
        mChicken->setFrameDuration( mChickenFrameDuration );

        mSpikeManager->clear();
        mSpikeManager->setMovement( mSpikeMovement );
        mSpikeManager->setSpawnInterval( mSpikeSpawnInterval );
        mSpikeManager->startMove();

        mIsFrozen = false;
    }

    void
    detectCollision() {

        for ( auto& obj : *mSpikeManager->getObjects() ) {

            if ( obj->collide( mChicken ) ) handleCollide();
        }
    }

    void
    handleCollide() {

        mChicken->hurt();
        mDesert->stopMove();
        mLand->stopMove();
        mWaterTop->stopMove();
        mWaterBody->stopMove();
        mSpikeManager->stopMove();
        mIsFrozen = true;
        mRestartButton->setShouldRender( true );
    }

    void 
    run() {

        if ( !mIsFrozen ) {

            detectCollision();
            mSpikeManager->move();
        }

        mDesert->render();
        mLand->render();
        mWaterTop->render();
        mWaterBody->render();
        mSpikeManager->render();
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