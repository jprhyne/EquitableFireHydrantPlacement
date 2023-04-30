param numHydrant integer >= 0;
param numHouses integer >= 0;
set hydrants := 1..numHydrant;
set houses := 1..numHouses;
param distances{houses,hydrants} >= 0;

# Determines if we have a particular house i to a hydrant j
var choose {houses,hydrants} >= 0;
var cost{hydrants} >= 0; # Exists due to a hacky way of me creating data files

minimize distanceFunc: sum {i in houses, j in hydrants} distances[i,j] * choose[i,j];

subject to one_hydrant_per_house {i in houses}:
	sum {j in hydrants} choose[i,j] = 1;
	
