from itertools import combinations
from functools import reduce
arr = []
with open("i1") as file:
    for l in file:
        arr.append(int(l.rstrip()))

def smallest_quantum_entanglement(groups):
    w = sum(arr)//groups
    m = -1
    for x in range(2,len(arr)-1):
        for c in combinations(arr,x):
            if sum(c) == w:
                mm = reduce(lambda x,y: x*y,c)
                if m == -1 or mm < m:
                    m = mm
        if m > 0:
            return m

print(smallest_quantum_entanglement(3))
print(smallest_quantum_entanglement(4))
              

