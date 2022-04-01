from random import randint
from heapq import heappush, heappop
k = 4
m = 4
n = 2

att = 0
dif = 0
for _ in range(1000000):
    att_vals = []
    for i in range(m):
        heappush(att_vals, randint(1,k))
        if i>n: heappop(att_vals)
    dif_vals = []
    for i in range(n):
        heappush(dif_vals, randint(1,k))
    for i in range(n):
        if att_vals>dif_vals:
            att+=1
        else:
            dif+=1

print(att/1000000)
print(dif/1000000)
