#!/usr/bin/env python3
from sys import argv
import os
import pandas as pd
import seaborn as sns


def makegraphs(filename):
    data = loadfile(filename)
    folderpath = os.path.dirname(filename) + '/'
    clientsPerElevator(data, folderpath)
    arrivalsPerFloor(data, folderpath)


def loadfile(filename):
    return pd.read_csv(filename, sep=' ', index_col='clientID')


def clientsPerElevator(data, folderpath):
    ax = sns.barplot(x=data.elevatorID.value_counts().index,
                     y=data.elevatorID.value_counts())
    ax.set(xlabel="Elevator",
           ylabel="Clients")
    ax.get_figure().savefig(folderpath + "clientsPerElevator.eps")


def arrivalsPerFloor(data, folderpath):
    ax = sns.barplot(x=data.arrivalFloor.value_counts().index,
                     y=data.arrivalFloor.value_counts())
    ax.set(xlabel="Floor",
           ylabel="Clients")
    ax.get_figure().savefig(folderpath + "arrivalsPerFloor.eps")


if __name__ == "__main__":
    sns.set(color_codes=True)
    sns.set_style("whitegrid")

    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
