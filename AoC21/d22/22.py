from collections import *
from itertools import *
from functools import *
import re

arr = []
for l in open("i1"):
    oo,b = l.split()
    a,b,c = b.split(",")
    a0,a1 = a.split("..")
    b0,b1 = b.split("..")
    c0,c1 = c.split("..")
    # add +1 as the input is inclusive and range is used later 
    arr.append((oo,int(a0[2:]),int(a1)+1,int(b0[2:]),int(b1)+1,int(c0[2:]),int(c1)+1))
    
# The idea here is to calculate the area of the current cuboid
# and subtract all of the area that cuboids after are covering
# within the current cuboid.
# This has to be done in a recursive manner as the area of the 
# sub cubes also has to be subtracted with their following cuboids

def calculate_unique_for_cube(current,sub_cubes):
    x0,x1,y0,y1,z0,z1 = current 
    #size of cube
    res = len(range(x0,x1))*len(range(y0,y1))*len(range(z0,z1))

    # We want to recurse through all of the sub cubes 
    # and subtract the unique parts with respect to the subcubes
    # from the current cube
    
    sub_cubes_to_process = []

    for elem in sub_cubes:
        x0b,x1b,y0b,y1b,z0b,z1b = elem

        # find the new low and high values
        # for each next sub cube, if it is 
        # within range of the current one
        # we take that cube part that is a sub part of current
        # we add it to the proccessing list
        # Otherwise continue with next
        if x0b > x1 or x1b < x0:
            continue
        else:
            x0b = max(x0,x0b)
            x1b = min(x1,x1b)
        if y0b > y1 or y1b < y0:
            continue
        else:
            y0b = max(y0,y0b)
            y1b = min(y1,y1b)
        if z0b > z1 or z1b < z0:
            continue
        else:
            z0b = max(z0,z0b)
            z1b = min(z1,z1b)
        sub_cubes_to_process.append([x0b,x1b,y0b,y1b,z0b,z1b])
    
    # We have collected all subcubes, now calculate the unique
    # part for each of them with respect to following ones
    for idx,sub_cube in enumerate(sub_cubes_to_process):
        res -= calculate_unique_for_cube(sub_cube,sub_cubes_to_process[idx+1:])
    return res

#Get rid of the on/off for cleaner code
reduced_arr = [x[1:] for x in arr]
res = 0
p1 = True

# Itereate each cuboid and sum its unique lights if they are switched on
for idx, cube in enumerate(arr):
    #Solve P1
    if p1:
        if any([True for x in reduced_arr[idx] if x>50 or x<-50]):
            print(res)
            p1 = False
    if cube[0] == "off":
        continue
    res += calculate_unique_for_cube(reduced_arr[idx],reduced_arr[idx+1:])

print(res)
