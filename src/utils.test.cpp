#include "utils.hpp"
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

void 
test_genRandomString() {

    for ( int i = 0; i < 5; i++ ) {

        std::string s = utils::genRandomString( 10 );
        std::cout << s << std::endl;
    }
}

void
test_genRandomInt() {

    int a0 = 0;
    int a1 = 0;
    int a2 = 0;
    int a3 = 0;
    int a4 = 0;

    for ( int i = 0; i < 1000; i++ ) {

        int in = utils::genRandomInt( 0, 4 );

        if ( in == 0 ) a0++;
        if ( in == 1 ) a1++;
        if ( in == 2 ) a2++;
        if ( in == 3 ) a3++;
        if ( in == 4 ) a4++;
    }

    std::cout << a0 << std::endl;
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;
    std::cout << a4 << std::endl;
}

void
test_genRandomBool() {

    int numOfTrue = 0;
    int numOfFalse = 0;

    for ( int i = 0; i < 10000; i++ ) {

        int result = utils::genRandomBool( 0.5 );

        if ( result == true ) numOfTrue++;
        if ( result == false ) numOfFalse++;
    }

    std::cout << "Num of true:  " << numOfTrue << std::endl;
    std::cout << "Num of false: " << numOfFalse << std::endl;
}

int
main() {

    srand( time(NULL) );

    // std::cout << rand() << ":" << RAND_MAX << std::endl;

    // test_genRandomString();
    // test_genRandomInt();

    test_genRandomBool();

    return 0;
}
