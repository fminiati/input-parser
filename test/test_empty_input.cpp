#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "FileParser.h"

int main()
{
    const std::string path = "test/test_empty_input";
    {
        std::ofstream out(path);
        out << "# just a comment\n";
        out << "# another comment\n";
    }

    fm::FileParser parser(path);

    std::ostringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());
    parser.flush();
    std::cout.rdbuf(old);

    if (buf.str().empty())
    {
        std::remove(path.c_str());
        return 0;
    }

    std::remove(path.c_str());
    return 1;
}
