CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -funroll-loops
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o testfuncs.o
EXECUTABLE = branch_test

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

testfuncs.o: testfuncs.h testfuncs.c
	$(CC) $(CFLAGS) -c testfuncs.c

main.o: main.c testfuncs.h
	$(CC) $(CFLAGS) -c main.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
