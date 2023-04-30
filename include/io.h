#ifndef IO
#define IO
#include "coordinate.h"
#include "distances.h"
#include <stdio.h>
#include <stdlib.h>
Coordinate *readFile(char *fileName, int *length, int *numZero);
void writeHouses(Coordinate *houses, int numHouses, char *fileName);
void writeDataFile(Coordinate *houses, int numHouses, Coordinate *hydrants, int numHydrants, char *fileName, int numExisting);
#endif
