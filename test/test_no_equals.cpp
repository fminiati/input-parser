#include <cstdlib>
#include <fstream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_no_equals.dat";
    {
        std::ofstream out(path);
        out << "valid = 42\n";
        out << "no_equals_here\n";
    }

    try
    {
        fm::FileParser parser(path);
    }
    catch (const fm::FileParserError &)
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
