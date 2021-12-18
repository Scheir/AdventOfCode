from itertools import *
from collections import *
import re

def explode(num):
    num = str(num).replace(' ','')
    cnt = 0
    for i, c in enumerate(num):
        if c == "[":
            cnt += 1
            if cnt == 5:
                # Find the pair we want to explode
                # seperate it from the left and right part of it
                close_brace = num.find("]", i)
                #The exploding pair, a is the left value and b is the right val
                a,b = list(map(int, num[i+1:close_brace].split(",")))
                # Everything left of the exploding pair
                left = list(num[:i])
                # Everything right of the exploding pair
                right = list(num[close_brace+1:])

                # Find the indicies of the start and end of left val 
                for li in range(len(left)-1,-1,-1):
                    if left[li].isdigit():
                        lis = li 
                        while left[lis].isdigit():
                            lis -= 1
                        left[lis+1:li+1] = str(int(''.join(left[lis+1:li+1]))+a)
                        break
                # Find the indicies of the start and end of right val 
                for ri in range(len(right)):
                    if right[ri].isdigit():
                        riend = 0
                        while right[ri+riend].isdigit():
                            riend += 1
                        right[ri:ri+riend] = str(int(''.join(right[ri:ri+riend]))+b)
                        break
                # Merge the left part, the exploded part and the right part
                return ''.join(left) + "0" + ''.join(right)
                    
        elif c == "]":
            cnt -= 1
    return None

def num_split(num):
    num = str(num).replace(" ","")
    # Find the first digit that is greater then 9,
    # split it into the 2 new digits by dividing by 2
    match = re.search("\d{2,}",num)
    if match:
        match = match.group()
        a,b = divmod(int(match),2)
        replace_string = "[" + str(a) + "," + str(a+b) + "]"
        num = num.replace(match, replace_string, 1)
        return num
    else:
        return None

def num_reduce(num):
    # Both Explode and split return None if there is 
    # nothing to be done. If that is the case for both
    # we are done.
    while True:
        ns = explode(num)
        if ns:
            num = ns 
            continue
        ns = num_split(num)
        if ns:
            num = ns 
            continue
        return str(num)

# Transform string to array to merge them
def nums_add(n1,n2):
    n1 = eval(n1)
    n2 = eval(n2)
    return [n1,n2]

def magnitude(num): 
    if isinstance(num, list): 
        a, b = num 
        a = magnitude(a) 
        b = magnitude(b) 
        return 3*a + 2*b 
    return num 


arr = []
for i in open("i1"):
    i = i.strip()
    arr.append(i)

#needed for part 2
arr2 = arr.copy()

num = arr.pop(0)
for x in arr:
    num = nums_add(num,x)
    num = num_reduce(num)

# Part One
print(magnitude(eval(num)))

# Part Two
res2 = 0

# Brute force part two by trying all combinations
for c in combinations(arr2,2):
    a,b = c
    num = nums_add(a,b)
    num = num_reduce(num)
    res2 = max(res2, magnitude(eval(num)))
print(res2)

