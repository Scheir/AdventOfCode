from itertools import combinations

weapons = [(8,4), (10,5), (25,6), (40,7), (74,8)]
armor = [(0,0),(13,1), (31,2), (53,3), (75,4), (102, 5)]
rings = [(0,0,0),(0,0,0),(25,1,0), (50,2,0), (100,3,0), (20,0,1), (40,0,2), (80,0,3)]
combrings = list(combinations(rings,2))

boss = (104,1,8)
res = 100000
res2 = 0
for x in weapons:
    for y in armor:
        for i in ("one_ring", "two_rings"):
            if i == "one_ring":
                for z in rings:
                    ph,pd,pa = (100, y[1]+z[2], x[1]+z[1])
                    bh,bd,ba = boss
                    cost = x[0]+y[0]+z[0]
                    while ph > 0 and bh > 0:
                        bh -= max(1,pa-bd)
                        ph -= max(1,ba-pd)
                    if bh <= 0:
                        res = res if res < cost else cost
                    if bh > 0:
                        res2 = res2 if res2 > cost else cost
            else:
                for z1,z2 in combrings:
                    ph,pd,pa = (100, y[1]+z1[2]+z2[2], x[1]+z1[1]+z2[1])
                    bh,bd,ba = boss
                    cost = x[0]+y[0]+z1[0]+z2[0]
                    while ph > 0 and bh > 0:
                        bh -= max(1,pa-bd)
                        ph -= max(1,ba-pd)
                    if bh <= 0:
                        res = res if res < cost else cost
                    if bh > 0:
                        res2 = res2 if res2 > cost else cost

print(res)
print(res2)
