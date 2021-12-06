arr = []
rows = []
nums = []
for i in open("i1"):
    i = i.strip()
    if len(nums) == 0:
        nums = i.rstrip().split(',')
    elif not i:
        if len(rows) > 0:
            arr.append(rows)
        rows = []
    else:
        rows.append(i.split())
if len(rows):
    arr.append(rows)


print(nums)
printOnes = True 
nn = 0
for n in nums:
    for i,b in enumerate(arr):
        for j,r in enumerate(b):
            for k,l in enumerate(r):
                if l == n:
                    arr[i][j][k] = "X"
    
    idxs = []
    for i,b in enumerate(arr):
        bingo = False
        for r in b:
            if r.count("X") == 5:
                bingo = True

        t = list(map(list,zip(*b)))
        for r in t:
            if r.count("X") == 5:
                bingo = True
        if bingo:
            res = 0
            for r in b:
                for x in r:
                    if x != "X":
                        res += int(x)
            if printOnes or len(arr) == 1:
                print(res*int(n))
                printOnes = False
            idxs.append(i)
    for idx in idxs[::-1]:
        arr.pop(idx)
    nn += 1

