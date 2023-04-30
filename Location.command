model Location.mod;
data ./dataFiles/Location.dat;
option solver "./ampl_linux-intel64/cplex";
solve;
display {j in hydrants} : {i in houses} choose[i,j];
display {j in hydrants} : makeHydrant[j];
