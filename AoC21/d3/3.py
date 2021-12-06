import copy
arr = []
for l in open("i1"):
    arr.append(l.rstrip())

eps = ""
gam = ""

mat = list(map(list,zip(*arr)))

for i in mat:
    zs = i.count('0')
    os = i.count('1')
    eps += '1' if os < zs else '0'
    gam += '0' if os < zs else '1'

print(int(eps,2)*int(gam,2))

arr2 = copy.deepcopy(arr)
mat2 = copy.deepcopy(mat)
x,y = 0,0
for i in range(len(arr[0])):
    zs = mat[i].count('0')
    os = mat[i].count('1')
    if zs == os:
        arr = [r for r in arr if r[i] == '1']
    elif zs > os:
        arr = [r for r in arr if r[i] == '0']
    else:
        arr = [r for r in arr if r[i] == '1']

    if len(arr) == 1:
        break
    mat = list(map(str,zip(*arr)))

for i in range(len(arr[0])):
    zs = mat2[i].count('0')
    os = mat2[i].count('1')
    if zs == os:
        arr2 = [r for r in arr2 if r[i] == '0']
    elif zs > os:
        arr2 = [r for r in arr2 if r[i] == '1']
    else:
        arr2 = [r for r in arr2 if r[i] == '0']

    if len(arr2) == 1:
        break
    mat2 = list(map(str, zip(*arr2)))

x,y = int(arr[0],2),int(arr2[0],2)
print(x*y)


