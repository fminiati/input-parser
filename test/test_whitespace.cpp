#include <cstdlib>
#include <fstream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_whitespace_input";
    {
        std::ofstream out(path);
        out << "  key1  =  value1  \n";
        out << " key2 = value2\n";
        out << "key3=value3\n";
    }

    fm::FileParser parser(path);

    std::string v1, v2, v3;
    parser.get_item(v1, "key1");
    parser.get_item(v2, "key2");
    parser.get_item(v3, "key3");

    if (v1 != "value1" || v2 != "value2" || v3 != "value3")
        return 1;

    std::remove(path.c_str());
    return 0;
}
