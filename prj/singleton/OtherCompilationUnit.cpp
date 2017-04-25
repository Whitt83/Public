#include "singleton.hpp"
#include "OtherClass.hpp"

void someFunctionInAnotherCU()
{
    OtherClass & c4 = Singleton<OtherClass>::getInstance();
    c4.hello("someFunctionInAnotherCU");
}
