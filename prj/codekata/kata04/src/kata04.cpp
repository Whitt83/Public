#include "kata04.hpp"

#include "csv_reader.hpp"
/* <string> included in header */
/* <vector> included in header */
#include <stdexcept>
#include <limits>
#include <iostream>

namespace Kata04
{
    //TODO put in env variable that points to root of source tree
    static std::string const KATA04_1_FILE = "/home/wbatcheler/github/github-public/prj/codekata/kata04/data/weather.dat";
    static std::string const KATA04_2_FILE = "/home/wbatcheler/github/github-public/prj/codekata/kata04/data/football.dat";



    void kata04_1(unsigned int & smallestSpreadDay)
    {
        CSVOutput_t csvOutput;
        if (false == loadCSVFile(KATA04_1_FILE, csvOutput, true, ' '))
        {
            /* cannot do what the user asked.  Throw something so we fail loudly */
            throw std::runtime_error("Unable to load or process input file");
        }

        //TODO Why didn't numeric limits work here?
        signed int smallestSpreadFound = 300;
        /* iterate over each row in the CSV Output*/
        for (CSVOutput_t::const_iterator it = csvOutput.begin(); it != csvOutput.end(); ++it)
        {
            /* If the record contains less than 3 fields, there's nothing we can do about it */
            if (it->size() < 3)
            {
                /* Insufficient number of fields in this record */
                continue;
            }
            try
            {
                signed int const dayNumber = std::stoi(it->at(0), nullptr);
                signed int const dailyHighTemperature = std::stoi(it->at(1),nullptr);
                signed int const dailyLowTemperature = std::stoi(it->at(2),nullptr);
                if ((dailyHighTemperature - dailyLowTemperature) < smallestSpreadFound)
                {
                    smallestSpreadFound = dailyHighTemperature - dailyLowTemperature;
                    smallestSpreadDay = dayNumber;
                }
            }
            catch(std::invalid_argument e)
            {
                /* Could not convert from string to integer... */
                std::cerr  << "Could not convert from string to integer:" << it->at(0) << "|" << it->at(1) << "|" << it->at(2) << std::endl;
                continue;
            }
        }
    }

    void kata04_2(std::string & teamWithSmallestGoalDifference)
    {
        CSVOutput_t csvOutput;
        /* Don't skip first row.  We need the headers. Told to parse looking for F & A */
        if (false == loadCSVFile(KATA04_2_FILE, csvOutput, false, ' '))
        {
            /* cannot do what the user asked.  Throw something so we fail loudly */
            throw std::runtime_error("Unable to load or process input file");
        }
        if (csvOutput.size() < 1)
        {
            /* Somehow we think we parsed the file, but returned no records... */
            throw std::runtime_error("Unable to load or process input file");
        }

        /* This kata expects us to find the fields labeled 'F' and 'A', so find them */
        /* This kata has an illegal CSV... have to work around it. */

        ssize_t FFieldIndex = -1;
        ssize_t AFieldIndex = -1;
        for (size_t i = 0; i < csvOutput.at(0).size(); i++)
        {
            if (csvOutput.at(0).at(i).compare("F") == 0)
            {
                if (FFieldIndex != -1)
                {
                    /* We thought we already had it? */
                    throw std::logic_error("Found multiple fields with 'F' column header!");
                }
                /* Because this CSV has a #. text field that doesn't have a column header... */
                FFieldIndex = i + 1;
            }
            if (csvOutput.at(0).at(i).compare("A") == 0)
            {
                if (AFieldIndex != -1)
                {
                    /* We thought we already had it? */
                    throw std::logic_error("Found multiple fields with 'A' column header!");
                }
                /* Because this CSV has a #. and '-' text field that don't have a column header... */
                AFieldIndex = i + 2;
            }
        }

        if ((FFieldIndex == -1) || (AFieldIndex == -1))
        {
            throw std::logic_error("Could not identify fields for 'For' or 'Against'");
        }

        /* We know what fields we're looking for, so start parsing the file vectors */
        size_t const minimumRequiredFieldCount = std::max(AFieldIndex, FFieldIndex);

        //TODO Why didn't numeric limits work here?
        signed int smallestSpreadFound = 300;

        CSVOutput_t::const_iterator it = csvOutput.begin();
        it++; /* Skip the first row since we know it's field headers */
        for (; it != csvOutput.end(); ++it)
        {
            if (it->size() < minimumRequiredFieldCount)
            {
                /* Insufficient number of fields in this record */
                std::cerr << "Too few fields in CSV record" << std::endl;
                continue;
            }
            try
            {
                std::string const teamName = it->at(1);
                unsigned int const FGoalCount = std::stoi(it->at(FFieldIndex),nullptr);
                unsigned int const AGoalCount = std::stoi(it->at(AFieldIndex),nullptr);
                if ((FGoalCount - AGoalCount) < smallestSpreadFound)
                {
                    smallestSpreadFound = FGoalCount - AGoalCount;
                    teamWithSmallestGoalDifference = teamName;
                }
            }
            catch(std::invalid_argument e)
            {
                /* Could not convert from string to integer... */
                std::cerr << "Could not convert from string to integer:" << it->at(1) << "|" << it->at(FFieldIndex) << "|" << it->at(AFieldIndex) << std::endl;
                continue;
            }
        }






    }

    void kata04_3()
    {
        /* The kata tells you to take into account common code between Kata04-1 & Kata04-2... I think I have done this already
         * To accomodate both katas I had to add an optional parameter to ignore the first line in the CSV.  The first Kata required it, the second didn't.
         * I don't think the readability of the programs suffered -- the CSV reader is fairly basic and just spits out a vector of vector of strings.  It's up
         *   to the calling function to decide what to do with those vectors, that's where it gets a little messy
         *
         *
         *
         */
    }




}
