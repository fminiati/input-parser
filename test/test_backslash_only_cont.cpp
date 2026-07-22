#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_backslash_only_cont.dat";
    {
        std::ofstream out(path);
        out << "data = 10 \\\n";
        out << "\\  # continuation with backslash-only line\n";
        out << "20\n";
    }

    fm::FileParser parser(path);

    auto v = parser.get_items<std::vector<int>>("data");

    if (v[0] != 10 || v[1] != 20)
    {
        std::remove(path.c_str());
        return 1;
    }

    std::remove(path.c_str());
    return 0;
}
