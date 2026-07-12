#include <iostream>
#include <string>
#include <fstream>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_type_mismatch_input";
    {
        std::ofstream out(path);
        out << "name = hello\n";
    }

    try
    {
        fm::FileParser parser(path);
        int val{};
        parser.get_item(val, "name");
    }
    catch (const std::ios_base::failure &)
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
