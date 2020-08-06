filename = open("Mapping.txt","r")
lines = filename.readlines()
places = []
for i in range(0,len(lines),2):
    places.append(lines[i+1])
route = list(map(int,input().strip().split()))[:29]
for num in route:
    print(places[num])
