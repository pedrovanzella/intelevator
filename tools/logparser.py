#!/usr/bin/env python3
from sys import argv
import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


def makegraphs(filename):
    data = loadfile(filename)
    folderpath = os.path.dirname(filename) + '/'
    clientsPerElevator(data, folderpath)
    arrivalsPerFloor(data, folderpath)
    dropoffsPerFloor(data, folderpath)
    averageTravelTime(data, folderpath)
    averageWaitTime(data, folderpath)


def loadfile(filename):
    return pd.read_csv(filename, sep=' ', index_col='clientID')


def clientsPerElevator(data, folderpath):
    plt.clf()
    ax = sns.barplot(x=data.elevatorID.value_counts().index,
                     y=data.elevatorID.value_counts())
    ax.set(xlabel="Elevator",
           ylabel="Clients")
    ax.get_figure().savefig(folderpath + "clientsPerElevator.eps")


def arrivalsPerFloor(data, folderpath):
    plt.clf()
    ax = sns.barplot(x=data.arrivalFloor.value_counts().index,
                     y=data.arrivalFloor.value_counts())
    ax.set(xlabel="Floor",
           ylabel="Clients")
    ax.get_figure().savefig(folderpath + "arrivalsPerFloor.eps")


def dropoffsPerFloor(data, folderpath):
    plt.clf()
    ax = sns.barplot(x=data.dropoffFloor.value_counts().index,
                     y=data.dropoffFloor.value_counts())
    ax.set(xlabel="Floor",
           ylabel="Clients")
    ax.get_figure().savefig(folderpath + "dropoffsPerFloor.eps")


def averageTravelTime(data, folderpath):
    plt.clf()
    data['travelTime'] = data['dropoffTime'] - data['pickupTime']
    g = sns.FacetGrid(data, col='dropoffFloor', row='arrivalFloor')
    g = g.map(sns.barplot, "travelTime", orient='v')
    g.fig.savefig(folderpath + "averageTravelTime.eps")


def averageWaitTime(data, folderpath):
    plt.clf()
    data['waitTime'] = data['pickupTime'] - data['createTime']
    waits = data.groupby('arrivalFloor',
                         as_index=False).aggregate(np.average)['waitTime']
    ax = sns.barplot(x=waits.index, y=waits)
    ax.set(xlabel="Floor",
           ylabel="Average Wait Time")
    ax.get_figure().savefig(folderpath + "averageWaitTime.eps")


if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
