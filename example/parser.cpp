#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include "FileParser.h"

int main(int argc, char *argv[])
{

    using namespace fm;
    const std::string prog(argv[0]);

    // file name string
    std::string filename{};
    // read in filename
    for (auto i{1}; i < argc; ++i)
        if (strncmp("-f", argv[i], 2) == 0)
            filename = argv[i + 1];

    if (filename.size() == 0)
    {
        std::cout << "\n No input file was provided.\n Run this prog with: " + prog + " -f filename\n\n";
        return 0;
    }

    FileParser parser(filename);

    auto vsize = parser.get_item<int>("vsize");
    auto v = parser.get_items<std::vector<double>>("vector");

    auto lsize = parser.get_item<int>("lsize");
    auto l = parser.get_items<std::list<float>>("list");

    auto x = parser.get_item<float>("flt_x");

    std::cout << "\nvector: ";
    for (auto i : v)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << "\nlist: ";
    for (auto i : l)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << "\nx=" << x << '\n';

    std::cout << "\n parser mapped data is:\n\n";
    parser.flush();
}
