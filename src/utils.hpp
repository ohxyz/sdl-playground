#include <string>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

namespace utils {

    // https://stackoverflow.com/questions/440133
    std::string 
    genRandomString( int len ) {

        std::string result;

        char selection[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        for ( int i = 0; i < len; i++ ) {
            result += selection[ rand() % (sizeof(selection) - 1) ];
        }
        
        return result;
    }

    // https://stackoverflow.com/questions/5008804
    int
    genRandomInt( int min, int max ) {

        return min + ( rand() % (max - min + 1) );
    }

    bool
    genRandomBool( float ratioOfTrue=0.5 ) {

        float f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        return f < ratioOfTrue;
    }
}

#endif