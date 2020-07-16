#include <SDL.h>
#include "object2d.hpp"
#include <vector>
#include "helpers.hpp"
#include "image.hpp"
#include "utils.hpp"

#ifndef RANDOM_OBSTACLE_HPP
#define RANDOM_OBSTACLE_HPP

class RandomObstacle {

public:

    static std::vector<Image*> mPrimaryObstacleImages;
    static std::vector<Image*> mSecondaryObstacleImages;

    Object2D* mPrimaryObstacle {nullptr};
    Object2D* mSecondaryObstacle {nullptr};

    bool mShouldSwap {false};
    bool mShouldRenderSecondary {true};

    int mMovementTicks;
    bool mIsMovementStarted;

    int mGap {0};

    RandomObstacle( int baseX=0, int baseY=0 ) {

        mShouldRenderSecondary = utils::genRandomBool();
        mGap = 25;

        auto imageOfPO = mPrimaryObstacleImages[ utils::genRandomInt(0,2) ];
        auto imageOfSO = mSecondaryObstacleImages[ utils::genRandomInt(0,2) ];

        if ( !mShouldRenderSecondary ) {

            mPrimaryObstacle = new Object2D( 
                baseX, 
                baseY - imageOfPO->height, 
                imageOfPO->width, 
                imageOfPO->height, 
                imageOfPO->texture
            );
        }
        else {

            mSecondaryObstacle = new Object2D( 
                baseX, 
                baseY - imageOfSO->height, 
                imageOfSO->width, 
                imageOfSO->height, 
                imageOfSO->texture
            );

            int xOfPO = baseX + mGap;
            int yOfPO = baseY - imageOfPO->height;

            mPrimaryObstacle = new Object2D( 
                xOfPO, 
                yOfPO, 
                imageOfPO->width, 
                imageOfPO->height, 
                imageOfPO->texture
            );

            mSecondaryObstacle->setHitboxColor( 0, 0, 0, 150 );
            mSecondaryObstacle->setHitbox( 5, 0, 0, 10 );
        }

        mPrimaryObstacle->setHitboxColor( 0, 0, 0, 150 );
        mPrimaryObstacle->setHitbox( 10, 5, 0, 5 );

        mShouldSwap = utils::genRandomBool();
    }

    ~RandomObstacle() {

        delete mPrimaryObstacle;
        delete mSecondaryObstacle;
    }

    static void
    init() {

        mPrimaryObstacleImages = { 
            new Image( "images/obstacles/obstacle-0-0.png" ),
            new Image( "images/obstacles/obstacle-0-1.png" ),
            new Image( "images/obstacles/obstacle-0-2.png" ),
        };

        mSecondaryObstacleImages = {
            new Image( "images/obstacles/obstacle-1-0.png" ),
            new Image( "images/obstacles/obstacle-1-1.png" ),
            new Image( "images/obstacles/obstacle-1-2.png" ),
        };
    }

    static void
    destroy() {

        mPrimaryObstacleImages.clear();
        mSecondaryObstacleImages.clear();
    }

    bool
    collide( Object2D* obj ) {

        auto hitboxOfObj = obj->getHitboxRect();
        auto hitboxOfPO = mPrimaryObstacle->getHitboxRect();

        if ( !mShouldRenderSecondary ) {
            return helpers::collide( hitboxOfObj, hitboxOfPO );
        }

        auto hitboxOfSO = mSecondaryObstacle->getHitboxRect();

        return (
            helpers::collide( hitboxOfObj, hitboxOfPO ) 
            || helpers::collide( hitboxOfObj, hitboxOfSO )
        ); 
    }

    void
    renderPrimaryObstacle() {

        if ( mPrimaryObstacle != nullptr ) {

            // mPrimaryObstacle->renderHitbox();
            mPrimaryObstacle->renderImage();
        } 
    }

    void
    renderSecondarySecondary() {

        if ( mPrimaryObstacle != nullptr && mShouldRenderSecondary ) {

            // mSecondaryObstacle->renderHitbox();
            mSecondaryObstacle->renderImage();
        }
    }

    void    
    render() {

        if ( mIsMovementStarted ) move();

        if ( mShouldSwap ) {

            renderPrimaryObstacle();
            renderSecondarySecondary();
        }
        else {

            renderSecondarySecondary();
            renderPrimaryObstacle();
        }
    }

    void
    startMove() {

        mIsMovementStarted = true;
    }

    void
    stopMove() {

        mIsMovementStarted = false;
    }

    void
    move() {

        mPrimaryObstacle->move();
        if ( mShouldRenderSecondary ) mSecondaryObstacle->move();
    }

    void
    setMovement( Move move ) { 
        
        mPrimaryObstacle->setMovement( move );
        if ( mShouldRenderSecondary ) mSecondaryObstacle->setMovement( move );
    }

    int
    getX() {

        if ( mShouldRenderSecondary ) {
            return mSecondaryObstacle->getX();
        }

        return mPrimaryObstacle->getX();
    }

    int
    getWidth() {

        if ( mShouldRenderSecondary ) {
            return mSecondaryObstacle->getWidth() + mGap + mPrimaryObstacle->getWidth();
        }

        return mPrimaryObstacle->getWidth();
    }

    Object2D*
    getPrimaryObstacle() { return mPrimaryObstacle; }

    Object2D*
    getSecondaryObstacle() { return mSecondaryObstacle; }
};

std::vector<Image*> RandomObstacle::mPrimaryObstacleImages = {};
std::vector<Image*> RandomObstacle::mSecondaryObstacleImages = {};


#endif