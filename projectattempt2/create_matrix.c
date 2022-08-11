//To create the matrices

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(const int argc, char *argv[]){
    const int size = atoi(argv[1]);

    double **A = (double**)malloc(size*sizeof(double*));
    double **B = (double**)malloc(size*sizeof(double*));
    char filename[60];
    strcpy(filename, argv[2]);

    for(int i = 0; i<size; i++){
        A[i] = (double*)malloc(size*sizeof(double));
        B[i] = (double*)malloc(size*sizeof(double));
    }

    srand(time(0));

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            A[i][j] = (double)(rand()/(RAND_MAX/1000));
            B[i][j] = (double)(rand()/(RAND_MAX/1000));
        }
    }

    FILE *output;

    output = fopen(filename, "w");

    if(output == NULL){
        printf("The following file can not be opened: %s",filename);
        exit(1);
    }

    fwrite(&size, sizeof(int), 1, output);

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            fwrite(&A[i][j], sizeof(double), 1, output);
        }
    }

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            fwrite(&B[i][j], sizeof(double), 1, output);
        }
    }

    fclose(output);

/*     printf("A = \n");
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }

    printf("B = \n");
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%lf ", B[i][j]);
        }
        printf("\n");
    } */




    for(int i = 0; i<size; i++){
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);



    return 0;
}