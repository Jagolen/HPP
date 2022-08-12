/* 
Matrix Matrix Multiplication with Strassens Algorithm
By Jakob Gölén
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Function for adding two matrices, since it is repeatedly used in the function, inlined
inline void matrix_addition(double **A, double **B, double **C, int size){
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

//Function for subtracting two matrices, since it is repeatedly used in the function, inlined
inline void matrix_subtraction(double **A, double **B, double **C, int size){
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

//Main strassen function. It is too complicated to be inlined.
void strassen_mult(double **A, double **B, double **C, int size){
    //Allocating memory for the submatrices, the 7 p matrices, and two temporary matrices to be used when addition is needed before multiplication
    double **A11 = (double**)malloc(size*sizeof(double*));
    double **A12 = (double**)malloc(size*sizeof(double*));
    double **A21 = (double**)malloc(size*sizeof(double*));
    double **A22 = (double**)malloc(size*sizeof(double*));

    double **B11 = (double**)malloc(size*sizeof(double*));
    double **B12 = (double**)malloc(size*sizeof(double*));
    double **B21 = (double**)malloc(size*sizeof(double*));
    double **B22 = (double**)malloc(size*sizeof(double*));

    double **C11 = (double**)malloc(size*sizeof(double*));
    double **C12 = (double**)malloc(size*sizeof(double*));
    double **C21 = (double**)malloc(size*sizeof(double*));
    double **C22 = (double**)malloc(size*sizeof(double*));

    double **P1 = (double**)malloc(size*sizeof(double*));
    double **P2 = (double**)malloc(size*sizeof(double*));
    double **P3 = (double**)malloc(size*sizeof(double*));
    double **P4 = (double**)malloc(size*sizeof(double*));
    double **P5 = (double**)malloc(size*sizeof(double*));
    double **P6 = (double**)malloc(size*sizeof(double*));
    double **P7 = (double**)malloc(size*sizeof(double*));

    double **temp1 = (double**)malloc(size*sizeof(double*));
    double **temp2 = (double**)malloc(size*sizeof(double*));

    for(int i = 0; i<size; i++){
        A11[i] = (double*)malloc(size*sizeof(double));
        A12[i] = (double*)malloc(size*sizeof(double));
        A21[i] = (double*)malloc(size*sizeof(double));
        A22[i] = (double*)malloc(size*sizeof(double));

        B11[i] = (double*)malloc(size*sizeof(double));
        B12[i] = (double*)malloc(size*sizeof(double));
        B21[i] = (double*)malloc(size*sizeof(double));
        B22[i] = (double*)malloc(size*sizeof(double));

        C11[i] = (double*)malloc(size*sizeof(double));
        C12[i] = (double*)malloc(size*sizeof(double));
        C21[i] = (double*)malloc(size*sizeof(double));
        C22[i] = (double*)malloc(size*sizeof(double));

        P1[i] = (double*)malloc(size*sizeof(double));
        P2[i] = (double*)malloc(size*sizeof(double));
        P3[i] = (double*)malloc(size*sizeof(double));
        P4[i] = (double*)malloc(size*sizeof(double));
        P5[i] = (double*)malloc(size*sizeof(double));
        P6[i] = (double*)malloc(size*sizeof(double));
        P7[i] = (double*)malloc(size*sizeof(double));

        temp1[i] = (double*)malloc(size*sizeof(double));
        temp2[i] = (double*)malloc(size*sizeof(double));
    }




    //Freeing the used memory
    for(int i = 0; i<size; i++){
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);

        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);

        free(C11[i]);
        free(C12[i]);
        free(C21[i]);
        free(C22[i]);

        free(P1[i]);
        free(P2[i]);
        free(P3[i]);
        free(P4[i]);
        free(P5[i]);
        free(P6[i]);
        free(P7[i]);

        free(temp1[i]);
        free(temp2[i]);
    }
    free(A11);
    free(A12);
    free(A21);
    free(A22);

    free(B11);
    free(B12);
    free(B21);
    free(B22);

    free(C11);
    free(C12);
    free(C21);
    free(C22);

    free(P1);
    free(P2);
    free(P3);
    free(P4);
    free(P5);
    free(P6);
    free(P7);

    free(temp1);
    free(temp2);
}


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

    //Calling the main strassen function
    strassen_mult(A, B, C, size/2);

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