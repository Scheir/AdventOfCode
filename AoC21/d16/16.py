from collections import *
from itertools import *
from functools import *
import re

# Parse the hexas in the input and transform the string to binary
string = list(open("i1").read().strip())
string = ['{0:b}'.format(int(x,16)).zfill(4) for x in string]
string = ''.join(string)

res = 0
def parse(string, idx):
    global res
    assert idx < len(string)
    ver = int(string[idx:idx+3],2)
    res += ver
    t = int(string[idx+3:idx+6],2)
    if t == 4:
        idx += 6
        v = 0
        while True:
            # for each iteration we have one val in hexa base 16
            v = v*16 + int(string[idx+1:idx+5],2)
            stop = string[idx] == '0'
            idx += 5
            if stop:
                return idx,v
    else:
        #We have an operator packet. They contain more packets inside
        #Will recurse and eventually end up in literal
        #For each operator packet we will store the values 
        #produced by the sub packets in an array
        #We either have a for loop operator packet or a for loop iterator
        #packet. 
        idx += 6
        ID = int(string[idx],2)
        idx += 1
        # Iterate each subpacket and store the result in values
        values = []
        #ID 0 is a while loop operator packet. Loop until we reach packet
        #lenght, which is represented by the next 15 bits
        if ID == 0:
            ID_LEN = 15
            packet_len = int(string[idx:idx+ID_LEN],2)
            idx += ID_LEN 
            before_idx = idx
            while True:
                idx,val = parse(string,idx)
                values.append(val)
                if idx - before_idx == packet_len:
                    break
        #ID 1 is a for loop operator packet. Iterate for a number
        # of times, given by the next three 11 bits
        else:
            ID_LEN = 11
            packets = int(string[idx:idx+ID_LEN],2)
            idx += ID_LEN 
            for _ in range(packets):
                idx,val = parse(string,idx)
                values.append(val)
                assert type(idx) == int

    # Do the correct operation on package type
    # Literal (type = 4) is handled above
    v = 0
    if t == 0:
        v = sum(values)
    elif t == 1:
        v = reduce(lambda x,y: x*y,values)
    elif t == 2:
        v = min(values)
    elif t == 3:
        v = max(values)
    elif t == 5:
        v = 1 if values[0] > values[1] else 0
    elif t == 6:
        v = 1 if values[0] < values[1] else 0
    elif t == 7:
        v = 1 if values[0] == values[1] else 0
    else:
        assert False, f'type is wrong: {t}'

    return idx, v

_, v = parse(string, 0)
print(res)
print(v)

