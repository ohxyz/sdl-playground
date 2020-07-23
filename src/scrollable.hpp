#include "object2d.hpp"
#include "structs.hpp"
#include <string>
#include "timer.hpp"

#ifndef SCROLLABLE_HPP
#define SCROLLABLE_HPP

class Scrollable : public Object2D {

    bool mShouldRepeatHorizontal {false};

    Move mMovement;

    int mMovementTicks {0};
    bool mIsMovementStarted {false};

    Timer* mTimer;

public:

    Scrollable( int x, int y, int w, int h, std::string imagePath, SDL_Rect imageClipRect, Move movement )
    : Object2D( x, y, w, h, imagePath, imageClipRect ) {

        mMovement = movement;
        mShouldRepeatHorizontal = true;
        getCurrentFrame()->width = getCurrentFrame()->width * 2;

        mTimer = new Timer( movement.interval );
    }

    Scrollable( int x, int y, int w, int h, std::string imagePath, Move movement )
    : Scrollable( x, y, w, h, imagePath, {0, 0, 0, 0}, movement ) {

    }

    void
    startMove() {
        
        mTimer->start();

        if ( mShouldRepeatHorizontal ) {

            if ( mMovement.direction == Direction::Left ) {
                getCurrentFrame()->x = 0;
            }
            else if ( mMovement.direction == Direction::Right ) {
                getCurrentFrame()->x = -getCurrentFrame()->imageClipWidth;
            }
        }
    }

    void
    stopMove() {

        mTimer->stop();
    }

    void
    move() {

        if ( mMovement.direction == Direction::None || mMovement.step == 0 ) return;

        if ( mTimer->isTimeOut() ) {

            switch ( mMovement.direction ) {

            case Direction::Right:

                if ( mShouldRepeatHorizontal && getCurrentFrame()->x >= -mMovement.step ) {

                    getCurrentFrame()->x = -getCurrentFrame()->imageClipWidth;
                }
                else {

                    getCurrentFrame()->x += mMovement.step;
                }

                break;

            case Direction::Left:

                if ( mShouldRepeatHorizontal 
                        && getCurrentFrame()->x + getCurrentFrame()->imageClipWidth <= mMovement.step ) {

                    getCurrentFrame()->x = 0;
                }
                else {

                    getCurrentFrame()->x -= mMovement.step;
                }

                break;
            }

            mTimer->reset();
        }
    }

    void
    setMovement( Move move ) {

        mMovement = move;
    }

    void
    setRepeatHorizontal( bool flag ) {

        mShouldRepeatHorizontal = flag; 
    }

    void
    render() {

        if ( mTimer->isStarted() ) move();

        getCurrentFrame()->renderImage();
    }
};

#endif