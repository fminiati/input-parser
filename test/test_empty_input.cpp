#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include "FileParser.h"

int main()
{
    const std::string path = "test/empty_input_data";
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

    std::remove(path.c_str());

    if (buf.str().empty())
        return 0;

    std::cerr << "unexpected output: [" << buf.str() << "]" << std::endl;
    return 1;
}
