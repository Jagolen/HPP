CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -Werror
LDFLAGS = 
RM = /bin/rm -f
OBJS1 = main.o transpose.o
OBJS2 = main_x.o transpose_x.o
EXECUTABLE1 = transpose_test
EXECUTABLE2 = transpose_test_x

all: $(EXECUTABLE1) $(EXECUTABLE2)

$(EXECUTABLE1): $(OBJS1)
	$(LD) $(LDFLAGS) $(OBJS1) -o $(EXECUTABLE1)

$(EXECUTABLE2): $(OBJS2)
	$(LD) $(LDFLAGS) $(OBJS2) -o $(EXECUTABLE2)

transpose.o: transpose.h transpose.c
	$(CC) $(CFLAGS) -c transpose.c

main.o: main.c transpose.h
	$(CC) $(CFLAGS) -c main.c 

transpose_x.o: transpose_x.h transpose_x.c
	$(CC) $(CFLAGS) -c transpose_x.c

main_x.o: main_x.c transpose_x.h
	$(CC) $(CFLAGS) -c main_x.c 

clean:
	$(RM) $(EXECUTABLE1) $(EXECUTABLE2) $(OBJS1) $(OBJS2)
