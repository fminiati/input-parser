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
#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace fm
{
    class FileParserError : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    class FileParser
    {
    public:
        // constructor
        FileParser(const std::string& a_file_name)
        {
            // open and parse file
            if (std::ifstream file(a_file_name); file)
            {
                bool append_entry_to_prev_key{false};

                std::string line, key;
                while (getline(file, line))
                {
                    if (!line.empty() && line.back() == '\r')
                        line.pop_back();
                    // valid substr: ignore initial blanks and commented out text
                    const auto beg = line.find_first_not_of(" \t");
                    const auto end = line.find_first_of('#');
                    if (end > beg)
                    {
                        // trim trailing spaces and backslashes (backslash indicates continuation)
                        const auto limit = (end != std::string::npos) ? end : line.size();
                        auto content_end = limit;
                        while (content_end > beg && (line[content_end-1] == ' ' || line[content_end-1] == '\\'))
                            --content_end;
                        const std::string s{line.substr(beg, content_end - beg)};

                        if (append_entry_to_prev_key)
                            m_entries[key].append(" " + s);
                        else if (auto pos = s.find('='); pos != std::string::npos && pos > 0)
                        {
                            key = s.substr(0, s.find_last_not_of(' ', pos - 1) + 1);
                            m_entries[key] = s.substr(pos + 1);
                        }
                        else
                            throw FileParserError("malformed input line");

                        // is there a backslash before commented out text ?
                        append_entry_to_prev_key = false;
                        auto scan = content_end;
                        while (scan < limit && line[scan] == ' ')
                            ++scan;
                        if (scan < limit && line[scan] == '\\')
                            append_entry_to_prev_key = true;
                    }
                    else
                    {
                        if (append_entry_to_prev_key)
                        {
                            throw FileParserError("expecting input continuation from previous line");
                        }
                    }
                }
            }
            else
            {
                throw FileParserError("cannot open file: " + a_file_name);
            }
        }

        // get item value of entry a_name
        template <class T>
        void get_item(T &a_val, const std::string& a_name)
        {
            if (const auto it = m_entries.find(a_name); it != m_entries.end())
            {
                std::istringstream line(it->second);
                line.exceptions(std::ios_base::failbit);
                try {
                    line >> a_val;
                } catch (const std::ios_base::failure&) {
                    throw FileParserError("bad value for item: " + a_name);
                }
                if (!line.eof())
                    throw FileParserError("trailing data for item: " + a_name);
            }
            else
            {
                throw FileParserError("item not found: " + a_name);
            }
        }

        // fill a_c container with (a_c.size) items from entry a_name
        template <class T>
        void get_items(T &a_c, const std::string& a_name)
        {
            if (a_c.empty())
                throw FileParserError("container is empty: " + a_name);

            if (const auto it = m_entries.find(a_name); it != m_entries.end())
            {
                std::istringstream line(it->second);
                line.exceptions(std::ios_base::failbit);
                try {
                    for (auto &c : a_c)
                        line >> c;
                } catch (const std::ios_base::failure&) {
                    throw FileParserError("bad value for item: " + a_name);
                }
                if (!line.eof())
                    throw FileParserError("trailing data for item: " + a_name);
            }
            else
            {
                throw FileParserError("item not found: " + a_name);
            }
        }

        // flush entries
        void flush() const
        {
            for (const auto& [key, entry] : m_entries)
            {
                std::cout << "\"" << key << "\" -- \"" << entry << "\"" << '\n';
            }
        }

    protected:
        std::unordered_map<std::string, std::string> m_entries;
    };
}; // namespace fm

#endif
