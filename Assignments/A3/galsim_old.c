#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char** argv){
    // Checking if the input arguments to the program are corret
    //if (argc != 6) {
    //    printf("Give 5 input arguments: int N, filename.gal , int nsteps, double delta_t, graphics (0 or 1) .\n");
    //    exit(1);
    //}
    const float circleRadius=0.0025, circleColor=0;
    const int windowWidth=800;
    int N = 100;
    int nsteps = 200;
    double delta_t = 0.001;

    char filename_in[60] = "ellipse_N_00100.gal";
    //strcpy(filename_in, argv[2]);
    //int N        =  atoi(argv[1]);
    //int nsteps   =  atoi(argv[3]);
    //int delta_t  =  atoi(argv[4]);
    //int graphics =  atoi(argv[5]);

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

    InitializeGraphics(argv[0],windowWidth,windowWidth);
    SetCAxes(0,1);
    // Declaring variables
    const double EPS = 0.001;
    double G = 100.0/N;
    int i, j, n, m;
    double r_x, r_y, r_vec, r_ij, num, sum_x, sum_y, F_x, F_y, a_x, a_y, k1_x, k1_y, k2_x, k2_y;

    // Implementing the algorithm
    for(n = 0; n < nsteps; n++){
        ClearScreen();
        for(i = 0; i < N; i++){
            // Initialize the variables
            sum_x = 0;
            sum_y = 0;
            for(j = 0; j < N; j++){
                // Summing as long as i is not equal j
                if (i != j){
                    //  The position of particle i relative to particle j
                    r_x  = inputs[i*6 + 0] - inputs[j*6 + 0];
                    r_y  = inputs[i*6 + 1] - inputs[j*6 + 1];

                    // The distance between the particle
                    r_vec = (r_x * r_x) + (r_y * r_y);
                    r_ij  = sqrt(r_vec);

                    // The summation in the formula for the force
                    num    = (r_ij + EPS) * (r_ij + EPS) * (r_ij + EPS);
                    sum_x += 1/num * inputs[j*6 + 2] * r_x;
                    sum_y += 1/num * inputs[j*6 + 2] * r_y;
                }       
            }
            // Adding the masses from input to output
            outputs[i*6 + 2] = inputs[i*6 + 2];

            // Adding the brightness from input to output
            outputs[i*6 + 5] = inputs[i*6 + 5];

            // Calculating the forces of particle i
            F_x = -G * inputs[i*6 + 2] * sum_x;
            F_y = -G * inputs[i*6 + 2] * sum_y;

            // The acceleration of particle i
            a_x = F_x/inputs[i*6 + 2];
            a_y = F_y/inputs[i*6 + 2];

            // The updated velocity of particle i at step n + 1
            k1_x = delta_t * a_x;
            k1_y = delta_t * a_y;
            outputs[i*6 + 3] = inputs[i*6 + 3] + k1_x;
            outputs[i*6 + 4] = inputs[i*6 + 4] + k1_y;

            // The updated position of particle i at step n + 1
            k2_x = delta_t * outputs[i*6 + 3];
            k2_y = delta_t * outputs[i*6 + 4];
            outputs[i*6 + 0] = inputs[i*6 + 0] + k2_x;
            outputs[i*6 + 1] = inputs[i*6 + 1] + k2_y;
            DrawCircle((float)(outputs[i*6 + 0]),(float)(outputs[i*6 + 1]),1,1,circleRadius,circleColor);
        }
        
        printf("Next pic \n");
        printf("%lf\n",outputs[0]);
        Refresh();
        usleep(10000);

    }
    FlushDisplay();
    CloseDisplay();
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





