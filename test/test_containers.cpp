#include <cstdlib>
#include <fstream>
#include <string>
#include <deque>
#include <set>
#include <unordered_set>
#include "FileParser.h"

int main()
{
    // test std::deque (emplace_back path)
    {
        const std::string path = "/tmp/test_containers_deque.dat";
        {
            std::ofstream out(path);
            out << "data = 10 20 30\n";
        }

        fm::FileParser parser(path);
        auto d = parser.get_items<std::deque<int>>("data");
        if (d.size() != 3) return 1;
        if (d[0] != 10 || d[1] != 20 || d[2] != 30) return 2;
        std::remove(path.c_str());
    }

    // test std::set (emplace path, sorted)
    {
        const std::string path = "/tmp/test_containers_set.dat";
        {
            std::ofstream out(path);
            out << "data = 30 10 20\n";
        }

        fm::FileParser parser(path);
        auto s = parser.get_items<std::set<int>>("data");
        if (s.size() != 3) return 3;
        auto it = s.begin();
        if (*it++ != 10) return 4;
        if (*it++ != 20) return 5;
        if (*it++ != 30) return 6;
        std::remove(path.c_str());
    }

    // test std::unordered_set (emplace path, unique)
    {
        const std::string path = "/tmp/test_containers_unordered_set.dat";
        {
            std::ofstream out(path);
            out << "data = 5 15 25\n";
        }

        fm::FileParser parser(path);
        auto u = parser.get_items<std::unordered_set<int>>("data");
        if (u.size() != 3) return 7;
        if (u.count(5) != 1) return 8;
        if (u.count(15) != 1) return 9;
        if (u.count(25) != 1) return 10;
        std::remove(path.c_str());
    }

    return 0;
}
