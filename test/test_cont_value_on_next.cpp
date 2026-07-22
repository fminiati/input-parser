#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_cont_value_on_next.dat";
    {
        std::ofstream out(path);
        out << "data = \\\n";
        out << "      3.0\n";
    }

    fm::FileParser parser(path);

    auto v = parser.get_items<std::vector<double>>("data");

    if (v[0] != 3.0)
        return 1;

    std::remove(path.c_str());
    return 0;
}
