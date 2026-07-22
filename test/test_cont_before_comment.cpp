#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_cont_before_comment.dat";
    {
        std::ofstream out(path);
        out << "data = 12.0 2 3 \\  # continue below\n";
        out << "      7.0 0.0\n";
    }

    fm::FileParser parser(path);

    auto v = parser.get_items<std::vector<double>>("data");

    if (v[0] != 12.0 || v[1] != 2.0 || v[2] != 3.0 || v[3] != 7.0 || v[4] != 0.0)
        return 1;

    std::remove(path.c_str());
    return 0;
}
