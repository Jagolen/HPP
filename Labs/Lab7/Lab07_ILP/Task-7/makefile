CC = gcc
LD = gcc
CFLAGS = -O0
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o myfunctions.o
EXECUTABLE = the_program

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

myfunctions.o: myfunctions.h myfunctions.c
	$(CC) $(CFLAGS) -c myfunctions.c

main.o: main.c myfunctions.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
