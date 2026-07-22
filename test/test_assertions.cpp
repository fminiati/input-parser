#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_assertions.dat";
    {
        std::ofstream out(path);
        out << "vsize = 3\n";
        out << "vector = 1.0 2.0 3.0\n";
        out << "flt_x = 7.5\n";
    }

    fm::FileParser parser(path);

    auto vsize = parser.get_item<int>("vsize");
    if (vsize != 3)
        return 1;

    auto v = parser.get_items<std::vector<double>>("vector");
    if (v[0] != 1.0 || v[1] != 2.0 || v[2] != 3.0)
        return 2;

    auto x = parser.get_item<float>("flt_x");
    if (x != 7.5f)
        return 3;

    std::remove(path.c_str());
    return 0;
}
