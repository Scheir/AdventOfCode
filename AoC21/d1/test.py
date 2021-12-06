from functools import reduce
arr = []
with open("i1") as file:
    for l in file:
        arr.append(int(l.rstrip()))

cur = 0
res = -1 
for x in arr:
    if x > cur:
        res += 1
    cur = x

cur = 0
res2 = -1
for x in range(len(arr)-2):
    a,b,c = arr[x:x+3]
    s = a+b+c
    if s > cur:
        res2 += 1
    cur = s

print(res)
print(res2)


print("P1:", sum(x < y for x,y in zip(arr, arr[1:])))
print("P2:", sum([1 * x < y for x,y in zip(arr, arr[3:])]))


vec = [1,2,3,4,5,6]
print(list([x+y for x,y in zip(vec,vec[3:])]))

print(sum(map(lambda x,y: x < y, arr, arr[1:])))

mat = [[1,2,3],[4,5,6]]

print(list(list(i) for i in zip(*mat)))


