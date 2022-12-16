from heapq import *
import re

D = {}
F = {}

for row in open("i1"):
    first = row.split()
    num = int(re.findall("\d+",row)[0])
    try:
        last = row.strip().split("valves ")[1]
        last = [x.strip() for x in last.strip().split(",")]
        last = last
    except:
        last = row.strip().split("valve ")[1].strip()
        last = [last]
    D[first[1]] = last
    if num > 0:
        F[first[1]] = int(num)


# Get length of path to all vaults that has flow
# for each vault that has flow
def get_path(start):
    seen = set()
    q = []
    heappush(q,(0,start))
    paths = [] 
    added = set()
    while q:
        c, cur = heappop(q)
        if cur in seen:
            continue
        seen.add(cur)
        for child in D.get(cur):
            if child in F and child not in added:
                added.add(child)
                paths.append((child, c+1))
            heappush(q,(c+1, child))
    return paths


# Bureforce dijkstra style??
def solve(start):
    q = []
    # time,cnt,cur,seen
    heappush(q, (0,0,start,set()))
    winner = 0
    while q:
        time,cnt,cur,seen = heappop(q)
        # Should have tried all paths here first time we reach 31
        if time == 31:
            return winner 
        
        if cur in seen:
            continue
        
        ns = seen | set([cur])
        time += 1
        FLOW = cnt + F.get(cur,0)*(31-time)
        winner = max(winner,FLOW)
        for child,dist in GRAPH.get(cur):
            heappush(q,(time+dist, FLOW, child, ns)) 


GRAPH = {x : get_path(x) for x in F}
GRAPH["AA"] = get_path("AA")

print(solve("AA"))
# Bureforce dijkstra style??
def solve2(start):
    q = []
    # time,cnt,cur,seen
    heappush(q, (0,0,0,0,start,start,set()))
    winner = 0
    DP = set() 
    while q:
        tot_time, time,time2,cnt,cur,cur2,seen = heappop(q)
        # Should have tried all paths here first time we reach 31
        comp = tuple([*sorted([cur,cur2]),cnt])
        if comp in DP:
            continue
        DP.add(comp)
        # I really have no idea have to include some stopping condition
        # into this. The below line is not good enough
        if time >= 26 and time2 >= 26:
            continue
        
        # This is a common snenario
        if cur == cur2 != "AA":
            continue
        
        # Just stop here even tho this is a valid scenario, eventually there will come an iteration
        # which works checks this anyway
        if cur in seen or cur2 in seen:
            continue
        
        ns = seen.copy() | set([cur,cur2])

        time += 1
        time2 += 1
        
        # Only add to flow if we are in the time limi
        FLOW = cnt + F.get(cur,0)*(max(0,27-time)) + F.get(cur2,0)*(max(0,27-time2))
        winner = max(winner,FLOW)
        # Try all combinations for the current state
        for child,dist in GRAPH.get(cur):
            for child2,dist2 in GRAPH.get(cur2):
                heappush(q,(time+dist+time2+dist2,time+dist,time2+dist2,FLOW, child, child2, ns)) 
    # Until I find a proper stop condition winner has to be returned here :/
    return winner


GRAPH = {x : get_path(x) for x in F}
GRAPH["AA"] = get_path("AA")


print(solve2("AA"))
