#!/bin/bash
set -euo pipefail

cd "$(dirname "$0")/.."
test_dir=test
build_dir=build
mkdir -p "$build_dir"
pass=0 fail=0

for f in "$test_dir"/test_*.cpp; do
    name=$(basename "$f" .cpp)
    if ! clang++ -std=c++17 -I src "$f" -o "$build_dir/$name" 2>&1; then
        echo "COMPILE FAIL: $name"
        fail=$((fail + 1))
        continue
    fi
    if "$build_dir/$name" 2>&1; then
        echo "PASS: $name"
        pass=$((pass + 1))
    else
        echo "FAIL: $name (exit $?)"
        fail=$((fail + 1))
    fi
    rm -f "$build_dir/$name"
done

echo ""
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
