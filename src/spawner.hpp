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

    bool mIsStarted {true};

    Range mRangeOfX;
    Range mRangeOfY;

    int mSpawnInterval;
    // Use amplifier e.g. 100ms, 200ms, 500ms, 1000ms. 
    // So the spawn interval is 100ms * 1, 200ms * 3, etc...
    Range mRangeOfSpawnInterval;

    Timer* mAutoSpawnTimer;

public:

    Spawner( Range aRangeX, Range aRangeY, Range aRangeInterval={1, 1, 1000} )
    : mRangeOfX( aRangeX ), 
      mRangeOfY( aRangeY ), 
      mRangeOfSpawnInterval( aRangeInterval ) {

        mAutoSpawnTimer = new Timer();
    }

    Spawner( int aX, int aY, int aInterval=1 ) {

        mRangeOfX = { aX, aX, 1 };
        mRangeOfY = { aY, aY, 1 };
        mRangeOfSpawnInterval = { aInterval, aInterval, 1 };

        mAutoSpawnTimer = new Timer();
    }

    ~Spawner() {

        mObjectQueue.clear();
        delete mAutoSpawnTimer;
    }

    void
    clear() {

        mObjectQueue.clear();
    }

    void
    startAutoSpawn() { 

        mAutoSpawnTimer->start( genSpawnInterval() );
        mIsStarted = true;
    }

    void
    stopAutoSpawn() {

        for ( auto& obj : mObjectQueue ) { obj->stopMove(); }
        mIsStarted = false;
    }

    int
    genSpawnInterval() {

        int base = utils::genRandomInt( mRangeOfSpawnInterval.start, mRangeOfSpawnInterval.end );

        return round( static_cast<float>(base) * mRangeOfSpawnInterval.amplifier );
    }

    void
    autoSpawn() {

        if ( !mIsStarted ) return;

        if ( mAutoSpawnTimer->isTimeOut() ) {

            spawn();
            clean();

            mAutoSpawnTimer->reset( genSpawnInterval() );
        }
    }

    void
    spawn() {

        int posX = round(
            static_cast<float>( utils::genRandomInt( mRangeOfX.start, mRangeOfX.end ) ) 
            * mRangeOfX.amplifier
        );
        int posY = round(
            static_cast<float>( utils::genRandomInt( mRangeOfY.start, mRangeOfY.end ) )
            * mRangeOfY.amplifier
        );

        ObjectType* obj = new ObjectType( posX, posY );

        // SDL_Log( "@@ %d %d", posX, posY );

        obj->setMovement( mObjectMovement );
        obj->startMove();
        mObjectQueue.push_back( obj );
    }

    void
    clean() {

        for ( int i = 0; i < mObjectQueue.size(); i ++ ) {

            ObjectType* obj = mObjectQueue[i];

            if ( obj->getX() + obj->getWidth() < 0 ) {

                mObjectQueue.erase( mObjectQueue.begin() + i );
                delete obj;
            }
        }
    }

    void
    renderObjects() {

        for ( auto& obj: mObjectQueue ) obj->render();
    }

    std::vector<ObjectType*>
    getObjects() { 

        return mObjectQueue; 
    }
    
    void
    setObjectMovement( Move aMove ) { 

        mObjectMovement = aMove; 
    }

    void
    setSpawnInterval( int aMilliseconds ) { 

        mRangeOfSpawnInterval = { aMilliseconds, aMilliseconds, 1 }; 
    }
    
    void
    setSpawnInterval( Range aRange ) {

        mRangeOfSpawnInterval = aRange;
    }
};

#endif