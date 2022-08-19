/* 
Matrix Matrix Multiplication with Strassens Algorithm
By Jakob Gölén
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

//Main strassen function. It is too complicated to be inlined.
static void strassen_mult(double **A, double **B, double **C, int size){

    //Base case, end of recursions
    if(size == 1){
        C[0][0] = A[0][0] * B[0][0];
    }
    else{
        int rest = size%2;

        //Matrix size is divisible by 2
        if(rest == 0){
            size = size/2;
        }
        //Matrix size is not divisible by 2, pad with one row and column
        else{
            size = (size+1)/2;
        }
        //Allocating memory for the submatrices, the 7 M matrices, and two temporary matrices to be used when addition is needed before multiplication
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

        double **M1 = (double**)malloc(size*sizeof(double*));
        double **M2 = (double**)malloc(size*sizeof(double*));
        double **M3 = (double**)malloc(size*sizeof(double*));
        double **M4 = (double**)malloc(size*sizeof(double*));
        double **M5 = (double**)malloc(size*sizeof(double*));
        double **M6 = (double**)malloc(size*sizeof(double*));
        double **M7 = (double**)malloc(size*sizeof(double*));

        double **temp1 = (double**)malloc(size*sizeof(double*));
        double **temp2 = (double**)malloc(size*sizeof(double*));
        double **temp3 = (double**)malloc(size*sizeof(double*));
        double **temp4 = (double**)malloc(size*sizeof(double*));
        double **temp5 = (double**)malloc(size*sizeof(double*));
        double **temp6 = (double**)malloc(size*sizeof(double*));
        double **temp7 = (double**)malloc(size*sizeof(double*));
        double **temp8 = (double**)malloc(size*sizeof(double*));
        double **temp9 = (double**)malloc(size*sizeof(double*));
        double **temp10 = (double**)malloc(size*sizeof(double*));

        #pragma omp parallel for
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

                M1[i] = (double*)malloc(size*sizeof(double));
                M2[i] = (double*)malloc(size*sizeof(double));
                M3[i] = (double*)malloc(size*sizeof(double));
                M4[i] = (double*)malloc(size*sizeof(double));
                M5[i] = (double*)malloc(size*sizeof(double));
                M6[i] = (double*)malloc(size*sizeof(double));
                M7[i] = (double*)malloc(size*sizeof(double));

                temp1[i] = (double*)malloc(size*sizeof(double));
                temp2[i] = (double*)malloc(size*sizeof(double));
                temp3[i] = (double*)malloc(size*sizeof(double));
                temp4[i] = (double*)malloc(size*sizeof(double));
                temp5[i] = (double*)malloc(size*sizeof(double));
                temp6[i] = (double*)malloc(size*sizeof(double));
                temp7[i] = (double*)malloc(size*sizeof(double));
                temp8[i] = (double*)malloc(size*sizeof(double));
                temp9[i] = (double*)malloc(size*sizeof(double));
                temp10[i] = (double*)malloc(size*sizeof(double));
            }



        //Distributing the A and B matrices into the submatrices, if the matrix is divisible by 2
        if(rest == 0){
            #pragma omp parallel for
                for(int i = 0; i<size; i++){
                    for(int j = 0; j<size; j++){
                        A11[i][j] = A[i][j];
                        A12[i][j] = A[i][j+size];
                        A21[i][j] = A[i+size][j];
                        A22[i][j] = A[i+size][j+size];

                        B11[i][j] = B[i][j];
                        B12[i][j] = B[i][j+size];
                        B21[i][j] = B[i+size][j];
                        B22[i][j] = B[i+size][j+size];
                    }
                }
        }

        /*If the matrix is not divisible by 2, the first to second to last rows and columns are transfered from the A and B matrix
        and the last row and column is determined by which sub matrix it is, for example the last row and column of A22 will be zeroes.
        */
       else{
            #pragma omp parallel for
                for(int i = 0; i<(size-1); i++){
                    for(int j = 0; j<(size-1); j++){
                        A11[i][j] = A[i][j];
                        A12[i][j] = A[i][j+size];
                        A21[i][j] = A[i+size][j];
                        A22[i][j] = A[i+size][j+size];

                        B11[i][j] = B[i][j];
                        B12[i][j] = B[i][j+size];
                        B21[i][j] = B[i+size][j];
                        B22[i][j] = B[i+size][j+size];
                    }

                    //The last rows and columns are either taken from A or B, or is padded with zeros, depending on the submatrix
                    A11[i][size-1] = A[i][size-1];
                    A11[size-1][i] = A[size-1][i];
                    A12[i][size-1] = 0;
                    A12[size-1][i] = A[size-1][i+size];
                    A21[i][size-1] = A[i+size][size-1];
                    A21[size-1][i] = 0;
                    A22[i][size-1] = 0;
                    A22[size-1][i] = 0; 

                    B11[i][size-1] = B[i][size-1];
                    B11[size-1][i] = B[size-1][i];
                    B12[i][size-1] = 0;
                    B12[size-1][i] = B[size-1][i+size];
                    B21[i][size-1] = B[i+size][size-1];
                    B21[size-1][i] = 0;
                    B22[i][size-1] = 0;
                    B22[size-1][i] = 0; 
                }

            //The last row and column, only A11 and B11 has non-zero values taken from A and B respectively
            A11[size-1][size-1] = A[size-1][size-1];
            A12[size-1][size-1] = 0;
            A21[size-1][size-1] = 0;
            A22[size-1][size-1] = 0;

            B11[size-1][size-1] = B[size-1][size-1];
            B12[size-1][size-1] = 0;
            B21[size-1][size-1] = 0;
            B22[size-1][size-1] = 0;
       }

        //The 7 M matrices can be calculated by using tasks
        #pragma omp parallel
        {
            //A single thread sets up the tasks
            #pragma omp single
            {

                /*Calculating M1 = (A11+A22)*(B11+B22) by first saving the addition in the two temp matrices and then recusively performing Strassen's 
                algorithm for the multiplication*/
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp1[i][j] = A11[i][j] + A22[i][j];
                            temp2[i][j] = B11[i][j] + B22[i][j];
                        }
                    }                   
                    strassen_mult(temp1, temp2, M1, size);
                }
                
                //Calculating M2 = (A21+A22)*B11
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp3[i][j] = A21[i][j] + A22[i][j];
                        }
                    }                   
                    strassen_mult(temp3, B11, M2, size);
                }


                //Calculating M3 = A11*(B12-B22)
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp4[i][j] = B12[i][j] - B22[i][j];
                        }
                    }                   
                    strassen_mult(A11, temp4, M3, size);
                }


                //Calculating M4 = A22*(B21-B11)
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp5[i][j] = B21[i][j] - B11[i][j];
                        }
                    }                   
                    strassen_mult(A22, temp5, M4, size);
                }


                //Calculating M5 = (A11+A12)*B22
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp6[i][j] = A11[i][j] + A12[i][j];
                        }
                    }                   
                    strassen_mult(temp6, B22, M5, size);
                }


                //Calculating M6 = (A21-A11)*(B11+B12)
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp7[i][j] = A21[i][j] - A11[i][j];
                            temp8[i][j] = B11[i][j] + B12[i][j];
                        }
                    }                   
                    strassen_mult(temp7, temp8, M6, size);
                }


                //Calculating M7 = (A12-A22)*(B21+B22)
                #pragma omp task
                {
                    for(int i = 0; i<size; i++){
                        for(int j = 0; j<size; j++){
                            temp9[i][j] = A12[i][j] - A22[i][j];
                            temp10[i][j] = B21[i][j] + B22[i][j];
                        }
                    }                   
                    strassen_mult(temp9, temp10, M7, size);
                }
            }
        }



        //Calculating C11 = M1 + M4 - M5 + M7
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            }
        }                   

        //Calculating C12 = M3 + M5
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C12[i][j] = M3[i][j] + M5[i][j];
            }
        }                   

        //Calculating C21 = M2 + M4
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C21[i][j] = M2[i][j] + M4[i][j];
            }
        }                   

        //Calculating C22 = M1 - M2 + M3 + M6
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
            }
        }                   

        //Merging the C submatrices into C, if C was divisible by 2
        if(rest == 0){
            for(int i = 0; i<size; i++){
                for(int j = 0; j<size; j++){
                    C[i][j] = C11[i][j];
                    C[i][j+size] = C12[i][j];
                    C[i+size][j] = C21[i][j];
                    C[i+size][j+size] = C22[i][j];
                }
            }
        }

        //Otherwise, the padded zeroes has to be removed
        else{
            for(int i = 0; i<(size-1); i++){
                for(int j = 0; j<(size-1); j++){
                    C[i][j] = C11[i][j];
                    C[i][j+size] = C12[i][j];
                    C[i+size][j] = C21[i][j];
                    C[i+size][j+size] = C22[i][j];
                }
                C[i][size-1] = C11[i][size-1];
                C[size-1][i] = C11[size-1][i];
                C[size-1][i+size] = C12[size-1][i];
                C[i+size][size-1] = C21[i][size-1];
            }
            C[size-1][size-1] = C11[size-1][size-1];
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

            free(M1[i]);
            free(M2[i]);
            free(M3[i]);
            free(M4[i]);
            free(M5[i]);
            free(M6[i]);
            free(M7[i]);

            free(temp1[i]);
            free(temp2[i]);
            free(temp3[i]);
            free(temp4[i]);
            free(temp5[i]);
            free(temp6[i]);
            free(temp7[i]);
            free(temp8[i]);
            free(temp9[i]);
            free(temp10[i]);
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

        free(M1);
        free(M2);
        free(M3);
        free(M4);
        free(M5);
        free(M6);
        free(M7);

        free(temp1);
        free(temp2);
        free(temp3);
        free(temp4);
        free(temp5);
        free(temp6);
        free(temp7);
        free(temp8);
        free(temp9);
        free(temp10);
    }
}


