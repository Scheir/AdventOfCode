import re
def manhattan(x,y,xx,yy):
    return abs(x-xx)+abs(y-yy)
arr = []
BS = set()
for row in open("i1"):
    x,y,xx,yy = [int(x) for x in re.findall("-?\d+", row)]
    arr.append((x,y,xx,yy,manhattan(x,y,xx,yy)))
    BS.add((x,y))
    BS.add((xx,yy))

def no_beac(arr,X,Y):
    for x,y,xx,yy,dist in arr:
        to_point = manhattan(x,y,X,Y)
        if to_point <= dist and (X,Y) not in BS:
            return True
    return False


Y = 2000000
# Can we find an optimal search range?
print(sum(no_beac(arr,X,Y) for X in range(-10000000,10000000)))

## Part 2
MAX_XY = 4000000 


for x,y,xx,yy,dist in arr:
    #Iterate all posible coords for current sensor
    # Start with X = x + DIST+1 and Y = y  (one further than Beac for cur S)
    # Next iter is => X = x+DIST, Y = y+1
    # Ivestigate this (X,Y) In ALL directions so we move in a pattern as in the example picture
    for X in range(dist+2):
        Y = y+(dist+1-X)
        X = X+x 
        # All directions
        for NX,NY in ((X,Y),(-X,Y),(X,-Y),(-X,-Y)):
            if 0<=NX<=MAX_XY and 0<=NY<=MAX_XY:
                if not no_beac(arr,NX,NY) and not (NX,NY) in BS:
                    print(NX*MAX_XY+NY)
                    exit()
