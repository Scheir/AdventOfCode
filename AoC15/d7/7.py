arr = []
d = {}
with open("i1") as file:
    for line in file:
        splitted_string = line.rstrip().split()
        arr.append(splitted_string)
        for s in splitted_string:
            if s.islower():
                d[s] = 0
                    
for iterations in range(2): 
    for runs in range(0,10000):
        for x in arr:
            if len(x) == 3:
                a,_,c = x
                if c == 'b' and d[c] != 0:
                    continue
                if a.isdigit():
                    d[c] = int(a)
                else:
                    d[c] = d[a]
            elif len(x) == 4:
                _,a,__,b = x
                a = a if a.isdigit() else d[a]
                d[b] = ~a & 0xffff
            else:
                a,b,c,_,e = x
                a = int(a) if a.isdigit() else d[a]
                c = int(c) if c.isdigit() else d[c]
                if b == "AND":
                    d[e] = a & c 
                elif b == "OR":
                    d[e] = a | c
                elif b == "LSHIFT":
                    d[e] = a << int(c)
                else:
                    d[e] = a >> int(c)
    wire_a = d['a']
    print(wire_a)
    for x in d:
        d[x] = 0
    d['b'] = wire_a

