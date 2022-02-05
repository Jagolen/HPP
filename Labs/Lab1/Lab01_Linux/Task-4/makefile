sorting:readData.o sort.o main.o
	gcc -w readData.o sort.o main.o -o sorting

readData.o: readData.h readData.c
	gcc -w -c readData.c

sort.o: sort.c sort.h
	gcc -w -c sort.c

main.o: main.h main.c readData.h sort.h
	gcc -w -c main.c

clean:
	rm *.o
