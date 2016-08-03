#include "kata04.hpp"
#include <iostream>
#include <string>

//TODO get gtest linking...

int main(int argc, char ** argv)
{

    /* Execute Kata04-1 */
    unsigned int smallestTemperatureSpreadDay = 0;
    Kata04::kata04_1(smallestTemperatureSpreadDay);
    std::cout  << "Day with smallest spread: " << smallestTemperatureSpreadDay << std::endl;


    /* Execute Kata04-2 */
    std::string teamWithSmalledGoalDifference;
    Kata04::kata04_2(teamWithSmalledGoalDifference);
    std::cout  << "Team with smallest goal difference: " << teamWithSmalledGoalDifference << std::endl;

    return 0;
}
