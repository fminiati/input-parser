#include <cstdlib>
#include <fstream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_whitespace.dat";
    {
        std::ofstream out(path);
        out << "  key1  =  value1  \n";
        out << " key2 = value2\n";
        out << "key3=value3\n";
    }

    fm::FileParser parser(path);

    auto v1 = parser.get_item<std::string>("key1");
    auto v2 = parser.get_item<std::string>("key2");
    auto v3 = parser.get_item<std::string>("key3");

    if (v1 != "value1" || v2 != "value2" || v3 != "value3")
        return 1;

    std::remove(path.c_str());
    return 0;
}
