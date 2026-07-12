#!/bin/bash
set -euo pipefail

cd "$(dirname "$0")/.."
test_dir=test
pass=0 fail=0

for f in "$test_dir"/test_*.cpp; do
    name=$(basename "$f" .cpp)
    if ! clang++ -std=c++17 -I src "$f" -o "$test_dir/$name" 2>&1; then
        echo "COMPILE FAIL: $name"
        ((fail++))
        continue
    fi
    if "$test_dir/$name" 2>&1; then
        echo "PASS: $name"
        ((pass++))
    else
        echo "FAIL: $name (exit $?)"
        ((fail++))
    fi
    rm -f "$test_dir/$name" "$test_dir/${name}_input"
done

echo ""
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
