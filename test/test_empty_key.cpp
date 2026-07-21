#include <cstdlib>
#include <fstream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_empty_key.dat";
    {
        std::ofstream out(path);
        out << "= 42\n";
    }

    try
    {
        fm::FileParser parser(path);
        int val{};
        parser.get_item(val, "");
    }
    catch (const fm::FileParserError &)
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
