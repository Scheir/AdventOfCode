from collections import *

arr = []
for row in open("i1"):
    arr.append(row.strip())

D = defaultdict(int)
stk = [] # Keep track of where we are
for row in arr:
    x = row.strip().split() 
    if x[1] == "cd":
        if x[2] == "..":
            stk.pop()
        elif x[2] == "/":
            stk = ["/"]
        else:
            stk.append(x[ 2 ])
            
    elif x[0].isnumeric():
        # Add the size to current and all parents:
        # stk = [/,a,b,c]
        # /, /a, /a/b, /a/b/c -> all are increased
        for i in range(len(stk)):
            D['/'.join(stk[:i+1])] += int(x[0])
    else:
        pass 
        # Useless data

print(sum(v for v in D.values() if v <= 100000))

#P2
NEEDED = 30000000 - (70000000 - D["/"])
print(min(x for x in D.values() if x > NEEDED))
