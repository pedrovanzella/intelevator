#!/usr/bin/env python3
from sys import argv
import os
import pandas as pd
import seaborn as sns


def makegraphs(filename):
    data = loadfile(filename)
    folderpath = os.path.dirname(filename) + '/'
    clientsPerElevator(data, folderpath)


def loadfile(filename):
    return pd.read_csv(filename, sep=' ', index_col='clientID')


def clientsPerElevator(data, folderpath):
    ax = sns.barplot(x=data.elevatorID.value_counts().index,
                     y=data.elevatorID.value_counts())
    ax.set(xlabel="Elevador",
           ylabel="Clientes")
    ax.get_figure().savefig(folderpath + "clientsPerElevator.eps")


if __name__ == "__main__":
    sns.set(color_codes=True)
    sns.set_style("whitegrid")

    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    makegraphs(argv[1])
