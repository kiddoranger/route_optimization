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
colours = ['green','blue','orange','brown','red','gray','purple']
for i in range(0,num_buses):
    cap=int(path.readline().split()[0])
    route=np.array(path.readline().split(),dtype=int)
    points = []
    for j in route:
        points.append(coord_map[j])
    points.append(end_point)
    # print(len(points))
    latitude_list1 = []
    long_list1 = []
    for x,y in points:
        latitude_list1.append(x)
        long_list1.append(y)
    for k in range(len(points)-1):
        dirs = gmaps.directions(points[k],points[k+1])
        latitude_list=[]
        long_list=[]
        # for key in dirs[0]['legs'][0]['steps'][0]:
        #     print(key)
        # print(len(dirs[0]['legs'][0]['steps']))
        print(len(dirs))
        for j in dirs[0]['legs'][0]['steps']:
            latitude_list.append(j['start_location']['lat'])
            latitude_list.append(j['end_location']['lat'])
            long_list.append(j['start_location']['lng'])
            long_list.append(j['end_location']['lng'])
        gmap.plot(latitude_list, long_list, colours[i], edge_width = 2.5)
    gmap.scatter(latitude_list1, long_list1, colours[i], size = 40, marker = True) 
gmap.draw("my_map_directions.html")