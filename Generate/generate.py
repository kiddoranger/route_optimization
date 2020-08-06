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

for _ in range(n):
  location = sample_point(office_coordinates, radius)
  locations.append(location)
  people_count.append(np.random.randint(k+1))
  # people_count.append(k)

# print(locations)
# print(people_count)

gmaps_distance_matrix = gmaps.distance_matrix(locations, locations)
# print(gmaps_distance_matrix)

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
        distance_matrix[i3][j3] = gmaps_distance_matrix['rows'][i2]['elements'][j2]['distance']['value']
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