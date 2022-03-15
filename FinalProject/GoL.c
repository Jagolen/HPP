/* GAME OF LIFE SIMULATION BY JAKOB GÖLÉN */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <unistd.h>


// Struct representing the tiles on the board and determines if the tile is alive or dead
typedef struct tiles{
    int Cell;
    int Cellbuffer;
} tile;



//Simple graphics routine in the command window
static inline void graphics(tile **board, int w, int h, long s){

    //Shows which step we are on
    printf("\nStep %ld",s);

    //Goes through the board and prints a filled square if the cell is alive or an empty square if the cell is dead
    for(int i = 0; i<w; i++){
        printf("\n");
        for(int j = 0; j<h; j++){
            if(board[i][j].Cell == 1) printf("▪ ");
            else printf("▫ ");
        }
    }
    printf("\n");
    //usleep(500000);
}

//Function setting the initial condition
void setup(const int argc, char *argv[], tile **board,int w, int h, int *min_x, int *max_x, int *min_y, int *max_y){
    if(argc == 6){//If a file was provided as input
        FILE *input;
        char filename[60];
        strcpy(filename, argv[5]);

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

            //Determining min and max coordinates
            if(x<*min_x) *min_x = x;
            if(x>*max_x) *max_x = x;
            if(y<*min_y) *min_y = y;
            if(y>*max_y) *max_y = y;
        }

        //Closing the file
        fclose(input);
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

        //Determining min and max coordinates
        if(x<*min_x) *min_x = x;
        if(x>*max_x) *max_x = x;
        if(y<*min_y) *min_y = y;
        if(y>*max_y) *max_y = y;

        //Write the coordinates to the file
        fwrite(&x, sizeof(int), 1, output);
        fwrite(&y, sizeof(int), 1, output);
    }

    //Close the file
    fclose(output);
    
}



int main(const int argc, char *argv[]){
    if (argc != 5 && argc !=6){
        printf("Input width and height (as integers), steps to run, how often to show the board (0 to only show starting and final configuration) and initial configuration (excliude this if you don't have an input file for manual setup)\n");
        return -1;
    }

    //Setting the input parameters
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    long steps = atol(argv[3]);
    int graphics_interval = atoi(argv[4]);

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
    
    //Determining the max and min coordinates of the alive cells to be set in the setup function (Only the cells inside this and the ones directly adjacent to the border needs to be measured)
    int min_x = width+1;
    int max_x = -1;
    int min_y = height+1;
    int max_y = -1;

    // INITIAL CONFIGURATION
    setup(argc, argv, board, width, height, &min_x, &max_x, &min_y, &max_y);
    graphics(board,width,height,0);

    // The algorithm
    for (long s = 0; s<steps; s++){
        for(int i = 0; i<width; i++){
            for(int j = 0; j<height; j++){
                //Variable for checking how many neighbors a cell has
                int neighbors = 0;
                
                /*Checking all the neighbors. I add the width/height 
                and then take the remainder in order to have a wrap around effect
                e.g a cell furthest left on the board will have a cell
                furthest right as a neighbor
                */
                neighbors += board[(i-1+width)%width][(j-1+height)%height].Cell;
                neighbors += board[(i-1+width)%width][(j+height)%height].Cell;
                neighbors += board[(i-1+width)%width][(j+1+height)%height].Cell;
                neighbors += board[(i+width)%width][(j-1+height)%height].Cell;
                neighbors += board[(i+width)%width][(j+1+height)%height].Cell;
                neighbors += board[(i+1+width)%width][(j-1+height)%height].Cell;
                neighbors += board[(i+1+width)%width][(j+height)%height].Cell;
                neighbors += board[(i+1+width)%width][(j+1+height)%height].Cell;
                //The cases

                /*
                An alive cell dies if it has less than 2 or more than 3 neighbors
                The cellbuffer must be used so that the board doesn't change until all
                cell states has been calculated
                */
                if(board[i][j].Cell == 1){
                    if(neighbors < 2 || neighbors > 3) board[i][j].Cellbuffer = 0;
                    else board[i][j].Cellbuffer = 1;
                }

                //A dead cell becomes alive if it has exactly 3 neighbors
                else{
                    if(neighbors == 3) board[i][j].Cellbuffer = 1;
                    else board[i][j].Cellbuffer = 0;
                }
            }
        }

        //When all cell states for the next step has been calculated, the cells are updated
        for(int i = 0; i<width; i++){
            for(int j = 0; j<height;j++){
                board[i][j].Cell = board[i][j].Cellbuffer;
            }
        }

        //Check if the board for this step should be displayed
        if(graphics_interval != 0){
            if(s % graphics_interval == 0) graphics(board,width,height,s+1);
        }

    }



    //Final configuration
    graphics(board,width,height,steps);

    //Freeing the memory used for the board
    for(int i=0; i<width; i++){
        free(board[i]);
    }
    free(board);

    return 0;
}