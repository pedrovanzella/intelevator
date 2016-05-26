#!/usr/bin/env python3
from sys import argv
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np


def makegraphs(filename):
    data = loadfile(filename)
    avgWaitingTime(data)
    avgTravelTime(data)
    arrivalsPerFloor(data)
    dropOffsPerFloor(data)
    totalNumberOfClientsDelivered(data)


def loadfile(filename):
    types = np.dtype([
        ('clientID', np.int64),
        ('partySize', np.int8),
        ('elevatorID', np.int8),
        ('arrivalFloor', np.int8),
        ('dropoffFloor', np.int8),
        ('createTime', np.int64),
        ('pickupTime', np.int64),
        ('dropoffTime', np.int64)
    ])
    with open(filename, 'r') as f:
        data = np.loadtxt(f, dtype=types)
        return data


def totalNumberOfClientsDelivered(data):
    print("Total number of clients: ", len(data))
    return len(data)


def findTopFloor(data):
    topfloor = 0

    for d in data:
        if d['arrivalFloor'] > topfloor:
            topfloor = d['arrivalFloor']
        if d['dropoffFloor'] > topfloor:
            topfloor = d['dropoffFloor']

    return topfloor


def arrivalsPerFloor(data):
    maxfloors = findTopFloor(data)
    print("Total number of floors: ", maxfloors)
    fls = []
    for x in range(0, maxfloors):
        fls.append(0)

    for d in data:
        fls[d['arrivalFloor'] - 1] += 1

    N = len(fls)
    x = range(1, N+1)

    plt.bar(x, fls, 1/1.5)
    plt.show()


def dropOffsPerFloor(data):
    maxfloors = findTopFloor(data)
    fls = []
    for x in range(0, maxfloors):
        fls.append(0)

    for d in data:
        fls[d['dropoffFloor'] - 1] += 1

    N = len(fls)
    x = range(1, N+1)

    plt.bar(x, fls, 1/1.5)
    plt.show()


def avgTravelTime(data):
    travelTimes = [x['dropoffTime'] - x['pickupTime'] for x in data]
    plotNormal(travelTimes)


def avgWaitingTime(data):
    maxfloors = findTopFloor(data)

    arrF = [0]
    for f in range(1, maxfloors):
        arrF.append(np.where(data['arrivalFloor'] == f))

    print("oi")
    print(arrF[1])

    waits = [x['pickupTime'] - x['createTime'] for x in data]
    plotNormal(waits)


def plotNormal(data):
    h = sorted(data)

    fit = stats.norm.pdf(h, np.mean(h), np.std(h))
    plt.plot(h, fit, '-o')
    plt.hist(h, normed=True)
    plt.show()

if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
