#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include "playground-mod.h"
#include <iostream>
#include <functional>
#include <iostream>


struct ClsStruct {

    int a {11};
    int b {22};
    int c {33};

};

class Cls {

    ClsStruct mStruct; 

public:

    Cls( ClsStruct s ) {

        mStruct = s;
    }

    int
    addAll() {

       return mStruct.a + mStruct.b + mStruct.c;
    }

};

int 
main( int argc, char* args[] ) {

    Cls* c = new Cls(  { .a=1, .b=2 } );

    std::cout << c->addAll() << std::endl;

    return 0;
}

