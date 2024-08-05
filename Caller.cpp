//Caller.cpp
#include <iostream>
#include "include/ToMarkLibrary.hpp"

#define br() std::cout << std::endl

int main(int, char **)
{
    std::cout << "ToMarkLib version: " << tomarklib::getVersion() << std::endl;

    // this is a test
    tomarklib::emojitools.visualTest();
    
    return 0;
}
