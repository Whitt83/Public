#include "OtherClass.hpp"

#include <iostream>

OtherClass::OtherClass()
: somePrivatePointer_ (new int)
{
    std::cout << "Created:" << this << std::endl;
}


OtherClass::~OtherClass()
{
    std::cout << "Destroyed:" << this << std::endl;
}

void OtherClass::hello(std::string const & message)
{
    std::cout << "Hello from " << message << " in " << this << std::endl;
}

