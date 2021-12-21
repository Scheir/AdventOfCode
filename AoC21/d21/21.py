def rolls():
    dice = [1,2,3]
    return [i+j+k for i in dice for j in dice for k in dice]

def DP(p1,p2,sp1,sp2,memoiz):
    p1c,p2c,sp1c,sp2c = p1,p2,sp1,sp2
    res = [0,0]
    #P1 wins
    if sp1 >= 21:
        return [1,0]
    #P2 wins
    if sp2 >= 21: 
        return [0,1]
    #Seen this state before, return result from the state
    if (p1,p2,sp1,sp2) in memoiz:
        return memoiz[(p1,p2,sp1,sp2)]
    # Roll three times with all outcomes
    # Recurse where rolls are added to p1
    # and p2 is first (p1) in next iteration
    for cur_roll in rolls():
        p1 = p1c+cur_roll
        assert p1 <= 20
        p1 = p1 if p1 <= 10 else p1-10
        sp1 = sp1c+p1 
        # Next round player two is player one and p1 is p2
        # we will keep going until we hit scores of atleast 21
        # or a state we have seen before.
        scores = DP(p2,p1,sp2,sp1,memoize)
        ## Since we are alternating p1 and p2 the result
        ## of next is also alternated
        ## if we dont do this all scores end up in p1
        res = [scores[1]+res[0], scores[0]+res[1]]
    memoiz[p1c,p2c,sp1c,sp2c] = res 
    return res 

#Part ONe
# My inputs
p1 = 7
p2 = 9
scores = [0,0]
turns = 0
b = True
die = 1
while scores[0] < 1000 and scores[1]<1000:
    for i in range(3): 
        turns += 1
        for j in range(die):
            if b and scores[0] < 1000:
                p1 = p1 + 1 if p1 < 10 else 1
            elif not b and scores[1] < 1000:
                p2 = p2 + 1 if p2 < 10 else 1
        die += 1
    if b == True:
        scores[0] += p1
    else:
        scores[1] += p2
    b = not b 
print(turns * min(scores))

# Part Two
# The idea here is to save (memoization) the winner from each state
# if we do this we can simply reuse the outcome of that state
# (dynamic programming).

# First time we finnish and store a values to memoiz we will hit sp1 or sp2
# for each next recursive iteration, so we will get either [27,0] or [0,27]
# then we are ready to reuse that state and so and so on

memoiz = {}
print(DP(7,9,0,0,memoize))

print(max(max(*memoiz.values())))
