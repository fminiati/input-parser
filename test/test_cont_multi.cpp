#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_cont_multi_input";
    {
        std::ofstream out(path);
        out << "data = 1 2 \\\n";
        out << "      3 4 \\\n";
        out << "      5 6\n";
    }

    fm::FileParser parser(path);

    std::vector<int> v(6);
    parser.get_items(v, "data");

    if (v[0] != 1 || v[1] != 2 || v[2] != 3 ||
        v[3] != 4 || v[4] != 5 || v[5] != 6)
        return 1;

    std::remove(path.c_str());
    return 0;
}
