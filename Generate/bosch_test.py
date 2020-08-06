import googlemaps 
import geopy.distance
import numpy as np
gmaps = googlemaps.Client(key='AIzaSyDDLOnUQz1by3JV-6F84iDPR6A4DS4LsqM') 

def direct_distance(pt1, pt2):
  return geopy.distance.vincenty(pt1, pt2)

def sample_point(centre, radius):
  while True:
    lat = np.random.uniform(centre[0]-1, centre[0]+1)
    lng = np.random.uniform(centre[1]-1, centre[1]+1)
    if direct_distance(centre, (lat, lng)) < radius:
      return (lat, lng)

office_address = 'Bosch bidadi'
office_geocode = gmaps.geocode(office_address)[0]['geometry']['location']
office_coordinates = (office_geocode['lat'], office_geocode['lng'])
# print(office_coordinates)

radius = 30 # Max distance of pickup point from office (in kms)
n = 5 # Number of distinct pickup points
k = 3 # Max number of people at a pickup point

locations = []
people_count = []
pickup = {}
pickup_points = int(input())  #number of people picked up

for _ in range(pickup_points):
    s = input()
    if (s in pickup) == False:
        pickup[s]=1
    else:
        pickup[s]+=1
for location in pickup:
    coords = gmaps.geocode(location)[0]['geometry']['location']
    locations.append((coords['lat'],coords['lng']))
    people_count.append(pickup[location])
n=len(locations)
# for _ in range(n):
#   location = sample_point(office_coordinates, radius)
#   locations.append(location)
#   people_count.append(np.random.randint(k+1))
  # people_count.append(k)
filename = open("Mapping.txt","w")
count = 0
i = 0
for location in pickup:
  for j in range(people_count[i]):
    filename.write(str(count)+" "+str(locations[i][0])+" "+str(locations[i][1])+" "+location+"\n")
    count+=1
  i+=1
exit(0)
# print(locations)
# print(people_count)
gmaps_distance_matrix = []
for location in locations:
  temp = []
  arr = gmaps.distance_matrix([location], locations)
  for i in range(n):
    temp.append(arr['rows'][0]['elements'][i]['distance']['value'])
  gmaps_distance_matrix.append(temp)
#print(gmaps_distance_matrix)

m = sum(people_count)
distance_matrix = np.zeros(shape=(m, m), dtype=int)

# for i in range(n):
#   for j in range(n):
#     print(gmaps_distance_matrix['rows'][i]['elements'][j]['distance']['value']) 

i1 = 0
for i2 in range(n):
  j1 = 0
  for j2 in range(n):
    for i3 in range(i1, i1+people_count[i2]):
      for j3 in range(j1, j1+people_count[j2]):
        distance_matrix[i3][j3] = gmaps_distance_matrix[i2][j2]
    j1 += people_count[j2]
  i1 += people_count[i2]

# print(distance_matrix)

for i in range(m):
  for j in range(m):
    print(distance_matrix[i][j], end =" ")
  print('')

gmaps_distance_to_office = gmaps.distance_matrix(locations, [office_coordinates])
# print(gmaps_distance_to_office)
distance_to_office = np.zeros(shape=(m), dtype=int)

ind = 0
for i in range(n):
  for j in range(ind, ind+people_count[i]):
    distance_to_office[j] = gmaps_distance_to_office['rows'][i]['elements'][0]['distance']['value']
  ind += people_count[i]

# print(distance_to_office)

for i in range(m):
  print(distance_to_office[i], end =" ")
