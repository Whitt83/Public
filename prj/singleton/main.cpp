#include <iostream>

#include "singleton.hpp"
#include "OtherClass.hpp"
#include "OtherCompilationUnit.hpp"
#include "library_function.hpp"

void someOtherFunction();

int main(int argc, char ** argv)
{

    /* This will work */
    OtherClass & c1 = Singleton<OtherClass>::getInstance();
    c1.hello("main");
    OtherClass & c2 = Singleton<OtherClass>::getInstance();
    c2.hello("main");

    someOtherFunction();

    someFunctionInAnotherCU();

    someLibraryFunction();
    return 0;
}

void someOtherFunction()
{
    OtherClass & c3 = Singleton<OtherClass>::getInstance();
    c3.hello("someOtherFunction");
}
