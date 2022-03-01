#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "graphics.h"



// Defining the timer
static double get_wall_seconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
    return seconds;
}


typedef struct galsim{
    double pos_x, pos_y;	
    double pos_x_new, pos_y_new;	
    double v_x, v_y;	
    double v_x_new, v_y_new;	
    double mass;	
    double brightness;	
} vec;


vec *p;

// The function for the summation in the formula for the force
static inline void SumInForce(int i, int j, double EPS, double *restrict sum_x, double *restrict sum_y, vec *p){
    double r_x, r_y, r_vec, r_ij, num, temp1, temp2, temp3, temp4;
    r_x = p[i].pos_x - p[j].pos_x;
    r_y = p[i].pos_y - p[j].pos_y;

    // The distance between the particle
    r_vec = (r_x * r_x) + (r_y * r_y);
    r_ij  = sqrt(r_vec);

    // The summation
    temp2   =  r_ij + EPS;
    temp3   = temp2 *temp2;
    num     = temp2 * temp3;
    temp1   = 1.0/num;
    temp4   = temp1 * p[j].mass;
    *sum_x += temp4 * r_x;
    *sum_y += temp4 * r_y;
}


int main(const int argc, char *argv[]){

    // Checking if the input arguments to the program are corret
    if (argc != 6) {
        printf("Give 5 input arguments: int N, filename.gal , int nsteps, double delta_t, graphics (0 or 1) .\n");
        exit(1);
    }
    
    // The input arguments
    char filename_in[70];
    strcpy(filename_in, argv[2]);
    const int N           =  atoi(argv[1]);
    const int nsteps      =  atoi(argv[3]);
    const double delta_t  =  atof(argv[4]);
    const int graphics    =  atoi(argv[5]);
    
    // Graphics settings
    const float circleRadius = 0.003, circleColor = 0;
    const int windowLength = 400;
    const int windowWidth = 400;
    unsigned int i, j, n, k;

    // Creating a window and setting the axes if graphics routines are turned on  
    if (graphics == 1){
        InitializeGraphics(argv[0], windowWidth, windowLength);
        SetCAxes(0, 1);
    }

    // Alocatting the memory dynamically

    p = (vec*) malloc(N*sizeof(vec));
    //double *inputs, *outputs;
    //inputs  = (double*)malloc(6*N*sizeof(double));
    //outputs = (double*)malloc(6*N*sizeof(double));
    
    FILE *file_in, *file_out;
    // Opening the input file
    file_in = fopen(filename_in, "r");
    if (file_in == NULL) {
        printf("Error! Can't open the file.\n");
        exit(1);
    }
    // Reading the input file

    for(i = 0; i < N; i++){         
        fread(&p[i].pos_x,     sizeof(double), 1, file_in);
        fread(&p[i].pos_y,     sizeof(double), 1, file_in);
        fread(&p[i].mass,      sizeof(double), 1, file_in);
        fread(&p[i].v_x,       sizeof(double), 1, file_in);
        fread(&p[i].v_y,       sizeof(double), 1, file_in);
        fread(&p[i].brightness,    sizeof(double), 1, file_in);
        //p[i].pos_x_new = p[i].pos_x;
        //p[i].pos_y_new = p[i].pos_y;
        //p[i].v_x_new   = p[i].v_x;
        //p[i].v_y_new   = p[i].v_y;
    }
    //fread(p, sizeof(double), 6*N, file_in);   

    // Closing the input file
    fclose(file_in);

    // Declaring variables
    const double EPS = 0.001;
    const double G = (double) (100.0/N);
    double sum_x, sum_y, temp10, F_x, F_y, a_x, a_y, v1_x, v1_y, p2_x, p2_y;
    double start_time, time_taken;

    // Starting the timer
    start_time = get_wall_seconds();

    // Implementing the algorithm
    for(n = 0; n < nsteps; n++){
        for(i = 0; i < N; i++){
            // Initialize the sum variables
            sum_x = 0;
            sum_y = 0;

            // Summing as long as i is not equal j
            for(j = 0; j < i; j++){
                SumInForce(i, j, EPS, &sum_x, &sum_y, p);
            }
            for(j = i+1; j < N; j++){
                SumInForce(i, j, EPS, &sum_x, &sum_y, p);
            } 
            // Calculating the forces of particle i
            F_x = -G * p[i].mass * sum_x;
            F_y = -G * p[i].mass * sum_y;

            // The acceleration of particle i
            temp10 = 1.0/p[i].mass;
            a_x = F_x * temp10;
            a_y = F_y * temp10;

            // The updated velocity of particle i at step n + 1
            v1_x = delta_t * a_x;
            v1_y = delta_t * a_y;
            p[i].v_x_new = p[i].v_x + v1_x;
            p[i].v_y_new = p[i].v_y + v1_y;

            // The updated position of particle i at step n + 1
            p2_x = delta_t * p[i].v_x_new;
            p2_y = delta_t * p[i].v_y_new;
            p[i].pos_x_new = p[i].pos_x + p2_x;
            p[i].pos_y_new = p[i].pos_y + p2_y;

            // Clearing the screen
            if (graphics == 1)
                ClearScreen();
        }
        // Updating the positions and velocities 
        for(k = 0; k < N; k++){
            p[k].pos_x = p[k].pos_x_new;
            p[k].pos_y = p[k].pos_y_new;
            p[k].v_x = p[k].v_x_new;
            p[k].v_y = p[k].v_y_new;

            // Drawing the stars/particles 
            if (graphics == 1)
                DrawCircle((float)(p[k].pos_x), (float)(p[k].pos_y), 1, 1, circleRadius, circleColor);
        }  

        // Refreshing and sleeping
        if (graphics == 1){
            Refresh();
            usleep(1500);
        }        
    }
    // Flushing and closing the display
    if (graphics == 1){
        FlushDisplay();
        CloseDisplay();
    }

    // Stopping the timer and measuring the execution time
    time_taken = get_wall_seconds() - start_time;

    // Printing the execution time
    printf("Time taken = %.4f\n", time_taken);

    // Creating new file for the outputs
    file_out = fopen("result.gal", "w");

    // Writing the data to the output file
    for (i = 0; i < N; i++){ 
        fwrite(&p[i].pos_x_new,       sizeof(double), 1, file_out);
        fwrite(&p[i].pos_y_new,       sizeof(double), 1, file_out);
        fwrite(&p[i].mass,            sizeof(double), 1, file_out);
        fwrite(&p[i].v_x_new,         sizeof(double), 1, file_out);
        fwrite(&p[i].v_y_new,         sizeof(double), 1, file_out);
        fwrite(&p[i].brightness,         sizeof(double), 1, file_out);
    } 

    // Closing the output file
    fclose(file_out);

    // Freeing the allocated memory
    free(p);

    return 0;

}



