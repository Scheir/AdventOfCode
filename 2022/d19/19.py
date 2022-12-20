import re
from collections import deque
arr = []
for row in open("i1"):
    a,b,c,d,e,f,g = [int(x) for x in re.findall("\d+", row)]
    arr.append((b,c,(d,e),(f,g)))


def solve(ore_cost, clay_cost, obsidian_cost, geode_cost, T = 24):
    ret = 0
    q = deque()
    q.append(((1,0,0,0),(0,0,0,0),T))
    seen = set() 
    while q:
        robots,ores,t =  q.popleft()
        r_o, r_c, r_ob, r_g= robots
        ore, clay, obsidian, geode = ores

        if t == 0:
            ret = max(ret,geode) 
            continue
        
        # OPTIMISATIONS
        # Never equip more ORE of any kind than ever will be needed,
        # Never use more robots than maximum cost of a certain ORE either.
        # Reducing search space enough to Bruteforce the shit
        if ore >= (t-1)*max(ore_cost,clay_cost,obsidian_cost[0],geode_cost[0]):
            ore = max(ore_cost,clay_cost,obsidian_cost[0],geode_cost[0])

        if r_o >= max(ore_cost,clay_cost,obsidian_cost[0],geode_cost[0]):
            r_o = max(ore_cost,clay_cost,obsidian_cost[0],geode_cost[0])

        if clay >= (t-1)*obsidian_cost[1]:
            clay = obsidian_cost[1]

        if r_c >= obsidian_cost[1]:
            r_c = obsidian_cost[1]

        if obsidian >= (t-1)*geode_cost[1]:
            obsidian = geode_cost[1]

        if r_ob >= geode_cost[1]:
            r_ob = geode_cost[1]

        if (ore,clay,obsidian,geode,r_o,r_c,r_ob,r_g) in seen:
            continue

        seen.add((ore,clay,obsidian,geode,r_o,r_c,r_ob,r_g))

        # Cant produce any robot
        q.append(((robots),(ore+r_o,clay+r_c,obsidian+r_ob,geode+r_g),t-1))
        # Ore robot
        if ore >= ore_cost:
            q.append(((r_o+1,r_c,r_ob,r_g),(ore-ore_cost+r_o, clay+r_c, obsidian+r_ob, geode+r_g),t-1))
        # Clay robot
        if ore >= clay_cost:
            q.append(((r_o,r_c+1,r_ob,r_g),(ore-clay_cost+r_o, clay+r_c, obsidian+r_ob, geode+r_g),t-1))
        # Obsidian cost
        o,c = obsidian_cost
        if ore >= o and clay >= c:
            q.append(((r_o,r_c,r_ob+1,r_g),(ore-o+r_o, clay-c+r_c, obsidian+r_ob, geode+r_g),t-1))
        #Geode cost
        o,ob = geode_cost
        if ore>=o and obsidian>=ob:
            q.append(((r_o,r_c,r_ob,r_g+1),(ore-o+r_o, clay+r_c, obsidian-ob+r_ob, geode+r_g),t-1))

    return ret

res = 0
res2 = 1;
for i,row in enumerate(arr,1): 
    res += i*solve(*row)
    if i in (1,2,3):
        res2 *= solve(*row,32)
print(res)
print(res2)
