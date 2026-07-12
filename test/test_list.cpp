#include <cstdlib>
#include <fstream>
#include <string>
#include <list>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_list_input";
    {
        std::ofstream out(path);
        out << "lsize = 4\n";
        out << "data = 10 20 30 40\n";
    }

    fm::FileParser parser(path);

    int sz{};
    parser.get_item(sz, "lsize");

    std::list<int> l(sz);
    parser.get_items(l, "data");

    auto it = l.begin();
    if (*it++ != 10) return 1;
    if (*it++ != 20) return 2;
    if (*it++ != 30) return 3;
    if (*it++ != 40) return 4;

    std::remove(path.c_str());
    return 0;
}
