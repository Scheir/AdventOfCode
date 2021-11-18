from itertools import permutations

d = {}
s = set()
with open("i1") as file:
    for f in file:
        fr, to, dist = f.rstrip().split()[::2]
        d[(fr,to)] = int(dist)
        d[(to,fr)] = int(dist)
        s.add(fr)
        s.add(to)

distances_arr = []
for p in permutations(s):
    distances_arr.append(sum(map(lambda x,y: d[(x,y)], p[:-1], p[1:])))

print(min(distances_arr))
print(max(distances_arr))
