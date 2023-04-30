#include <string.h>
#include <time.h>
#include "../include/coordinate.h"
#include "../include/distances.h"
#include "../include/io.h"

void main(int argc, char *argv[])
{
    char *housePath = (char *) calloc(1001, sizeof(char));
    char *hydrantPath = (char *) calloc(1001, sizeof(char));
    char *outputPath = (char *) calloc(1001, sizeof(char));
    if (argc == 4) {
        int houseLen = strlen(argv[1]);
        int hydrantLen = strlen(argv[2]);
        int outputLen = strlen(argv[3]);
        if ( houseLen > 1000 )
            housePath = realloc(housePath, houseLen + 1);
        if ( hydrantLen > 1000 )
            hydrantPath = realloc(hydrantPath, hydrantLen + 1);
        if ( outputLen > 1000 )
            outputPath = realloc(outputPath, outputLen + 1);
        for (int i = 0; i < houseLen; i++)
            housePath[i] = argv[1][i];
        for (int i = 0; i < hydrantLen; i++)
            hydrantPath[i] = argv[2][i];
        for (int i = 0; i < outputLen; i++)
            outputPath[i] = argv[3][i];
    } else {
        char *a = "dataFiles/house.txt";
        char *b = "dataFiles/hydrant.txt";
        char *c = "dataFiles/housesKept.txt";
        for (int i = 0; i < strlen(a); i++)
            housePath[i] = a[i];
        for (int i = 0; i < strlen(b); i++)
            hydrantPath[i] = b[i];
        for (int i = 0; i < strlen(c); i++)
            outputPath[i] = c[i];
    }
    int numHouse = -1;
    int numHydrant = -1;
    int numExisting = -1;
    Coordinate *houses = readFile(housePath, &numHouse, &numExisting);
    Coordinate *hydrants = readFile(hydrantPath, &numHydrant, &numExisting);
    int *retainIndex = calloc(numHouse, sizeof(int));
    int lastKept = 0;
    time_t start = time(0);
/*
Cleaning our data to remove buildings that are further than 600 feet away from the closest fire hydrant.
This number comes from the fact that the 2019 denver fire code requires a maximum of 600 feet from a building
and the closest hydrant.
Source: https://test.denvergov.org/Government/Agencies-Departments-Offices/Agencies-Departments-Offices-Directory/Community-Planning-and-Development/Building-Codes-Policies-and-Guides
*/
    for (int i = 0; i < numHouse; i++) {
        double minDistance = distanceInM(houses[i], hydrants[0]);
        for(int j = 1; j < numHydrant; j++) {
            double tmp = distanceInM(houses[i], hydrants[j]);
            if (tmp < minDistance)
                minDistance = tmp;
            if (minDistance < CUTOFF) {
                retainIndex[lastKept++] = i;
                printf("Keeping Index: %d\nWith distance: %lf\n", i, minDistance);
                break;
            }
        }
        if (i % 1000 == 0) 
            printf("Processed house: %d\nWith minDistance: %lf\n", i, minDistance);
    }
    time_t stop = time(0);

    //printf("Kept %d houses", lastKept);

    // Now, we only print out he latitudes and longitudes of the houses we are keeping
    Coordinate *keptList = calloc(lastKept, sizeof(Coordinate));
    for (int i = 0; i < lastKept; i++) {
        keptList[i] = houses[retainIndex[i]];
    }

    writeHouses(keptList, lastKept, outputPath);

    printf("Time to execute: %d seconds", stop - start);
    
    free(keptList);
    free(houses);
    free(hydrants);
    free(retainIndex);
    free(housePath);
    free(hydrantPath);
    free(outputPath);
}
