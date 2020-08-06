import gmplot 
import googlemaps
import numpy as np
gmaps = googlemaps.Client(key='AIzaSyDDLOnUQz1by3JV-6F84iDPR6A4DS4LsqM') 

gmap = gmplot.GoogleMapPlotter(12.7971706, 77.4238823, 11.5) # Bosch bidadi office
gmap.apikey = "AIzaSyDDLOnUQz1by3JV-6F84iDPR6A4DS4LsqM"
end_point=[12.7971706, 77.4238823]
f=open("../Mapping.txt",'r')

coord_map={}

for lines in f.readlines():
    x=lines.split()
    coord=[float(x[1]),float(x[2])]
    index=int(x[0])
    coord_map[index]=coord

path=open("../route.txt",'r')
num_buses=int(path.readline().split()[0])
for i in range(0,num_buses):
    cap=int(path.readline().split()[0])
    route=np.array(path.readline().split(),dtype=int)
    latitude_list=[]
    long_list=[]
    for j in route:
        latitude_list.append(coord_map[j][0])
        long_list.append(coord_map[j][1])
    arr=[(latitude_list[i],long_list[i]) for i in range(1,len(long_list)-1)]
    gdir=gmaps.directions((latitude_list[0],long_list[0]),(latitude_list[-1],long_list[-1]),waypoints=arr)
    print(gdir[0]["legs"])
    latitude_list.append(end_point[0])
    long_list.append(end_point[1])
    gmap.scatter(latitude_list, long_list, '#FF0000', size = 40, marker = False) 
    gmap.plot(latitude_list, long_list, 'cornflowerblue', edge_width = 2.5) 

gmap.draw("my_map.html")