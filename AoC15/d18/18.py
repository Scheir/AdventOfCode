from copy import deepcopy
mat = []
with open("i2") as file:
    for l in file:
        mat.append(list(l.rstrip()))
mat2 = deepcopy(mat)
mat2[0][0] = '+'
mat2[-1][0] = '+'
mat2[0][-1] = '+'
mat2[-1][-1] = '+'
for x in range(100):
    mc = deepcopy(mat)
    mc2 = deepcopy(mat2)
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            count = 0
            count2 = 0
            for dx in (-1,0,1):
                for dy in (-1,0,1):
                    if dx == dy == 0:
                        continue
                    dxx = i+dx
                    dyy = j+dy
                    if dxx in range(len(mat)) and dyy in range(len(mat[0])):
                        count += 1 if mc[dxx][dyy] == '#' else 0
                        count2 += 1 if mc2[dxx][dyy] in ('#', '+') else 0
            if mc[i][j] == '#':
                if count not in (2,3):
                    mat[i][j] = '.'
            elif mc[i][j] == '.':
                if count == 3:
                    mat[i][j] = '#'

            if mc2[i][j] == '#':
                if count2 not in (2,3):
                    mat2[i][j] = '.'
            elif mc2[i][j] == '.':
                if count2 == 3:
                    mat2[i][j] = '#'

res = sum([x.count('#') for x in mat])
res2 = sum([x.count('#') for x in mat2])+4
print(res)
print(res2)
