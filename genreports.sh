#!/bin/zsh

for file in output/*/*/trips.log
            tools/logparser.py $file
