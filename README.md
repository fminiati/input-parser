# FileParser

A single-header C++ library for parsing `key=value` input files into a `std::unordered_map<string,string>`.

## Features

- Single header, no build system required
- `key = value` syntax with `#` comments and `\` line continuation
- Template-based retrieval into scalars, dynamic containers, or fixed-size arrays
- `get_item<T>(name)` returns a single value; `get_items<Container>(name)` returns an auto-sized container; `get_array<T,N>(name)` returns a fixed-size array
- `get_items` supports any `std::ranges::range` container: `vector`, `deque`, `list`, `set`, `unordered_set`, etc.
- Throws `FileParserError` on missing keys, bad file paths, malformed input, or type mismatches

## Usage

### Input file (`config.txt`)

```
# simulation parameters
steps = 100
dt = 0.001

# particle positions
nparticles = 3
positions = 0.0 1.5 2.3 \   # continues on next line
            3.1 4.0 5.7
```

### C++ code

```cpp
#include "FileParser.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    fm::FileParser parser("config.txt");

    // Read a single value
    auto steps = parser.get_item<int>("steps");
    auto dt = parser.get_item<double>("dt");

    // Read into an auto-sized container
    auto positions = parser.get_items<std::vector<double>>("positions");

    // Read into a container with explicit count (strict: throws if not enough values)
    auto first_three = parser.get_items<std::vector<double>>("positions", 3);

    std::cout << "steps=" << steps << ", dt=" << dt << "\n";
    for (int i = 0; i < positions.size(); ++i)
        std::cout << "  particle " << i << ": " << positions[i] << "\n";
}
```

## Input file format

| Feature | Syntax |
|---|---|
| Comment | `# text` |
| Key-value pair | `key = value` (spaces around `=` optional) |
| Line continuation | `\` before or after a comment |

Continuation appends the next line to the current value:

```
vector = 1.0 2.0 3.0 \ # continues below
         4.0 5.0
```

is parsed as `vector` = `"1.0 2.0 3.0 4.0 5.0"`.

## API

```cpp
namespace fm {

class FileParser {
public:
    // Parse the given input file
    FileParser(const std::string& file_name);

    // Read a single value (type must be specified explicitly)
    template <class T>
    T get_item(const std::string& name) const;

    // Read into a container (count=0 auto-sizes, count>0 is strict)
    // Supports: vector, deque, list, set, unordered_set, etc.
    template <std::ranges::range T>
    T get_items(const std::string& name, std::size_t count = 0) const;

    // Read into a fixed-size array (size is the template parameter)
    template <typename T, std::size_t N>
    std::array<T, N> get_array(const std::string& name) const;

    // Print all parsed key-value pairs to stdout
    void flush() const;
};

} // namespace fm
```

## Build & run

No build system. Compile manually:

```bash
clang++ -std=c++20 -I src example/parser.cpp -o parser_example
./parser_example -f example/parser_input
```

Or run the test suite:

```bash
test/run_tests.sh
```

## License

MIT -- see [LICENSE](LICENSE).
