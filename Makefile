all: cleaning makeDistances

io.o: src/io.c include/io.h include/coordinate.h
	gcc src/io.c -c

distances.o: src/distances.c include/distances.h include/coordinate.h
	gcc src/distances.c -c

cleaning.o: src/cleaning.c include/io.h include/distances.h include/coordinate.h
	gcc src/cleaning.c -c

cleaning: cleaning.o io.o distances.o
	gcc cleaning.o io.o distances.o -lm -o cleaning

makeDistances.o: src/makeDistances.c include/io.h include/distances.h include/coordinate.h
	gcc src/makeDistances.c -c

makeDistances: makeDistances.o distances.o io.o 
	gcc makeDistances.o distances.o io.o -lm -o makeDistances

clean:
	rm cleaning makeDistances *.o
