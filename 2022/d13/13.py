import re
from functools import cmp_to_key
from itertools import zip_longest
inp = open("i1").read().strip().split("\n\n")

arr = []
for rows in inp:
    arr.append(rows.split("\n"))

def solve(x,y):
    if type(x) == list and type(y) == list:
        for u,v in zip_longest(x,y):
            # If any side is longer the other one is None
            # After all possible comparisons, longer = win
            if u == None:
                return -1
            if v == None:
                return 1

            # If both items are ints, check if anyone is a winner
            # Else continue
            if type(u) == int and type(v) == int:
                if u != v:
                    return -1 if u < v else 1

            # atleast one list, recurse 
            else:
                b = solve(u,v)
                # If any winner in the inner recurse round
                # return, otherwise keep iterating
                
                # Handles cases like [1,[2,2],3] , [1,[2,2],4]
                # The [2,2] parts are the recursed parts 
                if b != None:
                    return -1 if b == -1 else 1

    if type(x) == int and type(y) == list:
        return solve([x],y)

    if type(x) == list and type(y) == int:
        return solve(x,[y])
    



cnt = 0
for i,t in enumerate(arr,1):
    a,b = [eval(x) for x in t]
    if solve(a,b) == -1: 
        cnt += i

print(cnt)

all_items = []
for a,b in arr:
    all_items.append(eval(a))
    all_items.append(eval(b))

all_items += [[[2]]]+[[[6]]]

# Sort the list and search for the decoder keys
all_items = sorted(all_items,key=cmp_to_key(solve)) 
print((all_items.index([[2]])+1)*(all_items.index([[6]])+1))
