#!/bin/zsh

for file in output/*/*/arrivals.log
            echo Generating report for $file
            tools/logparser.py $file
