from copy import deepcopy
a,b = open("i1").read().split("\n\n")

a = a.strip()

pixels_on = set()

for i,r in enumerate(b.strip().split("\n")):
    for j,val in enumerate(r.strip()):
        if val == "#":
            pixels_on.add((i,j))


for _ in range(50):
    pix_on_new = set()
    rl,rh,cl,ch = 100000,0,100000,0
    for i,j in pixels_on:
        rl = min(rl,i)
        rh = max(rh,i)
        cl = min(cl,j)
        ch = max(ch,j)

    for r in range(rl-2, rh+2):
        for c in range(cl-2,rh+2):
            b = ""
            for dx in [-1,0,1]:
                for dy in [-1,0,1]:
                # MEEEEH the first and last bit of the transform string
                # messes things up a bit. Need to alternate to check for
                # lit and non lit 
                    if _%2 == 0:
                        b += '1' if (r+dx,c+dy) in pixels_on else '0'
                    else:
                        b += '1' if (r+dx,c+dy) not in pixels_on else '0'
            binval = int(b,2)
            if _ % 2 == 0:
                if a[binval] != "#":
                    pix_on_new.add((r,c))
            else:
                if a[binval] == "#":
                    pix_on_new.add((r,c))

    pixels_on = pix_on_new
    if _ == 1:
        print(len(pixels_on))
print(len(pixels_on))
            
