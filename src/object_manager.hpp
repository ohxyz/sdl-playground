#include "object2d.hpp"
#include "helpers.hpp"
#include <vector>
#include <SDL.h>
#include "structs.hpp"
#include <functional>

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

template <class ObjectType>
class ObjectManager {

    std::vector<ObjectType*> mObjectQueue;

    int mObjectPosX {0};
    int mObjectPosY {0};
    Move mMovement;

    int mSpawnInterval;
    int mTicksLastTime;
    bool mShouldMove {true};

public:

    ObjectManager() {

    }

    ObjectManager( int aPosX, int aPosY ) {

        mObjectPosX = aPosX;
        mObjectPosY = aPosY;
    }

    ObjectManager( int aPosX, int aPosY, Move aMovement, int aSpawnInterval=1000 )
    : ObjectManager( aPosX, aPosY ) {

        mMovement = aMovement;
        mSpawnInterval = aSpawnInterval;
    }

    ~ObjectManager() {

        mObjectQueue.clear();
    }

    void
    clear() {

        mObjectQueue.clear();
    }

    void
    startMove() { 

        mTicksLastTime = SDL_GetTicks();
        mShouldMove = true; 
    }

    void
    stopMove() {

        mShouldMove = false;
        for ( auto& obj : mObjectQueue ) { obj->stopMove(); }
    }

    void
    move() {

        if ( !mShouldMove ) return;

        int ticksNow = SDL_GetTicks();

        if ( ticksNow - mSpawnInterval > mTicksLastTime ) {

            auto obj = new ObjectType( mObjectPosX, mObjectPosY );

            obj->setMovement( mMovement );
            obj->startMove();
            mObjectQueue.push_back( obj );

            auto firstObj = mObjectQueue[0];

            if ( firstObj->getX() + firstObj->getWidth() < 0 ) {

                mObjectQueue.erase( mObjectQueue.begin() );
                delete firstObj;
            }

            mTicksLastTime = ticksNow;
        }

        // for ( auto& obj : mObjectQueue ) {

        //     if ( obj->collide( target ) ) onCollide();
        // }
    }

    void
    render() {

        for ( auto& obj: mObjectQueue ) obj->render();
    }

    std::vector<ObjectType*>*
    getObjects() { return &mObjectQueue; }
    
    void
    setMovement( Move aMove ) { mMovement = aMove; }

    void
    setSpawnInterval( int aMilliseconds ) { mSpawnInterval = aMilliseconds; }
    
};

#endif