#!/usr/bin/env python3
from sys import argv
import os
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt


def makegraphs(filename):
    data = loadfile(filename)
    folderpath = os.path.dirname(filename) + '/'
    clientsPerElevator(data, folderpath)
    arrivalsPerFloor(data, folderpath)
    dropoffsPerFloor(data, folderpath)


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


if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
