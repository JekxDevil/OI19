ncities,nareas = map(int,input().split())
cities = []
for i in range(ncities):
    l = input().split()
    name = l[0]
    x,y = int(l[1]), int(l[2])
    cities.append({"name":name,"x":x,"y":y})
def getArea(a,b,c):
    area = ((b["x"]-a["x"])*(c["y"]-a["y"])-(c["x"]-a["x"])*(b["y"]-a["y"]))/2.0;
    return area if area>0.0 else -area
areas = [0]*ncities
for i in range(nareas):
    a,b,c = map(int,input().split())
    a-=1
    b-=1
    c-=1
    area = getArea(cities[a],cities[b],cities[c])
    areas[a]+=area
    areas[b]+=area
    areas[c]+=area

best_cities = []
maxarea = -10000
for i,area in enumerate(areas):
    if area>maxarea:
        maxarea = area
        best_cities = [cities[i]["name"]]
    elif area==maxarea:
        best_cities.append(cities[i]["name"])
best_cities.sort()
for x in best_cities: print(x)
