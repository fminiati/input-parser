//
// Copyright (C) 2020 Francesco Miniati <francesco.miniati@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <list>
#include "FileParser.h"

int main(int argc, char *argv[])
{

    using namespace fm;
    const std::string prog(argv[0]);

    // fila name string
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

    int vsize{};
    parser.get_item(vsize, "vsize");
    std::vector<double> v(vsize);
    parser.get_items(v, "vector");

    int lsize{};
    parser.get_item(lsize, "lsize");
    std::list<float> l(lsize);
    parser.get_items(l, "list");

    constexpr int asize = 5;
    std::array<int, asize> a;
    parser.get_items(a, "array");

    float x{};
    parser.get_item(x, "flt_x");

    std::cout << "\nvector: ";
    for (auto i : v)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << "\nlist: ";
    for (auto i : l)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << "\narray: ";
    for (auto i : a)
        std::cout << i << " ";
    std::cout << '\n';
    std::cout << "\nx=" << x << '\n';

    std::cout << "\n parser mapped data is:\n\n";
    parser.flush();
}