int main(const char argc, char* argv[]){
    if(argc != 4){
        printf("Usage: ./strassen input_file(A & B matrices) output_file(C matrix) num_threads\n");
        return -1;
    }

    //The input filename
    char filename[60];
    strcpy(filename, argv[1]);

    //The output filename
    char outname[60];
    strcpy(outname, argv[2]);

    //Set number of threads and enable nested parallelism
    const int threads = atoi(argv[3]);
    printf("Threads = %d\n", threads);
    omp_set_num_threads(threads);

    //Opening the file and reading the size of the matrices
    int size;
    FILE *input;
    input = fopen(filename, "r");

    if(input == NULL){
        printf("The following file can not be opened: %s",filename);
        exit(1);
    }
    int read_res;

    read_res = fread(&size, sizeof(int), 1, input);

    //Allocating memory for the A and B matrices to be multiplied and for the C matrix where the result will be stored

    double **A = (double**)malloc(size*sizeof(double*));
    double **B = (double**)malloc(size*sizeof(double*));
    double **C = (double**)malloc(size*sizeof(double*));
    #pragma omp parallel for
        for(int i = 0; i<size; i++){
            A[i] = (double*)malloc(size*sizeof(double));
            B[i] = (double*)malloc(size*sizeof(double));
            C[i] = (double*)malloc(size*sizeof(double));
        }


    //Importing the A and B matrices from the file, the file is read in sequence so no parallelism here

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            read_res = fread(&A[i][j], sizeof(double), 1, input);
        }
    }

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            read_res = fread(&B[i][j], sizeof(double), 1, input);
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



    //Calling the main strassen function
    strassen_mult(A, B, C, size);

    //Writing the output file
    FILE *output;
    output = fopen(outname, "w");
    if(output == NULL){
        printf("The following file can not be opened: %s",outname);
        exit(1);
    }
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            fwrite(&C[i][j], sizeof(double), 1, output);
        }
    }
    fclose(output);
/*     printf("C = \n");
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%lf ", C[i][j]);
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