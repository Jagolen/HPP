CC = gcc
LD = gcc
CFLAGS = -g -Wall
LDFLAGS = 
RM = /bin/rm -f
OBJS = mymainprog.o myfuncs.o

prog: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o prog

myfuncs.o: myfuncs.h myfuncs.c
	$(CC) $(CFLAGS) -c myfuncs.c

mymainprog.o: mymainprog.c myfuncs.h
	$(CC) $(CFLAGS) -c mymainprog.c

clean:
	$(RM) prog $(OBJS)
