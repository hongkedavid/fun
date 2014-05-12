/*
 *  A very simple C++ program to test endianess of your machine
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) 
{
    unsigned int endianness = 0xdeadbeef;
    
    if (((unsigned char)(*(const char *)&endianness)) == 0xef)
        cout << "Little Endian" << endl;
    else if (((unsigned char)(*(const char *)&endianness)) == 0xde)
        cout << "Big Endian" << endl;

    return 0;
}
