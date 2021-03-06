/****************************************************************
 * Paul Senatillaka		Date: 2/22/10                   *
 * 91.350: Excursions in CS                                   	*
 * Assignment: Strassen Matrix Multiply Algorithm               *
 * Multiply two matrixes O(n^2.71) - 7 Multiplys, 18 Additions	*
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef int bool;

//Function Declerations
void printMatrix(int *matrix[], int size);
int **strassenMultiply(int **matrixA, int **matrixB, int size);
int** matrixAddSub(int **matrixA, int **matrixB, int size, bool Add);

int main(int argc, char *argv[]) {
    int **matrixA; // Matrix to multiply
    int **matrixB; // Matrix to multiply
    int **matrixC; // Result matrix

    const int SIZE = 8; // Matrix size;
    int i, j; // Matrix indices;

    // Create orignal matrices to multiply
    // Dynamically allocate space for a two dimensional array of ints with error checking
    matrixA = (int **) malloc(sizeof (int *) * SIZE);
    matrixB = (int **) malloc(sizeof (int *) * SIZE);
    matrixC = (int **) malloc(sizeof (int *) * SIZE);

    for (i = 0; i < SIZE; i++) {
        if (matrixA == NULL || (matrixA[i] = (int *) malloc(sizeof (int) * SIZE)) == NULL) {
            printf("Memory allocation for matrix failed. Aborting..");
            return;
        }
        if (matrixB == NULL || (matrixB[i] = (int *) malloc(sizeof (int) * SIZE)) == NULL) {
            printf("Memory allocation for matrix failed. Aborting..");
            return;
        }
        if (matrixC == NULL || (matrixC[i] = (int *) malloc(sizeof (int) * SIZE)) == NULL) {
            printf("Memory allocation for matrix failed. Aborting..");
            return;
        }
    }

    //Fill matrix with test values
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrixA[i][j] = 1;
            matrixB[i][j] = 1;
        }
    }

    matrixC = strassenMultiply(matrixA, matrixB, SIZE);
    printMatrix(matrixC, SIZE);

    return 0;
}

int ** strassenMultiply(int **matrixA, int **matrixB, int size) {

    int **matrixC; // Result matrix
    int i; // Counter
    bool add = 1;
    bool sub = 0;

    // Dynamically allocate space for a two dimensional array of ints with error checking
    matrixC = (int **) malloc(sizeof (int *) * size);

    for (i = 0; i < size; i++) {
        if (matrixC == NULL || (matrixC[i] = (int *) malloc(sizeof (int) * size)) == NULL) {
            printf("Memory allocation for matrix failed. Aborting..");
            return;
        }
    }

    // Bottom of recursion
    if (size == 2) {

        int m[7];
        m[0] = (matrixA[0][0] + matrixA[1][1]) * (matrixB[0][0] + matrixB[1][1]);
        m[1] = (matrixA[1][0] + matrixA[1][1]) * matrixB[0][0];
        m[2] = (matrixB[0][1] - matrixB[1][1]) * matrixA[0][0];
        m[3] = (matrixB[1][0] - matrixB[0][0]) * matrixA[1][1];
        m[4] = (matrixA[0][0] + matrixA[0][1]) * matrixB[1][1];
        m[5] = (matrixA[1][0] - matrixA[0][0]) * (matrixB[0][0] + matrixB[0][1]);
        m[6] = (matrixA[0][1] - matrixA[1][1]) * (matrixB[1][0] + matrixB[1][1]);

        matrixC[0][0] = m[0] + m[3] - m[4] + m[6];
        matrixC[0][1] = m[2] + m[4];
        matrixC[1][0] = m[1] + m[3];
        matrixC[1][1] = m[0] - m[1] + m[2] + m[5];
    }
    // Divide and conquer
    else {

        // Temp matrix to store operations
        int **matrixA11;
        int **matrixA12;
        int **matrixA21;
        int **matrixA22;

        int **matrixB11;
        int **matrixB12;
        int **matrixB21;
        int **matrixB22;

        size = size / 2; // Reduce size becuase we're splitting into 4 quads.

        int i, j; // Matrix indices

        // Dynamically allocate space for a two dimensional array of ints with error checking
        matrixA11 = (int **) malloc(sizeof (int *) * size);
        matrixA12 = (int **) malloc(sizeof (int *) * size);
        matrixA21 = (int **) malloc(sizeof (int *) * size);
        matrixA22 = (int **) malloc(sizeof (int *) * size);

        matrixB11 = (int **) malloc(sizeof (int *) * size);
        matrixB12 = (int **) malloc(sizeof (int *) * size);
        matrixB21 = (int **) malloc(sizeof (int *) * size);
        matrixB22 = (int **) malloc(sizeof (int *) * size);

        for (i = 0; i < size; i++) {
            matrixA11[i] = (int *) malloc(sizeof (int) * size);
            matrixA12[i] = (int *) malloc(sizeof (int) * size);
            matrixA21[i] = (int *) malloc(sizeof (int) * size);
            matrixA22[i] = (int *) malloc(sizeof (int) * size);

            matrixB11[i] = (int *) malloc(sizeof (int) * size);
            matrixB12[i] = (int *) malloc(sizeof (int) * size);
            matrixB21[i] = (int *) malloc(sizeof (int) * size);
            matrixB22[i] = (int *) malloc(sizeof (int) * size);
        }

        // Copy orign matrix into 4 sub-divided matrices
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                //We use the new size(orig size/2) as an offset here
                matrixA11[i][j] = matrixA[ i ][ j ];
                matrixA12[i][j] = matrixA[ i ][ j + size ];
                matrixA21[i][j] = matrixA[ i + size ][ j ];
                matrixA22[i][j] = matrixA[ i + size ][ j + size ];

                matrixB11[i][j] = matrixB[ i ][ j ];
                matrixB12[i][j] = matrixB[ i ][ j + size ];
                matrixB21[i][j] = matrixB[ i + size ][ j ];
                matrixB22[i][j] = matrixB[ i + size ][ j + size ];
            }
        }

        
        // Define new temp matrices M
        int **matrixM1;
        int **matrixM2;
        int **matrixM3;
        int **matrixM4;
        int **matrixM5;
        int **matrixM6;
        int **matrixM7;
        
        matrixM1 = (int **) malloc(sizeof (int *) * size);
        matrixM2 = (int **) malloc(sizeof (int *) * size);
        matrixM3 = (int **) malloc(sizeof (int *) * size);
        matrixM4 = (int **) malloc(sizeof (int *) * size);
        matrixM5 = (int **) malloc(sizeof (int *) * size);
        matrixM6 = (int **) malloc(sizeof (int *) * size);
        matrixM7 = (int **) malloc(sizeof (int *) * size);

        for (i = 0; i < size; i++) {
            matrixM1[i] = (int *) malloc(sizeof (int) * size);
            matrixM2[i] = (int *) malloc(sizeof (int) * size);
            matrixM3[i] = (int *) malloc(sizeof (int) * size);
            matrixM4[i] = (int *) malloc(sizeof (int) * size);
            matrixM5[i] = (int *) malloc(sizeof (int) * size);
            matrixM6[i] = (int *) malloc(sizeof (int) * size);
            matrixM7[i] = (int *) malloc(sizeof (int) * size);
        }

        
        // Set M matrices      
        matrixM1 = strassenMultiply( matrixAddSub(matrixA11, matrixA22,size,add) , matrixAddSub(matrixB11, matrixB22,size,add), size);
        matrixM2 = strassenMultiply( matrixAddSub(matrixA21, matrixA22,size,add) , matrixB11, size);
        matrixM3 = strassenMultiply( matrixAddSub(matrixB12, matrixB22,size,sub) , matrixA11, size);
        matrixM4 = strassenMultiply( matrixAddSub(matrixB21, matrixB11,size,sub) , matrixA22, size);
        matrixM5 = strassenMultiply( matrixAddSub(matrixA11, matrixA12,size,add) , matrixB22, size);
        matrixM6 = strassenMultiply( matrixAddSub(matrixA21, matrixA11,size,sub) , matrixAddSub(matrixB11, matrixB12,size,add), size);
        matrixM7 = strassenMultiply( matrixAddSub(matrixA12, matrixA22,size,sub) , matrixAddSub(matrixB21, matrixB22,size,add), size);

        
        // Define new temp matrices C
        int **matrixC11;
        int **matrixC12;
        int **matrixC21;
        int **matrixC22;

        matrixC11 = (int **) malloc(sizeof (int *) * size);
        matrixC12 = (int **) malloc(sizeof (int *) * size);
        matrixC21 = (int **) malloc(sizeof (int *) * size);
        matrixC22 = (int **) malloc(sizeof (int *) * size);

        for (i = 0; i < size; i++) {
            matrixC11[i] = (int *) malloc(sizeof (int) * size);
            matrixC12[i] = (int *) malloc(sizeof (int) * size);
            matrixC21[i] = (int *) malloc(sizeof (int) * size);
            matrixC22[i] = (int *) malloc(sizeof (int) * size);
        }

        // Store results into matrix C
        matrixC11 = matrixAddSub ( matrixAddSub( matrixM1,matrixM4,size,add ),  matrixAddSub( matrixM5,matrixM7,size,add ), size,sub);
        matrixC12 = matrixAddSub( matrixM3,matrixM5,size,add );
        matrixC21 = matrixAddSub( matrixM2,matrixM4,size,add );
        matrixC22 = matrixAddSub ( matrixAddSub( matrixM1,matrixM2,size,sub ),  matrixAddSub( matrixM3,matrixM6,size,add ), size,add);

        
        //Recontitute matrixC from smaller matrixC quandrants
        //size is used as an offset here
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                matrixC[ i ][ j ] = matrixC11[ i ][ j ];
                matrixC[ i ][ j+size ] = matrixC12[ i ][ j ];
                matrixC[ i+size ][ j ] = matrixC21[ i ][ j ];
                matrixC[ i+size ][ j+size ] = matrixC22[ i ][ j ];
            }
        }

        //Free memory
        for (i = 0; i < size; i++) {
            free(matrixM1[i]); free(matrixM2[i]); free(matrixM3[i]); free(matrixM4[i]); free(matrixM5[i]); free(matrixM6[i]); free(matrixM7[i]);
            free(matrixA11[i]); free(matrixA12[i]); free(matrixA21[i]); free(matrixA22[i]);
            free(matrixB11[i]); free(matrixB12[i]); free(matrixB21[i]); free(matrixB22[i]);
            free(matrixC11[i]); free(matrixC12[i]); free(matrixC21[i]); free(matrixC22[i]);
        }
        free(matrixM1); free(matrixM2); free(matrixM3); free(matrixM4); free(matrixM5); free(matrixM6); free(matrixM7);
        free(matrixA11); free(matrixA12); free(matrixA21); free(matrixA22);
        free(matrixB11); free(matrixB12); free(matrixB21); free(matrixB22);
        free(matrixC11); free(matrixC12); free(matrixC21); free(matrixC22);

    //end of else
    }

    return matrixC;
}

int** matrixAddSub(int **matrixA, int **matrixB, int size, bool Add) {
    int **matrixC; // Result matrix
    int i, j; // Matrix indices

    // Dynamically allocate space for a two dimensional array of ints with error checking
    matrixC = (int **) malloc(sizeof (int *) * size);

    for (i = 0; i < size; i++) {
        if (matrixC == NULL || (matrixC[i] = (int *) malloc(sizeof (int) * size)) == NULL) {
            printf("Memory allocation for matrix failed. Aborting..");
            return;
        }
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (Add) {
                matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
            } else {
                matrixC[i][j] = matrixA[i][j] - matrixB[i][j];
            }
        }
    }

    return matrixC;
}


void printMatrix(int *matrix[], int size) {
    int i, j;

    //Outer Row Loop
    for (i = 0; i < size; i++) {
        //Inner Column Loop
        for (j = 0; j < size; j++) {
            if (matrix[i][j] > 0) {
                printf(" %d ", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        //Row carriage return
        printf("\n");
    }
}


