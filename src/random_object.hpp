#include <SDL.h>
#include "object2d.hpp"
#include <vector>
#include "helpers.hpp"
#include "image.hpp"
#include "utils.hpp"

#ifndef RANDOM_OBJECT_HPP
#define RANDOM_OBJECT_HPP

class RandomObject {

    std::vector<Image*>* mPrimaryImages;
    std::vector<Image*>* mSecondaryImages;

    Frame* mPrimaryFrame {nullptr};
    Frame* mSecondaryFrame {nullptr};

    bool mShouldSwap {false};
    bool mShouldRenderSecondary {true};

    int mMovementTicks;
    bool mIsMovementStarted;
    Move mMovement;

    int mGap {25};

public:

    RandomObject( 
        int baseX, 
        int baseY,
        std::vector<Image*>* aPrimaryImages,
        std::vector<Image*>* aSecondaryImages,
        float percentageOfSecondary=0.5
    ) {

        mPrimaryImages = aPrimaryImages;
        mSecondaryImages = aSecondaryImages;

        mShouldRenderSecondary = utils::genRandomBool( percentageOfSecondary );
        int countOfPrimary = (*mPrimaryImages).size();

        if ( countOfPrimary == 0 ) throw "ERROR: No primary object images found!";

        auto imageOfPO = (*mPrimaryImages)[ utils::genRandomInt(0, countOfPrimary-1) ];

        int countOfSecondary = (*mSecondaryImages).size();

        if ( !mShouldRenderSecondary || countOfSecondary == 0 ) {

            mPrimaryFrame = new Frame( 
                baseX, 
                baseY - imageOfPO->height, 
                imageOfPO->width, 
                imageOfPO->height, 
                imageOfPO->texture
            );
        }
        else {

            auto imageOfSO = (*mSecondaryImages)[ utils::genRandomInt(0, countOfSecondary-1) ];

            mSecondaryFrame = new Frame( 
                baseX, 
                baseY - imageOfSO->height, 
                imageOfSO->width, 
                imageOfSO->height, 
                imageOfSO->texture
            );

            int xOfPO = baseX + mGap;
            int yOfPO = baseY - imageOfPO->height;

            mPrimaryFrame = new Frame( 
                xOfPO, 
                yOfPO, 
                imageOfPO->width, 
                imageOfPO->height, 
                imageOfPO->texture
            );

            mSecondaryFrame->setHitboxColor( 0, 0, 0, 150 );
            mSecondaryFrame->setHitbox( 5, 0, 0, 10 );
        }

        mPrimaryFrame->setHitboxColor( 0, 0, 0, 150 );
        mPrimaryFrame->setHitbox( 10, 10, 0, 10 );

        mShouldSwap = utils::genRandomBool();
    }

    ~RandomObject() {

        delete mPrimaryFrame;
        delete mSecondaryFrame;
    }

    bool
    collide( Object2D* target ) {

        auto hitboxOfTarget = target->getHitboxRect();
        auto hitboxOfPO = mPrimaryFrame->getHitboxRect();

        if ( !mShouldRenderSecondary ) {
            return helpers::collide( hitboxOfTarget, hitboxOfPO );
        }

        auto hitboxOfSO = mSecondaryFrame->getHitboxRect();

        return (
            helpers::collide( hitboxOfTarget, hitboxOfPO ) 
            || helpers::collide( hitboxOfTarget, hitboxOfSO )
        ); 
    }

    void
    renderPrimaryFrame() {

        if ( mPrimaryFrame != nullptr ) {
            mPrimaryFrame->renderImage();
        } 
    }

    void
    renderSecondaryFrame() {

        if ( mSecondaryFrame != nullptr && mShouldRenderSecondary ) {
            mSecondaryFrame->renderImage();
        }
    }

    void    
    render() {

        if ( mIsMovementStarted ) move();

        if ( mShouldSwap ) {

            renderPrimaryFrame();
            renderSecondaryFrame();
        }
        else {

            renderSecondaryFrame();
            renderPrimaryFrame();
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
    
            mPrimaryFrame->move( mMovement.direction, mMovement.step );

            if ( mSecondaryFrame ) {
                mSecondaryFrame->move( mMovement.direction, mMovement.step );
            }
            
            mMovementTicks = currentTicks;
        }
    }

    void
    setMovement( Move move ) { 

        mMovement = move;
    }

    int
    getX() {

        if ( mSecondaryFrame ) {
            return mSecondaryFrame->x;
        }

        return mPrimaryFrame->x;
    }

    int
    getWidth() {

        if ( mSecondaryFrame ) {
            return mSecondaryFrame->width + mGap + mPrimaryFrame->width;
        }

        return mPrimaryFrame->width;
    }

    void
    setPrimaryImages( std::vector<Image*>* aImages ) {

        mPrimaryImages = aImages;
    }

    void
    setSeconaryImages( std::vector<Image*>* aImages ) {

        mSecondaryImages = aImages;
    }

    Frame*
    getPrimaryFrame() { return mPrimaryFrame; }

    Frame*
    getSecondaryFrame() { return mSecondaryFrame; }
};

// std::vector<Image*> RandomObject::mPrimaryImages = {};
// std::vector<Image*> RandomObject::mSecondaryImages = {};


#endif