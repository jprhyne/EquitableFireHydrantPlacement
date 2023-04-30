#include "../include/io.h"
Coordinate *readFile(char *fileName, int *length, int *numZero)
{
    FILE *fp = fopen(fileName,"r");
    int cap = 650000;
    int numCoordinates = 0;
    Coordinate *list = (Coordinate *) calloc(cap, sizeof(Coordinate));
    int len = 100;
    int counter = 0;
    char *line = (char *) calloc(len,  sizeof(char));
    // First line tells us the number of hydrants already placed
    fgets(line,100,fp);
    sscanf(line, "%d", numZero);
    while (fgets(line, 100, fp)) {
        if (counter++ < 1)
            continue;
        // Now, we parse this line as lat, lon
        double lat = 0;
        double lon = 0;
        sscanf(line, "%lf %lf", &lat, &lon);
        //printf("%lf, %lf\n", lat, lon);
        Coordinate tmp;
        tmp.lat = lat;
        tmp.lon = lon;
        if (numCoordinates >= cap) {
            cap *= 100;
            list = realloc(list, cap);
        }
        list[numCoordinates++] = tmp;
    }
    fclose(fp);
    *length = numCoordinates;
    return list;
}

void writeHouses(Coordinate *houses, int numHouses, char *fileName)
{
    FILE *fp = fopen(fileName, "w");
    fprintf(fp, "Latitude Longitude\n");
    for (int i = 0; i < numHouses; i++) {
        fprintf(fp, "%lf %lf\n", houses[i].lat, houses[i].lon);
    }
    fclose(fp);
}

void writeDataFile(Coordinate *houses, int numHouses, Coordinate *hydrants, int numHydrants, char *fileName, int numExisting)
{
    FILE *fp = fopen(fileName, "w");
    fprintf(fp, "data;\n");
    fprintf(fp, "let numHydrant := %d;\nlet numHouses := %d;\n", numHydrants, numHouses);

    for (int i = 0; i < numHouses; i++) {
        if (i % 1000 == 0) 
            printf("Processing house %d\n", i);
        for (int j = 0; j < numHydrants; j++) {
            double distance = distanceInM(houses[i], hydrants[j]);
            // Only print out if the house is 1.2 KM or less away from the hydrant. 
            // This is roughly 3937 feet. Much more than is reasonable to expect for 
            // fire trucks to have access to during an emergency
            //if (distance < CUTOFF)
                fprintf(fp, "let distances[%d, %d] := %lf;\n", i + 1, j + 1, distance);
            //else
                //fprintf(fp, "let distances[%d, %d] := %lf;\n", i + 1, j + 1, 999999.0);
        }
    }
    if (numHydrants != numExisting) {
        for (int i = 0;i < numHydrants; i++) {
            if (i < numExisting) {
                fprintf(fp, "let cost[%d] := %d;\n", i + 1, 0);
            } else {
                fprintf(fp, "let cost[%d] := %d;\n", i + 1, 1);
            }
        }
    }
    fprintf(fp, "end;\n");
    fclose(fp);
}
