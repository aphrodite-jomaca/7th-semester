#!/usr/bin/env python3
import sys

arr = []
arrb = [1, 2, 4, 8, 16]

with open(sys.argv[1], 'rt') as f:
    arr = [float(x) for x in next(f).split()]


if sys.argv[2] == "case4":
    min = arr[0]
    pos = 0
    for i in range(0, 5):
        if min > arr[i]:
            min = arr[i]
            pos = i

    print("The pest B is :", arrb[pos])

else:
    import matplotlib.pyplot as plt 
    import numpy as np 
    bx=[1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 36, 48, 72, 144]
    by=[1, 2, 4, 8, 11, 16, 22, 44, 88, 176]
    y = len(by)
    x = []
    min = arr[0]
    for i in range(len(bx)):
        for j in range(len(by)):
            x.append(i*y+j)
            if min > arr[i*y+j]:
                min = arr[i*y+j]
                posi = i
                posj = j
    best = str(bx[posi])+'x'+str(by[posj])
    print('The best size N x M is :',best, 'with average time:', min, 'usecs')

    xx = []
    n_m = []
    for i in bx:
        for j in by:
            n_m.append(str(i)+'x'+str(j))
    u = []
    for k in range(0, len(n_m)-1, 10):
        u.append(n_m[k])
        xx.append(k)

    xx.append(posi*y+posj)
    u.append(best)
    plt.xticks(xx, u, rotation=45)
    plt.title('Process Time For Each NxM Values')
    plt.ylabel('usecs')

    plt.plot(x, arr)    
    plt.show()