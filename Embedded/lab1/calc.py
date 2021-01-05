import sys

arr = []

with open(sys.argv[1], 'rt') as f:
    arr = [int(x) for x in next(f).split()]

max = arr[0]
min = arr[0]
sum = 0

for i in arr:
    if max < i: max = i
    if min > i: min = i
    sum = sum + i

avg = sum / len(arr)
print("max =",max,", min =", min,", average =", avg)

f = open("temp","a")
f.write(str(avg)+" ")
f.close()