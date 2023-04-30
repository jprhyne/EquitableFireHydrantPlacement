#include <time.h>
#include <string.h>
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
        char *a = "dataFiles/housesSection1.txt";
        char *b = "dataFiles/hydrantsSection1.txt";
        char *c = "dataFiles/Clustering.dat";
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
    time_t start = time(0);
    writeDataFile(houses, numHouse, hydrants, numHydrant, outputPath, numExisting);
    time_t stop = time(0);

    printf("Time to execute: %d seconds\n", stop - start);
    free(houses);
    free(hydrants);
    free(housePath);
    free(hydrantPath);
    free(outputPath);
}
