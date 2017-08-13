#include <cstdint>

#pragma once
#include <iostream>

class P45
{
    public:
        typedef struct
        {
            uint32_t tN_;
            uint32_t pN_;
            uint32_t hN_;
            uint32_t iterations_;
            uint32_t number_;
        } Solution;

        P45();
        ~P45() = default;

        Solution findNextSolution();
    private:
        uint32_t tN_;
        uint32_t pN_;
        uint32_t hN_;
        inline uint32_t computeTriangle(uint32_t const n);
        inline uint32_t computePentagonal(uint32_t const n);
        inline uint32_t computeHexagonal(uint32_t const n);

        void adjustSearch(
            uint32_t & tN, uint32_t const fTN,
            uint32_t & pN, uint32_t const fPN,
            uint32_t & hN, uint32_t const fHN);
};


std::ostream & operator << (std::ostream& os, const P45::Solution & obj);
