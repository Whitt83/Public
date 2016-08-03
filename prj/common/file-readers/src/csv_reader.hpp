#include <vector>
#include <string>

//TODO come up with a reasonable namespace

typedef std::vector<std::vector<std::string> > CSVOutput_t;

bool loadCSVFile(std::string const & inputFile, CSVOutput_t & output, bool const ignoreFirstLine = true, char const delimiter = '\t');
