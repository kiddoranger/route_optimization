import googlemaps
import numpy as np
import gmplot 
gmaps = googlemaps.Client(key='AIzaSyDDLOnUQz1by3JV-6F84iDPR6A4DS4LsqM')
end_point=[12.7971706, 77.4238823]
f=open("Mapping.txt",'r')
gmap = gmplot.GoogleMapPlotter(12.7971706, 77.4238823, 11.5) # Bosch bidadi office
gmap.apikey = "AIzaSyDDLOnUQz1by3JV-6F84iDPR6A4DS4LsqM"
coord_map={}

for lines in f.readlines():
    x=lines.split()
    coord=[float(x[1]),float(x[2])]
    index=int(x[0])
    coord_map[index]=coord

path=open("route.txt",'r')
num_buses=int(path.readline().split()[0])
for i in range(0,num_buses):
    cap=int(path.readline().split()[0])
    route=np.array(path.readline().split(),dtype=int)
    points = []
    for j in route:
        points.append(coord_map[j])
    points.append(end_point)
    roads = gmaps.snap_to_roads(points,interpolate=True)
    latitude_list=[]
    long_list=[]
    for j in range(len(roads)):
        latitude_list.append(roads[j]['location']['latitude'])
        long_list.append(roads[j]['location']['longitude'])
    gmap.scatter(latitude_list, long_list, '#FF0000', size = 40, marker = False) 
    gmap.plot(latitude_list, long_list, 'cornflowerblue', edge_width = 2.5)
gmap.draw("my_map_snapped.html")