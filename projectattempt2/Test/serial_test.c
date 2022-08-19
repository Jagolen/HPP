/* 
Matrix Matrix Multiplication with Strassens Algorithm
By Jakob Gölén
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Main strassen function. It is too complicated to be inlined.
static void strassen_mult(double *A, double *B, double *C, int size){

    //Base case, end of recursions
    if(size == 1){
        C[0] = A[0] * B[0];
    }
    else{
        int orig_size = size;
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
        double *allocated_matrix = (double*)malloc(29*size*size*sizeof(double));

        double *A11 = &allocated_matrix[0];
        double *A12 = &allocated_matrix[size*size];
        double *A21 = &allocated_matrix[2*size*size];
        double *A22 = &allocated_matrix[3*size*size];

        double *B11 = &allocated_matrix[4*size*size];
        double *B12 = &allocated_matrix[5*size*size];
        double *B21 = &allocated_matrix[6*size*size];
        double *B22 = &allocated_matrix[7*size*size];

        double *C11 = &allocated_matrix[8*size*size];
        double *C12 = &allocated_matrix[9*size*size];
        double *C21 = &allocated_matrix[10*size*size];
        double *C22 = &allocated_matrix[11*size*size];

        double *M1 = &allocated_matrix[12*size*size];
        double *M2 = &allocated_matrix[13*size*size];
        double *M3 = &allocated_matrix[14*size*size];
        double *M4 = &allocated_matrix[15*size*size];
        double *M5 = &allocated_matrix[16*size*size];
        double *M6 = &allocated_matrix[17*size*size];
        double *M7 = &allocated_matrix[18*size*size];

        double *temp1 = &allocated_matrix[19*size*size];
        double *temp2 = &allocated_matrix[20*size*size];
        double *temp3 = &allocated_matrix[21*size*size];
        double *temp4 = &allocated_matrix[22*size*size];
        double *temp5 = &allocated_matrix[23*size*size];
        double *temp6 = &allocated_matrix[24*size*size];
        double *temp7 = &allocated_matrix[25*size*size];
        double *temp8 = &allocated_matrix[26*size*size];
        double *temp9 = &allocated_matrix[27*size*size];
        double *temp10 = &allocated_matrix[28*size*size];

        //Distributing the A and B matrices into the submatrices, if the matrix is divisible by 2
        if(rest == 0){
            for(int i = 0; i<size; i++){
                for(int j = 0; j<size; j++){
                    A11[i*size+j] = A[i*orig_size+j];
                    A12[i*size+j] = A[i*orig_size+j+size];
                    A21[i*size+j] = A[(i+size)*orig_size+j];
                    A22[i*size+j] = A[(i+size)*orig_size+j+size];

                    B11[i*size+j] = B[i*orig_size+j];
                    B12[i*size+j] = B[i*orig_size+j+size];
                    B21[i*size+j] = B[(i+size)*orig_size+j];
                    B22[i*size+j] = B[(i+size)*orig_size+j+size];
                }
            }
        }

        /*If the matrix is not divisible by 2, the first to second to last rows and columns are transfered from the A and B matrix
        and the last row and column is determined by which sub matrix it is, for example the last row and column of A22 will be zeroes.
        */
       else{
            for(int i = 0; i<(size-1); i++){
                for(int j = 0; j<(size-1); j++){
                    A11[i*size+j] = A[i*orig_size+j];
                    A12[i*size+j] = A[i*orig_size+j+size];
                    A21[i*size+j] = A[(i+size)*orig_size+j];
                    A22[i*size+j] = A[(i+size)*orig_size+j+size];

                    B11[i*size+j] = B[i*orig_size+j];
                    B12[i*size+j] = B[i*orig_size+j+size];
                    B21[i*size+j] = B[(i+size)*orig_size+j];
                    B22[i*size+j] = B[(i+size)*orig_size+j+size];
                }

                //The last rows and columns are either taken from A or B, or is padded with zeros, depending on the submatrix
                A11[i*size+size-1] = A[i*orig_size+size-1];
                A11[(size-1)*size+i] = A[(size-1)*orig_size+i];
                A12[i*size+size-1] = 0;
                A12[(size-1)*size+i] = A[(size-1)*orig_size+i+size];
                A21[i*size+size-1] = A[(i+size)*orig_size+size-1];
                A21[(size-1)*size+i] = 0;
                A22[i*size+size-1] = 0;
                A22[(size-1)*size+i] = 0; 

                B11[i*size+size-1] = B[i*orig_size+size-1];
                B11[(size-1)*size+i] = B[(size-1)*orig_size+i];
                B12[i*size+size-1] = 0;
                B12[(size-1)*size+i] = B[(size-1)*orig_size+i+size];
                B21[i*size+size-1] = B[(i+size)*orig_size+size-1];
                B21[(size-1)*size+i] = 0;
                B22[i*size+size-1] = 0;
                B22[(size-1)*size+i] = 0; 
            }
            //The last row and column, only A11 and B11 has non-zero values taken from A and B respectively
            A11[(size-1)*size+size-1] = A[(size-1)*orig_size+size-1];
            A12[(size-1)*size+size-1] = 0;
            A21[(size-1)*size+size-1] = 0;
            A22[(size-1)*size+size-1] = 0;

            B11[(size-1)*size+size-1] = B[(size-1)*orig_size+size-1];
            B12[(size-1)*size+size-1] = 0;
            B21[(size-1)*size+size-1] = 0;
            B22[(size-1)*size+size-1] = 0;
       }


        /*Calculating M1 = (A11+A22)*(B11+B22) by first saving the addition in the two temp matrices and then recusively performing Strassen's 
        algorithm for the multiplication*/
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp1[i*size+j] = A11[i*size+j] + A22[i*size+j];
                temp2[i*size+j] = B11[i*size+j] + B22[i*size+j];
            }
        }                   
        strassen_mult(temp1, temp2, M1, size);

        //Calculating M2 = (A21+A22)*B11
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp3[i*size+j] = A21[i*size+j] + A22[i*size+j];
            }
        }                   
        strassen_mult(temp3, B11, M2, size);

        //Calculating M3 = A11*(B12-B22)
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp4[i*size+j] = B12[i*size+j] - B22[i*size+j];
            }
        }                   
        strassen_mult(A11, temp4, M3, size);

        //Calculating M4 = A22*(B21-B11)
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp5[i*size+j] = B21[i*size+j] - B11[i*size+j];
            }
        }                   
        strassen_mult(A22, temp5, M4, size);

        //Calculating M5 = (A11+A12)*B22
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp6[i*size+j] = A11[i*size+j] + A12[i*size+j];
            }
        }                   
        strassen_mult(temp6, B22, M5, size);

        //Calculating M6 = (A21-A11)*(B11+B12)
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp7[i*size+j] = A21[i*size+j] - A11[i*size+j];
                temp8[i*size+j] = B11[i*size+j] + B12[i*size+j];
            }
        }                   
        strassen_mult(temp7, temp8, M6, size);

        //Calculating M7 = (A12-A22)*(B21+B22)
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                temp9[i*size+j] = A12[i*size+j] - A22[i*size+j];
                temp10[i*size+j] = B21[i*size+j] + B22[i*size+j];
            }
        }                   
        strassen_mult(temp9, temp10, M7, size);

        //Calculating C11 = M1 + M4 - M5 + M7
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C11[i*size+j] = M1[i*size+j] + M4[i*size+j] - M5[i*size+j] + M7[i*size+j];
            }
        }                   

        //Calculating C12 = M3 + M5
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C12[i*size+j] = M3[i*size+j] + M5[i*size+j];
            }
        }                   

        //Calculating C21 = M2 + M4
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C21[i*size+j] = M2[i*size+j] + M4[i*size+j];
            }
        }                   

        //Calculating C22 = M1 - M2 + M3 + M6
        for(int i = 0; i<size; i++){
            for(int j = 0; j<size; j++){
                C22[i*size+j] = M1[i*size+j] - M2[i*size+j] + M3[i*size+j] + M6[i*size+j];
            }
        }                   

        //Merging the C submatrices into C, if C was divisible by 2
        if(rest == 0){
            for(int i = 0; i<size; i++){
                for(int j = 0; j<size; j++){
                    C[i*orig_size+j] = C11[i*size+j];
                    C[i*orig_size+j+size] = C12[i*size+j];
                    C[(i+size)*orig_size+j] = C21[i*size+j];
                    C[(i+size)*orig_size+j+size] = C22[i*size+j];
                }
            }
        }

        //Otherwise, the padded zeroes has to be removed
        else{
            for(int i = 0; i<(size-1); i++){
                for(int j = 0; j<(size-1); j++){
                    C[i*orig_size+j] = C11[i*size+j];
                    C[i*orig_size+j+size] = C12[i*size+j];
                    C[(i+size)*orig_size+j] = C21[i*size+j];
                    C[(i+size)*orig_size+j+size] = C22[i*size+j];
                }
                C[i*orig_size+size-1] = C11[i*size+size-1];
                C[(size-1)*orig_size+i] = C11[(size-1)*size+i];
                C[(size-1)*orig_size+i+size] = C12[(size-1)*size+i];
                C[(i+size)*orig_size+size-1] = C21[i*size+size-1];
            }
            C[(size-1)*orig_size+size-1] = C11[(size-1)*size+size-1];
        }


        //Freeing the used memory
        free(allocated_matrix);
    }
}


