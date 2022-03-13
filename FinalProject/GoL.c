/* GAME OF LIFE SIMULATION BY JAKOB GÖLÉN */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

typedef struct tiles{
    bool Cell;
    bool Cellbuffer;
} tile;


int main(const int argc, char *argv[]){
    if (argc != 3){
        printf("Input width and height (as integers)");
        return -1;
    }
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);


    tile **board = (tile**)malloc(width*sizeof(tile*));
    for(int i=0; i<width; i++){
        board[i] = (tile*)malloc(height*sizeof(tile));
    }


    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            int randnr = rand()%10;
            if (randnr == 1) printf("▪ ");
            else printf("▫ ");
        }
        printf("\n");
    }


    for(int i=0; i<width; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}