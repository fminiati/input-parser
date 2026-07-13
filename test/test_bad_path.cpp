#include <iostream>
#include <string>
#include "FileParser.h"

int main()
{
    try
    {
        fm::FileParser parser("/tmp/nonexistent.txt");
    }
    catch (const fm::FileParserError &)
    {
        return 0;
    }

    return 1;
}
