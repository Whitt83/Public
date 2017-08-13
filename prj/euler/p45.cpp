#include "p45.hpp"

#include <exception>


P45::P45()
: tN_(2)
, pN_(2)
, hN_(2)
{

}
P45::Solution P45::findNextSolution()
{
    Solution results;
    uint32_t iterations = 0;

    adjustSearch(tN_, 0, pN_, 0, hN_, 0);

    while (true)
    {
        uint32_t const fTN = computeTriangle(tN_);
        uint32_t const fPN = computePentagonal(pN_);
        uint32_t const fHN = computeHexagonal(hN_);
        if (fTN >= 2147483648)
        {
        std::cout << "integer overflow soon.  Aborting." << std::endl;
            break;
        }
        iterations++;

        if ((fTN == fPN) && (fPN == fHN))
        {
            results.number_ = fTN;
            results.hN_ = hN_;
            results.pN_ = pN_;
            results.tN_ = tN_;
            results.iterations_ = iterations;
            break;
        }

        adjustSearch(tN_, fTN, pN_, fPN, hN_, fHN);
    }

    return results;
}

void P45::adjustSearch(
    uint32_t & tN, uint32_t const fTN,
    uint32_t & pN, uint32_t const fPN,
    uint32_t & hN, uint32_t const fHN)
{
    /* Which ever number produces the lowest value, increment it */
    if ((fTN <= fPN) && (fTN <= fHN))
    {
        tN++;
    }
    else if ((fPN <= fTN) && (fPN <= fHN))
    {
        pN++;
    }
    else if ((fHN <= fPN) && (fHN <= fTN))
    {
        hN++;
    }
    else
    {
        std::cout << fTN << std::endl;
        std::cout << fPN << std::endl;
        std::cout << fHN << std::endl;
        throw std::runtime_error("Coding error");
    }
}
uint32_t P45::computeTriangle(uint32_t const n)
{
    return (n * (n + 1)) / 2;
}

uint32_t P45::computePentagonal(uint32_t const n)
{
    return (n * (3 * n - 1)) /2;
}

uint32_t P45::computeHexagonal(uint32_t const n)
{
    return n * (2 * n - 1);
}


std::ostream & operator << (std::ostream& os, const P45::Solution & obj)
{
    os << "Solution:" << std::endl;
    os << "Triangle Number:" << obj.tN_ << std::endl;
    os << "Pentagonal Number:" << obj.pN_ << std::endl;
    os << "Hexagonal Number:" << obj.hN_ << std::endl;
    os << "Iterations:" << obj.iterations_ << std::endl;
    os << "Solution:" << obj.number_ << std::endl;
    return os;
}

