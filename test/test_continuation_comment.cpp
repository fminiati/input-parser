#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_continuation_comment.dat";
    {
        std::ofstream out(path);
        out << "data = 10 20 \\\n";
        out << "     30 40\n";
    }

    fm::FileParser parser(path);

    auto v = parser.get_items<std::vector<int>>("data");

    if (v[0] != 10 || v[1] != 20 || v[2] != 30 || v[3] != 40)
        return 1;

    std::remove(path.c_str());
    return 0;
}