/*

typedef struct galsim{
    double x, y, mass, bright, force;
}vec;


vec *pos, *v, *m, *br, *F, *v_after, *pos_after, *a, *k1, *k2, *r;

int main(int argc, char** argv){
    //if (argc != 6) {
    //    printf("Error. Expected five input arguments.\n");
    //    exit(1);
    //}

    char filename_in[50] = "ellipse_N_00100";
    //strcpy(filename_in, argv[2]);
    //int N        =  atoi(argv[1]);
    //int nsteps   =  atoi(argv[3]);
    //int delta_t  =  atoi(argv[4]);
    //int graphics =  atoi(argv[5]);

    int N = 100;
    int nsteps = 200;
    const double EPS = 0.001;
    double delta_t = 0.00001;
    int G = 100/N;
    //double r_x, r_y;
    double r_ij, num, r_vec, sum_x, sum_y;

    FILE *file_in, *file_out;

    char file_type[10] = ".gal";

    strcat(filename_in, file_type);

    file_in = fopen(filename_in, "r");



    if (file_in == NULL) {
        printf("Error! Can't open the file.\n");
        exit(1);
    }


    int i, j, n;

    pos        = (double*)malloc(N*sizeof(double));
    v          = (double*)malloc(N*sizeof(double));
    m          = (double*)malloc(N*sizeof(double));
    br         = (double*)malloc(N*sizeof(double));
    F          = (double*)malloc(N*sizeof(double));
    v_after    = (double*)malloc(N*sizeof(double));
    pos_after  = (double*)malloc(N*sizeof(double));
    a          = (double*)malloc(N*sizeof(double));
    k1         = (double*)malloc(N*sizeof(double));
    k2         = (double*)malloc(N*sizeof(double));
    r          = (double*)malloc(N*sizeof(double));

    for(i = 0; i < N; i++){ 
        fread(&pos[i].x,     sizeof(double), 1, file_in);
        fread(&pos[i].y,     sizeof(double), 1, file_in);
        fread(&m[i].mass,    sizeof(double), 1, file_in);
        fread(&v[i].x,       sizeof(double), 1, file_in);
        fread(&v[i].y,       sizeof(double), 1, file_in);
        fread(&br[i].bright, sizeof(double), 1, file_in);
    }
    fclose(file_in);
    
    
    for(n = 0; n < nsteps; n++){
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                if (i != j){
                    r[j].x  = pos[j].x - pos[i].x;
                    r[j].y  = pos[j].y - pos[i].y;

                    r_vec    = (r[j].x * r[j].x) + (r[j].y * r[j].y);
                    r_ij = sqrt(r_vec);
                    num  = (r_ij + EPS) * (r_ij + EPS) * (r_ij + EPS);
                    
                    sum_x = 1/num * m[j].mass * r[j].x;
                    sum_y = 1/num * m[j].mass * r[j].y;

                }       
            }
            F[i].x = -G * m[i].mass * r[i].x * sum_x;
            F[i].y = -G * m[i].mass * r[i].y * sum_y;

            a[i].x = F[i].x/m[i].mass;
            a[i].y = F[i].y/m[i].mass;

            k1[i].x = delta_t * a[i].x;
            k1[i].y = delta_t * a[i].y;

            v_after[i].x = v[i].x + k1[i].x;
            v_after[i].y = v[i].y + k1[i].y;

            k2[i].x = delta_t * v_after[i].x;
            k2[i].y = delta_t * v_after[i].y;

            pos_after[i].x = pos[i].x + k2[i].x;
            pos_after[i].y = pos[i].y + k2[i].y;
        }

    }

    
    char filename_out[70] = "result_";
    strcat(filename_out, filename_in);
    //printf("%s\n", filename_out);
    file_out = fopen("result.gal", "w");
    for (i = 0; i < N; i++){ 
        fwrite(&pos_after[i].x,       sizeof(double), 1, file_out);
        fwrite(&pos_after[i].y,       sizeof(double), 1, file_out);
        fwrite(&m[i].mass,            sizeof(double), 1, file_out);
        fwrite(&v_after[i].x,         sizeof(double), 1, file_out);
        fwrite(&v_after[i].y,         sizeof(double), 1, file_out);
        fwrite(&br[i].bright,         sizeof(double), 1, file_out);
    }
    fclose(file_out);
    
    
    for (i = 0; i < N; i++){
        printf("%lf\n", pos_after[i].x);  
        //printf("%lf\n", pos_after[i].y); 
        //printf("%lf\n", m[i].mass); 
        //printf("%lf\n", v_after[i].x);  
        //printf("%lf\n", v_after[i].y);
        //printf("%lf\n", br[i].bright); 
    }
    

    free(pos);
    free(v);
    free(m);
    free(br);
    free(pos_after);
    free(v_after);

    //for (m = 0; m < N*6; m++){
    //    printf("%lf\n", outputs[m]);  
    //}

    return 0;

}


*/

