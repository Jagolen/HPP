CFLAGS= -O3 -fopenmp -Wall -g -ffast-math -march=native -faggressive-loop-optimizations 
INCLUDES=-I/opt/X11/include
LDFLAGS=-L/opt/X11/lib -lX11 -lm -fopenmp

C: galsim.o graphics.o
	gcc -g -o galsim  galsim.o graphics.o $(LDFLAGS)

galsim.o: galsim.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c galsim.c 

	
graphics.o: graphics.c graphics.h
	gcc $(CFLAGS) $(INCLUDES) -c graphics.c

clean:
	rm -f ./galsim *.o