int main(const char argc, char* argv[]){
    if(argc != 3){
        printf("input the filename for the file containing the A and B matrices to be multiplied and the resulting output file where the C matrix is stored.\n");
        return -1;
    }

    //The input filename
    char filename[60];
    strcpy(filename, argv[1]);

    //The output filename
    char outname[60];
    strcpy(outname, argv[2]);

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

    double *A = (double*)malloc(size*size*sizeof(double));
    double *B = (double*)malloc(size*size*sizeof(double));
    double *C = (double*)malloc(size*size*sizeof(double));

    //Importing the A and B matrices from the file

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            read_res = fread(&A[i*size+j], sizeof(double), 1, input);
        }
    }

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            read_res = fread(&B[i*size+j], sizeof(double), 1, input);
        }
    }
    fclose(input);


    //TEST
/*     printf("A = \n");
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%lf ", A[i*size+j]);
        }
        printf("\n");
    }

    printf("B = \n");
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%lf ", B[i*size+j]);
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
            fwrite(&C[i*size+j], sizeof(double), 1, output);
        }
    }
    fclose(output);
/*     printf("C = \n");
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%lf ", C[i*size+j]);
        }
        printf("\n");
    } */


//Freeing the matrices
    free(A);
    free(B);
    free(C);



    return 0;
}