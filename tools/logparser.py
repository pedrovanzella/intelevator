#!/usr/bin/env python3
from sys import argv
import matplotlib.pyplot as plt
import numpy as np

def makegraphs(filename):
    data = loadfile(filename)
    print(data)
    plt.plot(data)
    plt.ylabel('some numbers')
    plt.show()

def loadfile(filename):
    with open(filename, 'r') as f:
        data = np.loadtxt(f, dtype={'names':
                                    ('clientID', 'partySize', 'elevatorID',
                                     'arrivalFloor', 'dropoffFloor',
                                     'createTime', 'pickupTime',
                                     'dropoffTime'),
                                    'formats':
                                    ('i4', 'i4', 'i4', 'i4', 'i4',
                                     'i4', 'i4', 'i4')})
        return data

if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
