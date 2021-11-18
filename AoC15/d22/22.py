def solve(bh, ph, pm, turn, dot, armor, mot, hard):
    ba = 10
    pm += 101 * (mot > 0)
    mot -= 1
    pd = 7 * (armor > 0)
    armor -= 1
    if hard and turn == "p":
        ph -= 1
    if dot > 0:
        bh -= 3
        dot -= 1
    if ph <= 0:
        return 10e10
    if bh <= 0:
        return 0
    if turn == "b":
        ph -= (ba - pd)
        if ph <= 0:
            return 10e10 
        return solve(bh, ph, pm, "p", dot, armor, mot, hard)
    else:
        res = 10e10 
        if pm < 53:
            return 10e10 
        if pm >= 53:
            res = min(res, 53 + solve(bh-4, ph, pm-53, "b", dot, armor, mot, hard))
        if pm >= 73:
            res = min(res, 73 + solve(bh-2, ph+2, pm-73, "b", dot, armor, mot, hard))
        if pm >= 113 and armor <= 0:
            res = min(res, 113 + solve(bh, ph, pm-113, "b", dot, 6, mot, hard))
        if pm >= 173 and dot <= 0:
            res = min(res, 173 + solve(bh, ph, pm-173, "b", 6, armor, mot, hard))
        if pm >= 229 and mot <= 0:
            res = min(res, 229 + solve(bh, ph, pm-229, "b", dot, armor, 5, hard))
        return res

print(solve(71, 50, 500, "p", 0, 0, 0, False))
print(solve(71, 50, 500, "p", 0, 0, 0, True))
