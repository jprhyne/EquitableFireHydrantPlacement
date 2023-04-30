#include "../include/runner.h"

void usage()
{
    fprintf(stderr, "Usage: runner [--preGen | --create]");
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        usage();
    if (strcmp("--preGen", argv[1]) == 0){
        runAMPL("../ampl_linux-intel64/ampl", "sudoku.command","output.txt");
        int *finalGrid = readOutFile("output.txt");
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0)
                printf("----------------------\n");
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0)
                    printf("|");
                printf("%d ", finalGrid[i + j * 9]);
            }
            printf("|\n");
        }
        printf("----------------------\n");
        free(finalGrid);
    } else {
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
        
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0)
                printf("----------------------\n");
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0)
                    printf("|");
                printf("%d ", grid[i][j]);
            }
            printf("|\n");
        }
        printf("----------------------\n");
    
        writeDataFile("sudoku.dat", grid);
        writeCommandFile("sudoku.dat", "sudoku.mod", "./ampl_linux-intel64/cplex", "sudoku.command");
        
        runAMPL("./ampl_linux-intel64/ampl", "sudoku.command", "out.txt");
        int *finalGrid = readOutFile("out.txt");
        for (int i = 0; i < 9; i++) {
            if (i % 3 == 0)
                printf("----------------------\n");
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0)
                    printf("|");
                printf("%d ", finalGrid[i + j * 9]);
            }
            printf("|\n");
        }
        printf("----------------------\n");
        free(finalGrid);
    }
}
