#!/bin/bash

NAME="$1";
echo "name:${NAME}"

g++ "${NAME}.cpp" -o ${NAME} -std=c++20 -pedantic -Wall

if [ -f "results.res" ]; then
    rm results.res
fi

for i in {01..50}; do
    test_file="test${i}.in"
    if [ -f "$test_file" ]; then
        ./${NAME} < "$test_file" >> results.res
    else
        echo "File not found: $test_file"
    fi
done

awk '{print "test", NR, ":", $0}' results.res

