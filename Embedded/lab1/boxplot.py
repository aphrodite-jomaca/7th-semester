#!/usr/bin/env python
#we need matplotlibs
##sudo apt-get install python-matplotlib
# Import libraries 
import os
import subprocess 
import matplotlib.pyplot as plt 
import numpy as np 

################ phods ########################
exe="gcc -O0 -o phods2 phods2.c"
os.system(exe)               #compile phods

exe="~/Embedded/lab_material/1/phods2 >> temp_for_plot"

if os.path.exists("temp_for_plot"):
    os.remove("temp_for_plot")

for i in range(10):
    os.system(exe)

arr1 = []

with open('temp_for_plot', 'rt') as f:
    arr1 = [int(x) for x in next(f).split()]

#print(arr1)
################## phods3 ########################

exe="gcc -O0 -o phods3 phods3.c"
os.system(exe)               #compile phods
os.remove("temp_for_plot")

exe="~/Embedded/lab_material/1/phods3 >> temp_for_plot"

for i in range(10):
    os.system(exe)

arr2 = []

with open('temp_for_plot', 'rt') as f:
    arr2 = [int(x) for x in next(f).split()]


################## phods4 ########################

exe="gcc -O0 -o phods4 phods4.c"
os.system(exe)               #compile phods
os.remove("temp_for_plot")

arr3 = []

b = 16
for i in range(10):
    exe="~/Embedded/lab_material/1/phods4 " + str(16) + " >> temp_for_plot"
    os.system(exe)



with open('temp_for_plot', 'rt') as f:
    arr3 = [int(x) for x in next(f).split()]

###################### phods5 ###########################

exe="gcc -O0 -o phods5 phods5.c"
os.system(exe)               #compile phods5
os.remove("temp_for_plot")
arr4 = []

bx = 144
by = 176

for k in range(10):
    exe="~/Embedded/lab_material/1/phods5 " + str(bx) + " " + str(by) + " >> temp_for_plot"
    os.system(exe)


with open('temp_for_plot', 'rt') as f:
    arr4 = [int(x) for x in next(f).split()]

#print(arr4)

####################################################


data  = [arr1, arr2, arr3, arr4]

fig, ax = plt.subplots()
ax.set_title('process time')
ax.boxplot(data)
plt.xticks([1, 2, 3, 4], ['phods', 'phods3', 'phods4', "phods5"])
ax.set_ylabel('u sec')
plt.show() 

print("nice")