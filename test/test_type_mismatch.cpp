#include <iostream>
#include <string>
#include <fstream>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_type_mismatch.dat";
    {
        std::ofstream out(path);
        out << "name = hello\n";
    }

    try
    {
        fm::FileParser parser(path);
        parser.get_item<int>("name");
    }
    catch (const fm::FileParserError &)
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
