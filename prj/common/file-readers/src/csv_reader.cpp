#include "csv_reader.hpp"

#include <istream>
#include <fstream>
/* <string> included in header */
/* <vector> included in header */

static unsigned int const MAX_BUFFER_SIZE = 1024;


/* We do expect this to be a 'friendly' file.  No trickery */
//TODO Does not handle white space in quotes, multiple types of delimiters
//TODO this doesn't care about jagged CSVs, which I think are technically malformed
//TODO doesn't handle CSVs with rows longer than 1024 characters

bool loadCSVFile(std::string const & inputFile, CSVOutput_t & output, bool const ignoreFirstLine, char const delimiter)
{
    std::ifstream inputStream(inputFile.c_str(), std::ifstream::in);
    if (!inputStream.good())
    {
        return false;
    }
    /* File is valid and open.  Start reading in & parsing lines */
    char buffer[1024];
    output.clear();
    unsigned int linesRead = 0;
    while (inputStream.good())
    {
        inputStream.getline(buffer, MAX_BUFFER_SIZE);
        linesRead++;
        if ((ignoreFirstLine == true) && (linesRead == 1))
        {
            continue;
        }
        std::vector<std::string> csvRecord;
        std::string const strBuffer = std::string(buffer);
        std::string::size_type previousPosition = 0;
        std::string::size_type currentPosition = 0;
        /* Search the string for the delimiter */
        /* Usage of currentPosition twice is intended -- search starting at the end of the previous field */
        while ((currentPosition = strBuffer.find(delimiter, currentPosition)) != std::string::npos)
        {
            /* slice from previous delimiter to current delimiter -- this becomes a CSV field */
            if (currentPosition == previousPosition)
            {
                /* We found a delimiter.  Ignore it and move on */
                currentPosition++;
                previousPosition = currentPosition;
                continue;
            }
            std::string const temporaryString = strBuffer.substr(previousPosition, currentPosition - previousPosition);
            previousPosition = currentPosition;
            csvRecord.push_back(temporaryString);
        }
        /* split from the final delimiter to the end of the line */
        csvRecord.push_back(strBuffer.substr(previousPosition));
        /* Finished parsing the line, push the entire row into output */
        output.push_back(csvRecord);
    }
    return true;
}



