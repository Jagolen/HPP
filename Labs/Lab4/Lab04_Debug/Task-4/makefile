CC = gcc
LD = gcc
CFLAGS = -g -O3 -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o sort_funcs.o
EXECUTABLE = sort_test

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

sort_funcs.o: sort_funcs.h sort_funcs.c
	$(CC) $(CFLAGS) -c sort_funcs.c

main.o: main.c sort_funcs.h
	$(CC) $(CFLAGS) -c main.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
