/* 
Matrix Matrix Multiplication with Strassens Algorithm
By Jakob Gölén
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(const char argc, char* argv[]){
    if(argc != 2){
        printf("input the filename for the file containing the A and B matrices to be multiplied");
        return -1;
    }

    //The input filename
    char filename[60];
    strcpy(filename, argv[1]);

    //Opening the file and reading the size of the matrices
    int size;
    FILE *input;
    input = fopen(filename, "r");

    if(input == NULL){
        printf("The following file can not be opened: %s",filename);
        exit(1);
    }

    fread(&size, sizeof(int), 1, input);

    //Allocating memory for the A and B matrices to be multiplied and for the C matrix where the result will be stored

    double **A = (double**)malloc(size*sizeof(double*));
    double **B = (double**)malloc(size*sizeof(double*));
    double **C = (double**)malloc(size*sizeof(double*));
    for(int i = 0; i<size; i++){
        A[i] = (double*)malloc(size*sizeof(double));
        B[i] = (double*)malloc(size*sizeof(double));
        C[i] = (double*)malloc(size*sizeof(double));
    }

    //Importing the A and B matrices from the file

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            fread(&A[i][j], sizeof(double), 1, input);
        }
    }

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            fread(&B[i][j], sizeof(double), 1, input);
        }
    }
    fclose(input);

//TEST
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


//Freeing the matrices

for(int i = 0; i<size; i++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);



    return 0;
}