#include <iostream>
#include <string>
#include "FileParser.h"

int main()
{
    try
    {
        fm::FileParser parser("test/nonexistent_file.txt");
    }
    catch (const fm::FileParserError &)
    {
        return 0;
    }

    return 1;
}
