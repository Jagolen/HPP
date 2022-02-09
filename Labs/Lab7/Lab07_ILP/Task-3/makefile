CC = gcc
LD = gcc
CFLAGS = -O3 -Wall
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o stencil.o
EXECUTABLE = stencil_test

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

stencil.o: stencil.h stencil.c
	$(CC) $(CFLAGS) -c stencil.c

main.o: main.c stencil.h
	$(CC) $(CFLAGS) -c main.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
