/**
 * This file demonstrates two ways to call AMPL from inside C
 *
 * The first way will require us to have the files already made for AMPL. 
 * 
 * The second is to create the files from inside C
 */
#include "../include/runFiles.h"

void runAMPL(char *amplPath, char *amplInputFile, char *outFile)
{
    // Poor practice, but demonstrates what we need to be done
    int amplPathLen = strlen(amplPath);
    int amplInputLen = strlen(amplInputFile);
    int outFileLen = strlen(outFile);
    // Build a string to contain our command to pass to the system method
    int commandLength = amplPathLen + amplInputLen + outFileLen + 10; 
    char *command = (char *) calloc((commandLength + 1) , sizeof(char));
    for (int i = 0; i < amplPathLen; i++) {
        command[i] = amplPath[i];
    }
    command[amplPathLen] = ' ';
    command[amplPathLen + 1] = '<';
    command[amplPathLen + 2] = ' ';
    for (int i = 0; i < amplInputLen; i++) {
        command[i + amplPathLen + 3] = amplInputFile[i];
    }
    command[amplPathLen + amplInputLen + 3] = ' ';
    command[amplPathLen + amplInputLen + 4] = '>';
    command[amplPathLen + amplInputLen + 5] = ' ';
    for (int i = 0 ; i < outFileLen; i++) {
        command[i + amplPathLen + amplInputLen + 6] = outFile[i];
    }
    // Now, we run the command
    system(command);
    free(command);
}

void runAMPL_default(char *amplPath, char *amplInputFile)
{
    runAMPL(amplPath, amplInputFile, "output.txt");
}

/**
 * Used For debugging the above functions
 */
/*
int main(int argc, char *argv[])
{
    runAMPL_default(argv[1], argv[2]);
}
*/
