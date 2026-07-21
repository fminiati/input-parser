# FileParser

A single-header C++ library for parsing `key=value` input files into a `std::unordered_map<string,string>`.

## Features

- Single header, no build system required
- `key = value` syntax with `#` comments and `\` line continuation
- Template-based retrieval into scalars or pre-sized containers (`vector`, `list`, `array`, etc.)
- Throws `FileParserError` on missing keys, bad file paths, or malformed input
- Type mismatches throw `std::ios_base::failure`

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
    int steps{};
    parser.get_item(steps, "steps");

    double dt{};
    parser.get_item(dt, "dt");

    // Read into a pre-sized container
    int n{};
    parser.get_item(n, "nparticles");

    std::vector<double> positions(n);
    parser.get_items(positions, "positions");

    std::cout << "steps=" << steps << ", dt=" << dt << "\n";
    for (int i = 0; i < n; ++i)
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
    FileParser(const std::string file_name);

    // Read a single value into a scalar
    template <class T>
    void get_item(T &val, const std::string name);

    // Fill a pre-sized container with values
    template <class T>
    void get_items(T &container, const std::string name);

    // Print all parsed key-value pairs to stdout
    void flush() const;
};

} // namespace fm
```

## Build & run

No build system. Compile manually:

```bash
clang++ -std=c++17 -I src example/parser.cpp -o parser_example
./parser_example -f example/parser_input
```

Or run the test suite:

```bash
test/run_tests.sh
```

## License

MIT -- see [LICENSE](LICENSE).
