#!/usr/bin/env python3
from sys import argv
import matplotlib.pyplot as plt
import numpy as np


def makegraphs(filename):
    data = loadfile(filename)
    print(data)
    times = getTimes(data)
    print(times)
    plt.plot(data)
    plt.ylabel('some numbers')
    plt.show()


def loadfile(filename):
    # 0: clientID
    # 1: partySize
    # 2: elevatorID
    # 3: arrivalFloor
    # 4: dropoffFloor'
    # 5: createTime
    # 6: pickupTime
    # 7: dropoffTime
    with open(filename, 'r') as f:
        data = np.loadtxt(f)
        return data


def getTimes(data):
    return data[:, [5, 6, 7]]

if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
