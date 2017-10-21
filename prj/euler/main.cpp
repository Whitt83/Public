#include "p45.hpp"

#include <chrono>
#include <iostream>

int main(int argc, char ** argv)
{

    P45 p45;

    /* First one we know to be 40755 */
    P45::Solution const solution = p45.findNextSolution();


    /* Second one is unknown */
    {
        auto const startTime = std::chrono::high_resolution_clock::now();
        P45::Solution const solution = p45.findNextSolution();
        auto const endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> runTime = endTime - startTime;
        std::cout << solution;
        std::cout << "Found #2 solution in " << solution.iterations_ << " iterations." << std::endl;
        std::cout << "Elapsed Time: (s)" << runTime.count() << std::endl;
    }

    return 0;
}
