#!/usr/bin/env python3
from sys import argv
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np


def makegraphs(filename):
    data = loadfile(filename)
    totalNumberOfClientsDelivered(data)
    avgWaitingTime(data)
    avgTravelTime(data)


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


def totalNumberOfClientsDelivered(data):
    print("Total number of clients: ", len(data))
    return len(data)


def getTimes(data):
    return data[:, [5, 6, 7]]


def avgTravelTime(data):
    times = getTimes(data)
    travelTimes = [x[2] - x[1] for x in times]
    plotNormal(travelTimes)


def avgWaitingTime(data):
    times = getTimes(data)
    waits = [x[1] - x[0] for x in times]
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
