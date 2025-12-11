#!/bin/bash

# Compile the program (optional if already compiled)
g++ src/Pattern-Strategy-TextFormatter.cpp -o textformatter

# Define test cases
declare -a sentences=("tHiS iS a TeSt" "" "hELLO, u$3r@bC!")

echo "Running text formatter tests..."
echo "================================"

for input_sentence in "${sentences[@]}"; do
    echo "Input: '$input_sentence'"
    echo "--------------------------------"

    # Case 1: Uppercase
    output=$(printf "%s\n1\n" "$input_sentence" | ./textformatter)
    expected=$(echo "$input_sentence" | tr '[:lower:]' '[:upper:]')
    echo "Uppercase Output: '$output'"
    if echo "$output" | grep -q "$expected"; then
        echo "PASS"
    else
        echo "FAIL (expected '$expected')"
    fi
    echo

    # Case 2: Lowercase
    output=$(printf "%s\n2\n" "$input_sentence" | ./textformatter)
    expected=$(echo "$input_sentence" | tr '[:upper:]' '[:lower:]')
    echo "Lowercase Output: '$output'"
    if echo "$output" | grep -q "$expected"; then
        echo "PASS"
    else
        echo "FAIL (expected '$expected')"
    fi
    echo

    # Case 3: Title Case
    output=$(printf "%s\n3\n" "$input_sentence" | ./textformatter)
    # Expected: capitalize each word (basic approximation)
    expected=$(echo "$input_sentence" | awk '{for(i=1;i<=NF;i++){ $i=toupper(substr($i,1,1)) tolower(substr($i,2)) }}1')
    echo "Title Case Output: '$output'"
    if echo "$output" | grep -q "$expected"; then
        echo "PASS"
    else
        echo "FAIL (expected '$expected')"
    fi
    echo

    # Default (no formatting)
    output=$(printf "%s\n\n" "$input_sentence" | ./textformatter)
    expected="$input_sentence"
    echo "Default Output: '$output'"
    if echo "$output" | grep -q "$expected"; then
        echo "PASS"
    else
        echo "FAIL (expected '$expected')"
    fi
    echo "================================"
done
