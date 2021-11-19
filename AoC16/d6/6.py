from collections import Counter
arr = []
with open("i1") as file:
    for i in file:
        arr.append(list(i.rstrip()))

mat = list(map(list,zip(*arr)))
string = ""
string2 = ""
for x in mat:
    lst = Counter(x).most_common()
    a,_ = lst[0]
    b,_ = lst[-1]
    string += a
    string2 += b

print(string)
print(string2)
