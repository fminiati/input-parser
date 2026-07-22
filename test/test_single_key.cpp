#include <cstdlib>
#include <fstream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "/tmp/test_single_key.dat";
    {
        std::ofstream out(path);
        out << "answer = 42\n";
    }

    fm::FileParser parser(path);

    auto val = parser.get_item<int>("answer");

    if (val != 42)
        return 1;

    std::remove(path.c_str());
    return 0;
}
