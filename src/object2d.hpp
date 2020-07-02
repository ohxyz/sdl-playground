#include <string>
#include <vector>
#include <SDL.h>
#include "frame.hpp"

#ifndef OBJECT2D
#define OBJECT2D

class Object2D {

public:
    Object2D();
    Object2D( std::vector<Frame>& );
    Object2D( int, int, int, int );
    Object2D( int, int, int, int, SDL_Color );
    Object2D( int, int, int, int, SDL_Color, SDL_Color );
    Object2D( int, int, int, int, std::string );
    ~Object2D();
    void startAnimation( bool=false );
    void stopAnimation();
    void resumeAnimation();
    void setBackgroundColor( uint8_t, uint8_t, uint8_t, uint8_t );
    void setBorderColor( uint8_t, uint8_t, uint8_t, uint8_t );
    void animate();
    void render();
    void setFrames( std::vector<Frame>& );
    void setFrame( Frame& );

private:
    int mAnimationTicks;
    int mAnimationFrameIndex {0};
    std::vector<Frame> mAnimationFrames;
    bool mIsAnimationEnabled {false};
    bool mCanAnimationRepeat {false};

    Frame mFrame;
    Frame* mCurrentFrame;
};

#endif