#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_cont_value_on_next_input";
    {
        std::ofstream out(path);
        out << "data = \\\n";
        out << "      3.0\n";
    }

    fm::FileParser parser(path);

    std::vector<double> v(1);
    parser.get_items(v, "data");

    if (v[0] != 3.0)
        return 1;

    std::remove(path.c_str());
    return 0;
}
