param numHydrant integer >= 0;
param numHouses integer >= 0;
set hydrants := 1..numHydrant;
set houses := 1..numHouses;
param distances{houses,hydrants} >= 0;
param cost{hydrants} >= 0;

# Determines if we have a particular house i to a hydrant j
var choose {houses,hydrants} >= 0;
# Determines if we use a particular hydrant
var makeHydrant {hydrants} binary;

minimize distanceFunc: sum {i in houses, j in hydrants} distances[i,j] * choose[i,j] + sum {j in hydrants} 10000 * makeHydrant[j] * cost[j];

subject to one_hydrant_per_house {i in houses}:
	sum {j in hydrants} choose[i,j] = 1;

subject to needMadeFirst { i in houses, j in hydrants }:
	choose[i,j] <= makeHydrant[j];

#subject to maxPerHydrant { j in hydrants }:
#	sum { i in houses } choose[i,j] <= 200
