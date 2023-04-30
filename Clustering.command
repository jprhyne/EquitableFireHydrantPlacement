model Clustering.mod;
data ./dataFiles/Clustering.dat;
option solver "./ampl_linux-intel64/cplex";
solve;
display {j in hydrants} : {i in houses} choose[i,j];
