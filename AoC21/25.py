from copy import deepcopy
arr = []
for x in open("i1"):
    x = x.rstrip()
    if x:
        arr.append(list(x))

R = len(arr)
C = len(arr[0])

turn = 0
while True:
    cnt = 0
    ta = deepcopy(arr)
    for i in range(R):
        for j in range(C):
            if ta[i][j] == ">" and ta[i][(j+1)%C] == ".":
                arr[i][j] = "."
                arr[i][(j+1)%C] = ">"
                cnt += 1
    ta = deepcopy(arr)
    for i in range(R):
        for j in range(C):
            if ta[i][j] == "v" and ta[(i+1)%R][j] == ".":
                arr[i][j] = "."
                arr[(i+1)%R][j] = "v" 
                cnt += 1
    turn += 1
    if cnt == 0:
        print(turn)
        exit()

