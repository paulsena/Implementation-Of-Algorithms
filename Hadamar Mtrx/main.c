// Paul Senatillaka
// Excursions in CS
// Assignment 1: Generating Hadamar Matrices
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int *matrix[], int size);
void generateHadamar(int *matrix[], int size, int pos_i, int pos_j, int sign);

int main(int argc, char *argv[])
{
    int size = atoi(argv[3]);
    int **matrix;
    int i;

    /* Dynamically allocate space for a two dimensional array of ints with error checking */
    matrix = (int **)malloc(sizeof (int *) * size);

    for(i = 0; i < size; i++) {
        if (matrix == NULL || (matrix[i] = (int *)malloc(sizeof(int) * size)) == NULL) {
            printf("Memory allocation for matrix failed. Aborting..");
            return 1;
        }
    }

    printf("Generating Hadamar Matrix with Size: %d\n", size);

    generateHadamar(matrix,size,0,0,1);
    printMatrix(matrix,size);


    // Free memory of matrix
    for(i = 0; i < size; i ++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

void printMatrix(int *matrix[],int size)
{
    int i,j;

    //Outer Row Loop
    for (i=0; i<size; i++)
    {
        //Inner Column Loop
        for (j=0; j<size; j++)
        {
            if (matrix[i][j] > 0) {
                printf(" %d ", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        //Row carriage return
    }
        printf("\n");

}

void generateHadamar(int *matrix[], int size, int pos_i, int pos_j, int sign)
{
    if (size == 2)
    {
        matrix[pos_i]   [pos_j]     = 1 * sign;
        matrix[pos_i]   [pos_j+1]   = 1 * sign;
        matrix[pos_i+1] [pos_j]     = 1 * sign;
        matrix[pos_i+1] [pos_j+1]   = -1 * sign;

    }
    else
    {
        generateHadamar(matrix, size/2, pos_i, pos_j, sign);
        generateHadamar(matrix, size/2, pos_i, pos_j + size/2, sign);
        generateHadamar(matrix, size/2, pos_i + size/2, pos_j, sign);
        generateHadamar(matrix, size/2, pos_i + size/2, pos_j + size/2, sign * -1);
    }
}
