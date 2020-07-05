#include "object2d.hpp"
#include "helpers.h"

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class ObjectManager {

public:
    ObjectManager() {}
    ~ObjectManager() {}

    bool
    collide( Object2D* obj1, Object2D* obj2 ) {

        SDL_Rect rect1 = obj1->getCurrentRect();
        SDL_Rect rect2 = obj2->getCurrentRect();

        return helpers::collide( rect1, rect2 );
    }
};

#endif