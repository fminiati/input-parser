#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_continuation.dat";
    {
        std::ofstream out(path);
        out << "data = 1.0 2.0 \\\n";
        out << "     3.0 4.0\n";
    }

    fm::FileParser parser(path);

    auto v = parser.get_items<std::vector<double>>("data");

    if (v[0] != 1.0 || v[1] != 2.0 || v[2] != 3.0 || v[3] != 4.0)
        return 1;

    std::remove(path.c_str());
    return 0;
}
