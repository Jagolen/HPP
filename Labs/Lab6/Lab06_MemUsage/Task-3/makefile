CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o testfunc1.o testfunc2.o
EXECUTABLE = restrict_test

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

testfunc1.o: testfunc1.h testfunc1.c
	$(CC) $(CFLAGS) -c testfunc1.c

testfunc2.o: testfunc2.h testfunc2.c
	$(CC) $(CFLAGS) -c testfunc2.c

main.o: main.c testfunc1.h testfunc2.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
