#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_cont_comment_only.dat";
    {
        std::ofstream out(path);
        out << "data = 1 2 \\\n";
        out << "  \\  # comment on continuation\n";
        out << "3 4\n";
    }

    fm::FileParser parser(path);

    std::vector<int> v(4);
    parser.get_items(v, "data");

    if (v[0] != 1 || v[1] != 2 || v[2] != 3 || v[3] != 4)
    {
        std::remove(path.c_str());
        return 1;
    }

    std::remove(path.c_str());
    return 0;
}
