#include <cstdlib>
#include <fstream>
#include <string>
#include <array>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_array.dat";
    {
        std::ofstream out(path);
        out << "data = 5 6 7 8 9\n";
    }

    fm::FileParser parser(path);

    auto a = parser.get_array<int, 5>("data");

    if (a[0] != 5) return 1;
    if (a[1] != 6) return 2;
    if (a[2] != 7) return 3;
    if (a[3] != 8) return 4;
    if (a[4] != 9) return 5;

    std::remove(path.c_str());
    return 0;
}
