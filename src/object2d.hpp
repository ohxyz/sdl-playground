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
    Object2D( int, int, int, int, std::string );
    ~Object2D();
    void startAnimation();
    void startAnimation( int, bool=false );
    void stopAnimation();
    void resumeAnimation();
    void animate(); 
    void render();
    void setFrames( std::vector<Frame>& );

private:
    int mAnimationTicks;
    int mAnimationInterval {100};
    int mAnimationFrameIndex {0};
    std::vector<Frame> mAnimationFrames;
    bool mIsAnimationEnabled {false};
    bool mCanAnimationRepeat {false};

    Frame mFrame;
    Frame* mCurrentFrame;
};

#endif