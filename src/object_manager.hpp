#include "object2d.hpp"

#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

class ObjectManager {

public:
    ObjectManager() {}
    ~ObjectManager() {}

    bool
    collide( Object2D* obj1, Object2D* obj2 ) {

        Frame* f1 = obj1->getCurrentFrame();
        Frame* f2 = obj2->getCurrentFrame();

        if ( (f1->x < f2->x) && (f1->x + f1->width  < f2->x) ) {
            printf( "Obj1 on LEFT side of Obj2\n" );
            return false;
        }
        else if ( (f1->y < f2->y) && (f1->y + f1->height < f2->y) ) {
            printf( "Obj1 on UP side of Obj2\n" );
            return false;
        }
        else if (  f1->y > (f2->y + f2->height) ) {
            printf( "Obj1 on DOWN side of Obj2\n" );
            return false;
        }
        else if ( f1->x > (f2->x + f2->width) ) {
            printf( "Obj1 on RIGHT side of Obj2\n" );
            return false;
        }

        return true;
    }
};

#endif