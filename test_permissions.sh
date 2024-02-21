#!/bin/bash

gcc permissions.c -o permissions

declare -a tests=(
    "600 foo bar r foo bar"      
    "640 foo bar r foo b"        
    "600 foo bar r other bar"    
    "640 foo bar rw other bar"  
    ""                           
    "\"everyone has access\" foo bar r foo bar" 
)

for test in "${tests[@]}"; do
    echo "Running test: permissions $test"
    ./permissions $test
    status=$?
    echo "Exit status: $status"
    echo "---------------------"
done
