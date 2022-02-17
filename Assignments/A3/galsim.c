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

// The function for the summation in the formula for the force
static inline void SumInForce(int i, int j, double EPS, double *sum_x, double *sum_y, double *restrict inputs){
    double r_x, r_y, r_vec, r_ij, num, temp1, temp2, temp3, temp4;
    r_x  = inputs[i*6 + 0] - inputs[j*6 + 0];
    r_y  = inputs[i*6 + 1] - inputs[j*6 + 1];

    // The distance between the particle
    r_vec = (r_x * r_x) + (r_y * r_y);
    r_ij  = sqrt(r_vec);

    // The summation
    temp2   =  r_ij + EPS;
    temp3   = temp2 *temp2;
    num     = temp2 * temp3;
    temp1   = 1.0/num;
    temp4   = temp1 * inputs[j*6 + 2];
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
    
    // Creating a window and setting the axes if graphics routines are turned on  
    if (graphics == 1){
        InitializeGraphics(argv[0], windowWidth, windowLength);
        SetCAxes(0, 1);
    }
    

    // Alocatting the memory dynamically
    double *inputs, *outputs;
    inputs  = (double*)malloc(6*N*sizeof(double));
    outputs = (double*)malloc(6*N*sizeof(double));

    FILE *file_in, *file_out;
    // Opening the input file
    file_in = fopen(filename_in, "r");
    if (file_in == NULL) {
        printf("Error! Can't open the file.\n");
        exit(1);
    }
    // Reading the input file
    fread(inputs, sizeof(double), 6*N, file_in);   

    // Closing the input file
    fclose(file_in);

    // Declaring variables
    const double EPS = 0.001;
    const double G = (double) (100.0/N);
    unsigned int i, j, n, k;
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
                SumInForce(i, j, EPS, &sum_x, &sum_y, inputs);
            }
            for(j = i+1; j < N; j++){
                SumInForce(i, j, EPS, &sum_x, &sum_y, inputs);
            } 
            // Adding the masses from input to output
            outputs[i*6 + 2] = inputs[i*6 + 2];

            // Adding the brightness from input to output
            outputs[i*6 + 5] = inputs[i*6 + 5];

            // Calculating the forces of particle i
            F_x = -G * inputs[i*6 + 2] * sum_x;
            F_y = -G * inputs[i*6 + 2] * sum_y;

            // The acceleration of particle i
            temp10 = 1.0/inputs[i*6 + 2];
            a_x = F_x * temp10;
            a_y = F_y * temp10;

            // The updated velocity of particle i at step n + 1
            v1_x = delta_t * a_x;
            v1_y = delta_t * a_y;
            outputs[i*6 + 3] = inputs[i*6 + 3] + v1_x;
            outputs[i*6 + 4] = inputs[i*6 + 4] + v1_y;

            // The updated position of particle i at step n + 1
            p2_x = delta_t * outputs[i*6 + 3];
            p2_y = delta_t * outputs[i*6 + 4];
            outputs[i*6 + 0] = inputs[i*6 + 0] + p2_x;
            outputs[i*6 + 1] = inputs[i*6 + 1] + p2_y;

            // Clearing the screen
            if (graphics == 1)
                ClearScreen();
        }
        // Updating the positions and velocities 
        for(k = 0; k < N; k++){
            inputs[k*6 + 0] = outputs[k*6 + 0];
            inputs[k*6 + 1] = outputs[k*6 + 1];
            inputs[k*6 + 3] = outputs[k*6 + 3];
            inputs[k*6 + 4] = outputs[k*6 + 4];

            // Drawing the stars/particles 
            if (graphics == 1)
                DrawCircle((float)(inputs[k*6 + 0]), (float)(inputs[k*6 + 1]), 1, 1, circleRadius, circleColor);
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
    fwrite(outputs, sizeof(double), 6*N, file_out);   

    // Closing the output file
    fclose(file_out);

    // Freeing the allocated memory
    free(inputs);
    free(outputs);

    return 0;

}



