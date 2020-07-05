#include <stdlib.h>
#include "utils.h"

std::string 
generateRandomString( int len ) {

    std::string str;

    char selection[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for ( int i = 0; i < len; i++ ) {
        str += selection[ rand() % (sizeof(selection) - 1) ];
    }
    
    return str;
}