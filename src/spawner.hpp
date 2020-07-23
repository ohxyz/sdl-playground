#include "object2d.hpp"
#include "helpers.hpp"
#include <vector>
#include <SDL.h>
#include <functional>
#include "structs.hpp"
#include "utils.hpp"
#include <math.h>
#include "timer.hpp"

#ifndef SPAWNER_HPP
#define SPAWNER_HPP

template <class ObjectType>
class Spawner {

    std::vector<ObjectType*> mObjectQueue;

    int mSpawnPosX {0};
    int mSpawnPosY {0};
    Move mObjectMovement;

    bool mShouldMove {true};

    bool mIsRange {false};
    Range mRangeOfX;
    Range mRangeOfY;


    int mSpawnInterval;
    // Use amplifier e.g. 100ms, 200ms, 500ms, 1000ms. 
    // So the spawn interval is 100ms * 1, 200ms * 3, etc...
    Range mRangeOfSpawnInterval;

    Timer* mTimer;

public:

    Spawner( int aX, int aY, int aInterval=1 )
    : mSpawnPosX( aX ), mSpawnPosY( aY ), mSpawnInterval( aInterval ) {

        mTimer = new Timer();
    }

    Spawner( Range aRangeX, Range aRangeY, Range aRangeInterval={1, 1, 1000} )
    : mIsRange( true ), 
      mRangeOfX( aRangeX ), 
      mRangeOfY( aRangeY ), 
      mRangeOfSpawnInterval( aRangeInterval ) {

        mTimer = new Timer();
    }

    ~Spawner() {

        mObjectQueue.clear();
    }

    void
    clear() {

        mObjectQueue.clear();
    }

    void
    start() { 

        mTimer->start( getSpawnIntervalMS() );
        mShouldMove = true;
    }

    void
    stop() {

        mShouldMove = false;
        for ( auto& obj : mObjectQueue ) { obj->stopMove(); }
    }

    int
    getSpawnIntervalMS() {

        if ( !mIsRange ) {

            return mSpawnInterval;
        }

        int base = utils::genRandomInt( mRangeOfSpawnInterval.start, mRangeOfSpawnInterval.end );

        return round( static_cast<float>(base) * mRangeOfSpawnInterval.amplifier );
    }

    void
    spawn() {

        if ( !mShouldMove ) return;

        if ( mTimer->isTimeOut() ) {

            int posX = mSpawnPosX;
            int posY = mSpawnPosY;

            if ( mIsRange ) {

                posX = round(
                    static_cast<float>( utils::genRandomInt( mRangeOfX.start, mRangeOfX.end ) ) 
                    * mRangeOfX.amplifier
                );
                posY = round(
                    static_cast<float>( utils::genRandomInt( mRangeOfY.start, mRangeOfY.end ) )
                    * mRangeOfY.amplifier
                );
            }

            ObjectType* obj = new ObjectType( posX, posY );

            // SDL_Log( "@@ %d %d", posX, posY );

            obj->setMovement( mObjectMovement );
            obj->startMove();
            mObjectQueue.push_back( obj );

            auto firstObj = mObjectQueue[0];

            if ( firstObj->getX() + firstObj->getWidth() < 0 ) {

                mObjectQueue.erase( mObjectQueue.begin() );
                delete firstObj;
            }

            mTimer->reset( getSpawnIntervalMS() );
        }
    }

    void
    renderObjects() {

        for ( auto& obj: mObjectQueue ) obj->render();
    }

    std::vector<ObjectType*>
    getObjects() { return mObjectQueue; }
    
    void
    setObjectMovement( Move aMove ) { mObjectMovement = aMove; }

    void
    setSpawnInterval( int aMilliseconds ) { mSpawnInterval = aMilliseconds; }
    
};

#endif