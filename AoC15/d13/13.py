from itertools import permutations
def get_res(d, s):
    happiness = []
    for p in permutations(s):
        current_setting = sum(map(lambda x, y: d[(x,y)]+d[(y,x)], p[:-1], p[1:])) + d[(p[0],p[-1])] + d[(p[-1],p[0])] 
        happiness.append(current_setting)
    return max(happiness)

d = {}
s = set()
with open("i1") as file:
    for l in file:
        a,_,b,c,_,_,_,_,_,_,e = l.rstrip()[:-1].split()
        c = int(c) if b == "gain" else -int(c)
        d[(a,e)] = c
        s.add(a)

print(get_res(d,s))

for x in s:
    d[("me",x)] = 0
    d[(x,"me")] = 0
s.add("me")

print(get_res(d,s))
