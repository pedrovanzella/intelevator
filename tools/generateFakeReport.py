#!/usr/bin/env python3
from sys import argv
import numpy as np

# 0: clientID
# 1: partySize
# 2: elevatorID
# 3: arrivalFloor
# 4: dropoffFloor
# 5: createTime
# 6: pickupTime
# 7: dropoffTime


def genreport(name):
    ids = np.arange(0, 1000, 1)
    partySize = np.random.randint(1, 3, size=1000)
    elevatorID = np.random.randint(1, 4, size=1000)
    arrivalFloor = np.random.randint(1, 8, size=1000)
    dropoffFloor = np.random.randint(1, 8, size=1000)
    createTime = np.random.randint(0, 100000, size=1000)
    pickupTime = np.asarray([x + np.random.randint(10, 30) for x in createTime])
    dropoffTime = np.asarray([x + np.random.randint(10, 30) for x in pickupTime])

    data = np.stack((ids, partySize, elevatorID, arrivalFloor,
                    dropoffFloor, createTime, pickupTime,
                    dropoffTime), axis=-1)

    np.savetxt(name, data, fmt='%d')


if __name__ == "__main__":
    if len(argv) < 2:
        print("Usage: %s logfile" % argv[0])
        exit()

    genreport(argv[1])
