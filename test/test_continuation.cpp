#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_continuation_input";
    {
        std::ofstream out(path);
        out << "data = 1.0 2.0 \\\n";
        out << "     3.0 4.0\n";
    }

    fm::FileParser parser(path);

    std::vector<double> v(4);
    parser.get_items(v, "data");

    if (v[0] != 1.0 || v[1] != 2.0 || v[2] != 3.0 || v[3] != 4.0)
        return 1;

    std::remove(path.c_str());
    return 0;
}
