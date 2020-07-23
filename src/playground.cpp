#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include "playground-mod.h"
#include <iostream>
#include <functional>
#include <iostream>


int 
main( int argc, char* args[] ) {

    std::vector<int> ints = { 2, 4, 6, 8 };

    // ints.erase( ints.begin() + 1 );

    for ( int i = 0; i < ints.size(); i++ ) {

        if ( ints[i] == 6 || ints[i] == 2 ) {

            ints.erase( ints.begin()+i );
        }
    }

    for ( int i = 0; i < ints.size(); i++ ) {

        std::cout << ints[i] << std::endl;
    }
}

