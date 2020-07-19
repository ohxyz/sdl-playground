#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include "playground-mod.h"
#include <iostream>
#include <functional>
#include <iostream>

void
outside() {

    std::cout << "outside!" << std::endl;
}

void
call( std::function<void()> callback ) {

    callback();
}

class Cls {

    int mInt = 1;

public:

    void
    inside() {

        std::cout << mInt << std::endl;
    }

    void
    callInside() {

        call( inside );
    }
};

int 
main( int argc, char* args[] ) {

    call( outside );
    auto cls = new Cls;
    
    cls->callInside();

    return 0;
}

