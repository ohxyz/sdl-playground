#include <stdio.h>
#include "playground-mod.h"
#include <vector>
#include <math.h>

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

    std::vector<T> ts;
    std::vector<T> ts2;

    printf( "@@ %d\n", ts.size() );

    T t1 = { .a=1, .b=2 };
    T t2 = { .a=3, .b=4 };

    ts.push_back( t1 );
    ts.push_back( t2 );

    ts2 = {

        { 5 },
        { 6 }
    };

    printf( "@@ %d\n", ts2[1].a );

    T arg = { .a=99 };
    T arg2 = { .a=999 };
    T arg3 = { .a=9999 };
    T* pArg3 = &arg3;

    fn( { .a=99 }, arg2, pArg3 );

    printf( "@@@ %d, %d, %d\n", arg.a, arg2.a, arg3.a );

    int a = pow(10, 2);
    int x = 13;

    int y = - pow( x-5, 2 ) + 1;

    double z = pow( 2, 2.5 );

    int rz = round(z);

    printf( "@@@@ %f, %d\n", z, rz);

    return 0;
}

