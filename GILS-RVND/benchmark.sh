#!/bin/zsh
for file in instances/*; do
    echo $file
    ./tsp $file >> results.txt
done
