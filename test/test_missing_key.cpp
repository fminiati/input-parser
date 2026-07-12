#include <iostream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_missing_key_input";
    {
        std::ofstream out(path);
        out << "exists = 42\n";
    }

    try
    {
        fm::FileParser parser(path);
        int val{};
        parser.get_item(val, "does_not_exist");
    }
    catch (const fm::FileParserError &)
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
