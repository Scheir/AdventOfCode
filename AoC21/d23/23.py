from collections import *
from itertools import *
from functools import *
from copy import deepcopy
import re

#############
#...........#
###A#D#C#A###
  #D#C#B#A#
  #D#B#A#C#
  #C#D#B#B#
  #########

# Where in top cols are
COL_INDEX = {0:2,1:4,2:6,3:8}

#Map letters to their final col
LET_TO_COL = {'A':0,'B':1,'C':2,'D':3} 

# Valid top indices
VALID_TOP = (0,1,3,5,7,9,10)

# COST # 
COST = {'A':1,'B':10,'C':100,'D':1000}

# START #
S1 = ['A','D','D','C']
S2 = ['D','C','B','D']
S3 = ['C','B','A','B']
S4 = ['A','A','C','B']

# GOAL #
G1 = ['a','a','a','a']
G2 = ['b','b','b','b']
G3 = ['c','c','c','c']
G4 = ['d','d','d','d']

# Top #
T = ['.']*11

# Start state #
start_state = ({0:S1,1:S2,2:S3,3:S4},T)
done_state = [G1,G2,G3,G4]

# Print exactly as it looks in the task to 
# better understand what the hell is going on
def print_state(state):
    cols,top = state
    print(" #############")
    print(" #"+ ''.join(top)+"#")
    vec = list(map(list,zip(*cols.values())))
    for x in vec:
        print("   #"+'#'.join(x)+"#  ")

# Check if we reached final state
def completed(state):
    cols, top = state
    a,b,c,d = cols.values()
    if a == G1 and b == G2 and c == G3 and d == G4 and top == T:
        return True
    return False

# Check if an item is movable in the colums.
# If it is a small letter it is not movable
# as it reached the final state
# If it is locked between two chars
# it is not movable either
def movable(state,c,idx):
    col,top = state
    #print("MOVABLE",c,idx,top,col[c][idx])
    if col[c][idx].islower() or col[c][idx] == '.':
        return False
    for i,v in enumerate(col[c]):
        if i == idx:
            break
        if v != '.':
            return False
    return True

# Check if a character can be moved from
# colum to selected top index
def valid_move_from_col(state,c,top_idx):
    cols,top = state
    if COL_INDEX[c] < top_idx:
        for i in range(COL_INDEX[c], top_idx+1):
            if top[i] != '.':
                return False
    else:
        for i in range(top_idx, COL_INDEX[c]+1):
            if top[i] != '.':
                return False
    return True

#Check if a character can be moved from top index
# to a column to reach its final position 
def valid_move_from_top(state,c,cur_top_idx):
    cols,top = state
    if cur_top_idx < COL_INDEX[c]:
        for i in range(cur_top_idx+1, COL_INDEX[c]+1):
            if top[i] != '.':
                return -1,False
    else:
        for i in range(COL_INDEX[c], cur_top_idx):
            if top[i] != '.':
                return -1, False
    char_to_move = top[cur_top_idx]
    if char_to_move not in done_state[c][0].upper():
        return -1,False
    for i in range(3,-1,-1):
        if cols[c][i] == '.':
            return i,True
        if cols[c][i] not in done_state[c][0]:
            return -1, False

assert(movable(start_state,1,2)) == False
assert(movable(start_state,1,0)) == True
assert(valid_move_from_col(start_state,2,5)) == True

#global res var
res = 10e10 

# Solve the problem recursively, always try to 
# move characters from top to their final position 
# before moving stuff from columns to top.

# Try all possible solutions, calculate the cost
# and stop the current iteration if we allready found 
# a cheaper solution.

# It is running for a long time (45+ sec),
# probably need to add some memoization here
# Feels very brute forceish right now
def solve(state,cost):
    global res

    #print("--------------------")
    #print_state(state)

    # Start by checking if we are done or if we
    # Update result if necessary
    if completed(state):
        res = min(cost,res)
        return 
    # No point in continuing if this is true
    if cost > res:
        return 
    cols, top = state
    #Try to move anything frop top to cols
    for i, v in enumerate(top):
        if v == '.':
            continue
        move_to_idx = LET_TO_COL[v]
        ret, ok = valid_move_from_top(state,move_to_idx,i)
        if ok:
            # if we manage to move, assing new values, copy the cols and top
            # to pass a new dict to the next recursive iteration
            top[i] = '.'
            cols[LET_TO_COL[v]][ret] = v.lower()
            nc = deepcopy(cols)
            nt = top.copy()
            # Cost is the distance * character cost
            ncost = cost + COST[v]*(abs(i-COL_INDEX[move_to_idx])+ret+1)
            return solve((nc,nt),ncost)
    
    # Move anything that is movable from columns
    # to top and recurse, very brute forceish
    for i, v in cols.items():
        if cost > res:
            return
        c_idx = COL_INDEX[i]
        #Check from top to bottom in a col if the character
        # is movable or not
        for j in range(0,4):
            if not movable(state,i,j):
                continue
            # If it is movable,
            # Try to move it to every possible location in top
            # if it is valid, move it and recurse
            for top_idx in range(11):
                if top_idx not in VALID_TOP:
                    continue
                if not valid_move_from_col(state,i,top_idx):
                    continue
                nc = deepcopy(cols)
                nt = top.copy()
                nc[i][j] = '.'
                nt[top_idx] = v[j]
                ncost = cost + COST[v[j]]*(j+abs(c_idx-top_idx)+1) 
                solve((nc,nt),ncost)
                 
print("PART ONE SOLVED BY HAND ;)")
solve(start_state,0)
print(res)
