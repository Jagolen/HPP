CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f
OBJS = main.o func.o
EXECUTABLE = pure_test

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

func.o: func.h func.c
	$(CC) $(CFLAGS) -c func.c	

main.o: main.c func.h
	$(CC) $(CFLAGS) -c main.c 

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
