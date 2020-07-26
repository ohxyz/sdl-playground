#include "object2d.hpp"
#include "helpers.hpp"
#include "chicken.hpp"
#include <SDL.h>
#include "scrollable.hpp"
#include "random_spike.hpp"
#include "spawner.hpp"
#include "bird.hpp"
#include "timer.hpp"
#include "utils.hpp"

#ifndef GAME_RUNNER_HPP
#define GAME_RUNNER_HPP

class GameRunner {
    
    Scrollable* mDesert {nullptr};
    Scrollable* mLand {nullptr};
    Scrollable* mWaterTop {nullptr};
    Scrollable* mWaterBody {nullptr};
    Object2D* mRestartButton {nullptr};
    Chicken* mChicken {nullptr};

    Spawner<RandomSpike>* mSpikeSpawner {nullptr};
    Spawner<Bird>* mBirdSpawner {nullptr};

    bool mIsFrozen {false};

    std::vector<Image*> mPrimarySpikeImages;
    std::vector<Image*> mSecondarySpikeImages;

    Timer* mSpawnTimer;

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

        RandomSpike::init();
        mSpikeSpawner = new Spawner<RandomSpike>( 360, 362 );

        // Near collide of y is around 200, 4, 7,
        mBirdSpawner = new Spawner<Bird>( {360, 360}, {4, 7, 40}, {300, 400, 10} );
        mSpawnTimer = new Timer();

        init();
    }

    ~GameRunner() {

        delete mChicken;
        delete mLand;
        delete mWaterTop;
        delete mWaterBody;
        delete mDesert;
        delete mSpikeSpawner;
        mPrimarySpikeImages.clear();
        mSecondarySpikeImages.clear();

        delete mSpawnTimer;
    }
    
    void
    init() {

        // At begining of the game, set a fixe value to spawn
        mSpawnTimer->start( 2000 );

        // Land and spikes have same movement.
        Move landMovement = { .direction=Direction::Left, .step=5, .interval=10 };
        Move birdMovement = { .direction=Direction::Left, .step=6, .interval=10 };
        
        mRestartButton->setShouldRender( false );

        mDesert->setX( 0 );
        mDesert->startMove();
        
        mLand->setX( 0 );
        mLand->setMovement( landMovement );
        mLand->startMove();

        mWaterTop->setX( 0 );
        mWaterTop->startMove();

        mWaterBody->setX( 0 );
        mWaterBody->startMove();

        mChicken->init();

        mBirdSpawner->clear();

        mSpikeSpawner->clear();
        mSpikeSpawner->setObjectMovement( landMovement );

        mBirdSpawner->clear();
        mBirdSpawner->setObjectMovement( birdMovement );

        mIsFrozen = false;
    }

    void
    detectCollision() {

        for ( auto& spike : mSpikeSpawner->getObjects() ) {

            if ( spike->collide( mChicken ) ) handleCollide();
        }

        for ( auto& bird: mBirdSpawner->getObjects() ) {
            
            if ( bird->collide( mChicken ) ) handleCollide();
        }
    }

    void
    handleCollide() {

        mChicken->hurt();
        mDesert->stopMove();
        mLand->stopMove();
        mWaterTop->stopMove();
        mWaterBody->stopMove();
        mSpikeSpawner->stopAutoSpawn();
        mBirdSpawner->stopAutoSpawn();
        mIsFrozen = true;
        mRestartButton->setShouldRender( true );
    }

    void
    spawn() {

        if ( mSpawnTimer->isTimeOut() ) {

            int which = utils::genRandomInt( 0, 1 );

            if ( which == 0 ) {

                mBirdSpawner->spawn();
            }
            else if ( which == 1 ) {

                mSpikeSpawner->spawn();
            }

            mSpawnTimer->reset( utils::genRandomInt( 3, 5 ) * 410 );
        }
    }

    void 
    run() {

        if ( !mIsFrozen ) {

            detectCollision();
            spawn();
        }

        mDesert->render();
        mLand->render();
        mWaterTop->render();
        mWaterBody->render();
        mSpikeSpawner->renderObjects();
        mBirdSpawner->renderObjects();
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