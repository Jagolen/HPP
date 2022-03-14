/* GAME OF LIFE SIMULATION BY JAKOB GÖLÉN */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>


// Struct representing the tiles on the board and determines if the tile is alive or dead
typedef struct tiles{
    int Cell;
    int Cellbuffer;
} tile;



//Simple graphics routine in the command window
static inline void graphics(tile **board, int w, int h){
    for(int i = 0; i<w; i++){
        printf("\n");
        for(int j = 0; j<h; j++){
            if(board[i][j].Cell == 1) printf("▪ ");
            else printf("▫ ");
        }
    }
}

//Function setting the initial condition
void setup(const int argc, char *argv[], tile **board,int w, int h){
    if(argc == 4){//If a file was provided as input
        FILE *input;
        char filename[60];
        strcpy(filename, argv[3]);

        //Opening the input file
        input = fopen(filename,"r");
        if(input == NULL){
            printf("The following file can not be opened: %s",filename);
            exit(1);
        }

        //Reading the input file
        int saved_cells;
        fread(&saved_cells, sizeof(int), 1, input);
        for (int i = 0; i<saved_cells; i++){
            int x,y;
            fread(&x, sizeof(int), 1, input);
            fread(&y, sizeof(int),1, input);
            if(x >= w || y >= h || x<0 || y<0){
                printf("Error: Coordinates in file are outside the board\n");
                exit(-1);
            }
            board[x][y].Cell = 1;
        }
        fclose(input);
        graphics(board,w,h);
        return;
    }
    //If there is no input file, a manual setup is required
    printf("MANUAL INITIAL CONFIGURATION\n");

    //Set up file and filename
    char filename[60];
    printf("Output filename: ");
    scanf("%s",filename);
    FILE *output;
    output = fopen(filename, "w");

    //Set up number of cells
    int saved_cells;
    printf("How many alive cells at start?: ");
    scanf("%d",&saved_cells);
    fwrite(&saved_cells, sizeof(int), 1, output);
    
    //For every cell to be written, write the x and y coordinates and check that it's inside the board
    for(int i = 0; i<saved_cells; i++){
        int x ,y;
        printf("x and y for cell %d of %d (non-negative integers): ",i+1, saved_cells);
        scanf("%d %d", &x, &y);
        if(x >= w || y >= h || x<0 || y<0){
            printf("Error: Input coordinates are outside the board\n");
            exit(-1);
        }
        board[x][y].Cell = 1;
        fwrite(&x, sizeof(int), 1, output);
        fwrite(&y, sizeof(int), 1, output);
    }

    //Close the file and print the starting board
    fclose(output);
    graphics(board,w,h);
    
}



int main(const int argc, char *argv[]){
    if (argc != 3 && argc !=4){
        printf("Input width and height (as integers) and initial configuration (excliude this if you don't have an input file for manual setup)\n");
        return -1;
    }
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    //Creating the board
    tile **board = (tile**)malloc(width*sizeof(tile*));
    for(int i=0; i<width; i++){
        board[i] = (tile*)malloc(height*sizeof(tile));
    }

    //Setting all cells to zero
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            board[i][j].Cell = 0;
            board[i][j].Cellbuffer = 0;
        }
    }
    
    // INITIAL CONFIGURATION
    setup(argc, argv, board, width, height);



    //Freeing the memory used for the board
    for(int i=0; i<width; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}