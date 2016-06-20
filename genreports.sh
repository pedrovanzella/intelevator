#!/bin/zsh

for file in output/Skyscraper/*/trips.log
            tools/logparser.py $file
