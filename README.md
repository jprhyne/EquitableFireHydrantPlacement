# EquitableFireHydrantPlacement
Repository for my source code for the 2023 D2P through Auraria Library

# Compilation Instructions
First, you need to install ampl into this directory. Due to potential licensing issues, I did not include it here,
however you can download the community edition from https://ampl.com/ce/

Depending on the file name, you may need to also change the file path inside runClustering.sh, runLocation.sh, and their respective command files.

1. ```make```
2. Open "parsing.ipynb" inside jupyter notebooks (Or run the parsing.py file. Some of the figures won't display this way, but it will save all the ones saved)
3. Enjoy!

# Potential Things to Investigate
* Change the penalty inside Location.mod
* Change max number of houses per hydrant in Location.mod
    * This is VERY memory intensive, and can make the program take a LONG time to terminate depending on your hardware
