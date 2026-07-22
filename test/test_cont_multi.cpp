#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_cont_multi.dat";
    {
        std::ofstream out(path);
        out << "data = 1 2 \\\n";
        out << "      3 4 \\\n";
        out << "      5 6\n";
    }

    fm::FileParser parser(path);

    auto v = parser.get_items<std::vector<int>>("data");

    if (v[0] != 1 || v[1] != 2 || v[2] != 3 ||
        v[3] != 4 || v[4] != 5 || v[5] != 6)
        return 1;

    std::remove(path.c_str());
    return 0;
}
