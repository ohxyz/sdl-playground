#include <SDL.h>
#include "object2d.hpp"
#include <vector>
#include "helpers.hpp"
#include "image.hpp"
#include "utils.hpp"

#ifndef RANDOM_OBJECT_HPP
#define RANDOM_OBJECT_HPP

class RandomObject {

public:

    static std::vector<Image*> mPrimaryObjectImages;
    static std::vector<Image*> mSecondaryObjectImages;

    Object2D* mPrimaryObject {nullptr};
    Object2D* mSecondaryObject {nullptr};

    bool mShouldSwap {false};
    bool mShouldRenderSecondary {true};

    int mMovementTicks;
    bool mIsMovementStarted;
    Move mMovement;

    int mGap {0};

    RandomObject( int baseX=0, int baseY=0, float ratioOfSecondary=0.5 ) {

        mShouldRenderSecondary = utils::genRandomBool( ratioOfSecondary );
        mGap = 25;

        int countOfPrimary = mPrimaryObjectImages.size();
        int countOfSecondary = mSecondaryObjectImages.size();

        auto imageOfPO = mPrimaryObjectImages[ utils::genRandomInt(0, countOfPrimary-1) ];
        auto imageOfSO = mSecondaryObjectImages[ utils::genRandomInt(0, countOfSecondary-1) ];

        if ( !mShouldRenderSecondary ) {

            mPrimaryObject = new Object2D( 
                baseX, 
                baseY - imageOfPO->height, 
                imageOfPO->width, 
                imageOfPO->height, 
                imageOfPO->texture
            );
        }
        else {

            mSecondaryObject = new Object2D( 
                baseX, 
                baseY - imageOfSO->height, 
                imageOfSO->width, 
                imageOfSO->height, 
                imageOfSO->texture
            );

            int xOfPO = baseX + mGap;
            int yOfPO = baseY - imageOfPO->height;

            mPrimaryObject = new Object2D( 
                xOfPO, 
                yOfPO, 
                imageOfPO->width, 
                imageOfPO->height, 
                imageOfPO->texture
            );

            mSecondaryObject->setHitboxColor( 0, 0, 0, 150 );
            mSecondaryObject->setHitbox( 5, 0, 0, 10 );
        }

        mPrimaryObject->setHitboxColor( 0, 0, 0, 150 );
        mPrimaryObject->setHitbox( 5, 5, 0, 5 );

        mShouldSwap = utils::genRandomBool();
    }

    ~RandomObject() {

        delete mPrimaryObject;
        delete mSecondaryObject;
    }

    static void
    init() {

        mPrimaryObjectImages = { 
            new Image( "images/obstacles/obstacle-0-0.png" ),
            new Image( "images/obstacles/obstacle-0-1.png" ),
            new Image( "images/obstacles/obstacle-0-2.png" ),
        };

        mSecondaryObjectImages = {
            new Image( "images/obstacles/obstacle-1-0.png" ),
            new Image( "images/obstacles/obstacle-1-1.png" ),
            new Image( "images/obstacles/obstacle-1-2.png" ),
        };
    }

    static void
    destroy() {

        mPrimaryObjectImages.clear();
        mSecondaryObjectImages.clear();
    }

    bool
    collide( Object2D* target ) {

        auto hitboxOfTarget = target->getHitboxRect();
        auto hitboxOfPO = mPrimaryObject->getHitboxRect();

        if ( !mShouldRenderSecondary ) {
            return helpers::collide( hitboxOfTarget, hitboxOfPO );
        }

        auto hitboxOfSO = mSecondaryObject->getHitboxRect();

        return (
            helpers::collide( hitboxOfTarget, hitboxOfPO ) 
            || helpers::collide( hitboxOfTarget, hitboxOfSO )
        ); 
    }

    void
    renderPrimaryObject() {

        if ( mPrimaryObject != nullptr ) {

            mPrimaryObject->renderHitbox();
            mPrimaryObject->renderImage();
        } 
    }

    void
    renderSecondaryObject() {

        if ( mPrimaryObject != nullptr && mShouldRenderSecondary ) {

            mSecondaryObject->renderHitbox();
            mSecondaryObject->renderImage();
        }
    }

    void    
    render() {

        if ( mIsMovementStarted ) move();

        if ( mShouldSwap ) {

            renderPrimaryObject();
            renderSecondaryObject();
        }
        else {

            renderSecondaryObject();
            renderPrimaryObject();
        }
    }

    void
    startMove() {

        mMovementTicks = SDL_GetTicks();
        mIsMovementStarted = true;
    }

    void
    stopMove() {

        mIsMovementStarted = false;
    }

    void
    move() {

        int currentTicks = SDL_GetTicks();

        if ( currentTicks - mMovementTicks > mMovement.interval ) {
    
            mPrimaryObject->moveOnce();
            if ( mShouldRenderSecondary ) mSecondaryObject->moveOnce();
            
            mMovementTicks = currentTicks;
        }
    }

    void
    setMovement( Move move ) { 

        mMovement = move;
        mPrimaryObject->setMovement( move );
        if ( mShouldRenderSecondary ) mSecondaryObject->setMovement( move );
    }

    int
    getX() {

        if ( mShouldRenderSecondary ) {
            return mSecondaryObject->getX();
        }

        return mPrimaryObject->getX();
    }

    int
    getWidth() {

        if ( mShouldRenderSecondary ) {
            return mSecondaryObject->getWidth() + mGap + mPrimaryObject->getWidth();
        }

        return mPrimaryObject->getWidth();
    }

    Object2D*
    getPrimaryObject() { return mPrimaryObject; }

    Object2D*
    getSecondaryObject() { return mSecondaryObject; }
};

std::vector<Image*> RandomObject::mPrimaryObjectImages = {};
std::vector<Image*> RandomObject::mSecondaryObjectImages = {};


#endif