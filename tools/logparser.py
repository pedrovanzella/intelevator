#!/usr/bin/env python3
from sys import argv
import matplotlib.pyplot as plt

def makegraphs(file):
    plt.plot([1, 2, 3, 4])
    plt.ylabel('some numbers')
    plt.show()

if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
