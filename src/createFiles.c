/**
 *  This file write data for a particular formulation of sudoku
 *  to files of the form AMPL is expected
 */

#include "../include/createFiles.h"

/**
 * Function that creates the model file with path modelFile.
 * This formulation is the 3d array one, and while we can 
 * modify the values and generate below dynamically depending
 * on some kind of user input, really all that can change is going to 
 * the name of constraints and/or variable names. 
 */
void writeModelFile(char *modelFile)
{
    FILE *fp = fopen(modelFile,"w");

    // The following is going to be the same
    // For this given formulation
    fprintf(fp,
"\
set x := {1, 2, 3, 4, 5, 6, 7, 8, 9}; # x-coordinate inside our grid\n\
set y := {1, 2, 3, 4, 5, 6, 7, 8, 9}; # y-coordinate inside our grid\n\
set value := {1, 2, 3, 4, 5, 6, 7, 8, 9}; # value that is taken at coordinate (i,j)\n\
\n\
#3D variable representing our initial data\n\
param givenInfo {x,y,value} binary;\n\
# 3D variable where the value at grid[i,j,k] = 1 \n\
# if and only if the number k is present at the\n\
# coordinate (i,j) inside our 9x9 grid\n\
var grid {x,y,value} binary;\n\
# Sudoku doesn't require an objective function\n\
# So, we just add a function to let\n\
# AMPL run. This can be anything \n\
minimize dummyFunc: 0;\n\
\n\
# Constraint that ensures we only have 1 number\n\
# per column\n\
subject to onePerColumn {(j,k) in {y,value}}:\n\
	sum {i in x} grid[i,j,k] = 1;\n\
	\n\
# Constraint that ensures we only have 1 number\n\
# per row\n\
subject to onePerRow {(i,k) in {x,value}}:\n\
	sum {j in y} grid[i,j,k] = 1;\n\
\n\
# Set that helps with our onePerBox constraint\n\
set offset = {1, 4, 7};\n\
\n\
# Set that helps with our onePerBox constraint\n\
set boundaries = {0,1,2};\n\
\n\
# Constraint that ensures we only have 1 number\n\
# per 3x3 box\n\
subject to onePerBox {(i,j,k) in {offset, offset, value}}:\n\
	sum {(a,b) in {boundaries,boundaries}} grid[i + a, j + b, k] = 1;\n\
\n\
# Constraint that ensures we only have 1 number\n\
# per cell in our grid\n\
subject to onePerCell {(i,j) in {x, y}}:\n\
	sum {k in value} grid[i,j,k] = 1;\n\
\n\
# Constraint that ensures we don't violate the given data\n\
subject to startData {(i,j,k) in {x,y,value}}:\n\
	grid[i,j,k] >= givenInfo[i,j,k];\n");
    fclose(fp);
}

/** 
 * This function takes in a path to the data file to be written 
 * as well as a 9x9 grid of integers. This will be transformed into the 
 * form that we expect.
 *
 * @param dataFile path the file we want to write to
 * @param grid 9x9 grid of integers. It must take values between 0 and 9 inclusive
 *      if grid[i][j] is 0 then it interpreted as blank
 */
void writeDataFile(char *dataFile, int grid[9][9])
{
    // Create a file pointer and start our file
    FILE *fp = fopen(dataFile, "w");
    fprintf(fp,"data;\n\n");
    fprintf(fp, "for{(i,j,k) in {x,y,value}} {let givenInfo[i,j,k] := 0}");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != 0) {
                // This means we want to write out 
                // let grid[i,j,grid[i][j]] := 1;
                // Note: this is a bit of an abuse of notation
                fprintf(fp, "let givenInfo[%d,%d,%d] := 1;\n", i + 1,j + 1, grid[i][j]);
            }
        }
    }
    fprintf(fp,"end;");
    fclose(fp);
}

/**
 * This function creates a file stored at the path commandFile
 * This is a little unnecessary, but helps encapsulate the entire
 * process inside one programming language
 */
void writeCommandFile(char *dataFile, char *modelFile, char *solverPath, char *commandFile)
{
    FILE *fp = fopen(commandFile, "w");
    fprintf(fp, 
"\n\
model %s;\n\
data  %s;\n\
option solver \"%s\";\n\
solve;\n\
display {k in value}: {i in x, j in y} grid[i,j,k];",
            modelFile, dataFile, solverPath);
    // model fileName; loads the file as a model file
    // data fileName; loads the file as a data file
    // option solver path; defines the solver we want to use
    // solve; actually solves our program
    // display ...; This displays our grid sliced by values
    // So it will print out 9 9x9 grids. The kth grid will be a 
    // 2d binary array where each 1 determines where k goes inside the grid.
    fclose(fp);
}

int *readOutFile(char *outFile)
{
    FILE *fp = fopen(outFile,"r");
    int *grid = (int *) calloc(9 * 9, sizeof(int));

    int len = 256;
    char *line = (char *) calloc(256, sizeof(char));
    int counter = 0;
    int value = 1;

    //Read the file line by line. Note: this may only work on linux machines. Unsure about
    //other operating systems
    while (fgets(line, len, fp))
    {
        //Skip over the first 4 lines
        if (counter++ < 4) 
            continue;
        // Now, we need to check if we need
        // to parse this line or now
        // If the first character is g,:, or ;
        // then it contains no information we want to grab
        if (line[0] == 'g' || line[0] == ':' ||  line[0] == '\n')
            continue;
        if (line[0] == ';') {
            value++;
            continue;
        }
        // If it is not a skipping line,
        // then read it in in its entirety
        int row;
        int *nums = (int *) malloc(9 * sizeof(int));
        sscanf(line, "%d %d %d %d %d %d %d %d %d %d", &row, nums, nums + 1, nums + 2, nums + 3, nums + 4, nums + 5, nums + 6, nums + 7, nums + 8);
        // Yes the above is ugly, but it is a quickish way to read in our output
        for (int i = 0; i < 9; i++){
            if (nums[i] == 1) {
                grid[row - 1 + i * 9] = value;
                break;
            }
        }
        free(nums);

    }
    fclose(fp);
    return grid;
}
/*
int main()
{
    writeModelFile("sudoku.mod");
    int grid[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    }
    // Lazy way of initially making the grid
    // You could instead read in a bunch of files 
    // containing real sudoku grids
    // This will create a random "valid" starting state
    srand(time(NULL));
    grid[0][0] = rand()%10;
    grid[1][3] = rand()%10;
    grid[2][6] = rand()%10;
    grid[3][1] = rand()%10;
    grid[4][4] = rand()%10;
    grid[5][7] = rand()%10;
    grid[6][2] = rand()%10;
    grid[7][5] = rand()%10;
    grid[8][8] = rand()%10;

    writeDataFile("sudoku.dat", grid);
    writeCommandFile("sudoku.dat", "sudoku.mod", "./ampl_linux-intel64/cplex", "sudoku.command");
    
    runAMPL("./ampl_linux-intel64/ampl", "sudoku.command", "out.txt");
    int *finalGrid = readOutFile("out.txt");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", finalGrid[i + j * 9]);
        }
        printf("\n");
    }
    free(finalGrid);

}
*/
