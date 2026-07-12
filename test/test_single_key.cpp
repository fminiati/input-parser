#include <cstdlib>
#include <fstream>
#include <string>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_single_key_input";
    {
        std::ofstream out(path);
        out << "answer = 42\n";
    }

    fm::FileParser parser(path);

    int val{};
    parser.get_item(val, "answer");

    if (val != 42)
        return 1;

    std::remove(path.c_str());
    return 0;
}
