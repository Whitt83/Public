#pragma once


template <typename T_>
class Singleton
{

    public:
        __attribute__((always_inline))
        static inline T_ & getInstance()
        {
            static T_ instance;
            return instance;
        }

    private:
        Singleton() = default;
        virtual ~Singleton() = default;

};
