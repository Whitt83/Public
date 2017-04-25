#pragma once

#include <memory>
#include <string>

class OtherClass
{
    public:
        OtherClass();
        ~OtherClass();
        void hello(std::string const & message);
    private:
        std::unique_ptr<int> somePrivatePointer_;
};

