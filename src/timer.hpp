#include <SDL.h>

#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {

    bool mIsTimeOut {false};
    bool mIsStarted {false};

    int mStartTicks {0};
    int mExpiryTicks {0};

public:

    Timer() {

    }

    Timer( int aTicks ) {

        mExpiryTicks = aTicks;
    }

    ~Timer() {

    }

    void
    start() {

        mStartTicks = SDL_GetTicks();
        mIsStarted = true;
    }

    void
    start( int aExpiryTicks ) {

        mExpiryTicks = aExpiryTicks;
        start();
    }

    void
    stop() {

        mIsStarted = false;
    }

    void
    reset() {

        mStartTicks = SDL_GetTicks();
    }

    void
    reset( int aExpiryTicks ) {

        mExpiryTicks = aExpiryTicks;
        reset();
    }

    bool
    isTimeOut() {

        if ( !mStartTicks ) return false;

        int currentTicks = SDL_GetTicks();

        return currentTicks - mExpiryTicks >= mStartTicks;
    }

    void
    setExpiryTicks( int aTicks ) {

        mExpiryTicks = aTicks;
    }

    bool
    isStarted() { return mIsStarted; }
};

#endif