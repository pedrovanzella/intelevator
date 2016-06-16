#!/bin/zsh

for file in output/Low-rise/*/trips.log
            tools/logparser.py $file
