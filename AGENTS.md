# AGENTS.md

## What this is

Header-only C++ library (`fm::FileParser`) that parses `key=value` input files into a `std::unordered_map<string,string>`. Namespace: `fm`. Single header: `src/FileParser.h`.

## Build & run

No build system. Compile the test manually:

```
clang++ -std=c++17 -I src example/parser.cpp -o parser_example
./parser_example -f example/parser_input
```

Run the test suite:

```
test/run_tests.sh
```

## Input file format

- `key = value` lines; `#` starts a comment; `\` before/after a comment means "continues on next line".
- `get_item(name, T&)` reads a single value; `get_items(name, T&)` fills a container of `T` (container must be pre-sized).
- Parser throws `FileParserError` on missing keys, bad file paths, malformed input, or type mismatches.

## Conventions

- No build config, CI, linter, formatter, or test framework. Changes are validated by compiling and running `example/parser.cpp`.
- C++17 only. Target platform config assumes clang++ on macOS (see `.vscode/c_cpp_properties.json`).
