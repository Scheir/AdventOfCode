from collections import deque

arr = []
for row in open("i1"):
    arr.append(int(row.strip()))

# DUPLICATES in input,so we need to seperate the numbers
# index in arr works fine
Q = deque([(i,x) for i,x in enumerate(arr)])

N = len(Q)-1
for i,v in enumerate(arr):
    # Find index
    IDX = Q.index((i,v))
    # rotate left to get value at IDX 0
    # To remove the value we are moving
    Q.rotate(-IDX)
    #Pop the value
    Q.popleft()
    # Rotate Again to insert value at the correct place
    Q.rotate(-v % N)
    Q.appendleft((i,v))
Q = deque([x for _,x in Q])
Q.rotate(-Q.index(0))
print(Q[1000]+Q[2000]+Q[3000])


# P2
# Exactly the same as P1
arr = []
for row in open("i1"):
    arr.append(int(row.strip())*811589153)
Q = deque([(i,x) for i,x in enumerate(arr)])
N = len(Q)-1
for _ in range(10):
    for i,v in enumerate(arr):
        IDX = Q.index((i,v))
        Q.rotate(-IDX)
        Q.popleft()
        Q.rotate(-v % N)
        Q.appendleft((i,v))
Q = deque([x for _,x in Q])
Q.rotate(-Q.index(0))
print(Q[1000]+Q[2000]+Q[3000])
