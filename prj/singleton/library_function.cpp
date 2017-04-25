#include "library_function.hpp"

#include "singleton.hpp"
#include "OtherClass.hpp"

void someLibraryFunction()
{
    OtherClass & c5 = Singleton<OtherClass>::getInstance();
    c5.hello("someLibraryFunction");
}
