#include <iostream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_missing_key.dat";
    {
        std::ofstream out(path);
        out << "exists = 42\n";
    }

    try
    {
        fm::FileParser parser(path);
        parser.get_item<int>("does_not_exist");
    }
    catch (const fm::FileParserError &)
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
