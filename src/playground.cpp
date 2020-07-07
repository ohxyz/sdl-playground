#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include "playground-mod.h"
#include <iostream>

struct TT {

    int i;
    int j;
};

struct T {

    int a;
    int b;
    TT tt;
};

void fn( T t, T t2, T* t3 ) {

    printf( "%d\n", t.a );

    t.a = 100;
    t2.a = 1000;
    t3->a = 10000;
}

int 
main( int argc, char* args[] ) {

    std::vector<int> v1 = { 1, 2, 3 };
    std::vector<char> v2 = { 'a', 'b', 'c' };

    for ( auto &i : v1 ) std::cout << i << std::endl;
    for ( auto &i : v2 ) std::cout << i << std::endl;

    return 0;
}

