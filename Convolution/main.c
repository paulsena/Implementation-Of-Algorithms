/* 
 * HW 4: Convolution of two polynomials
 * Author: Paul Senatillaka
 *
 * Created on February 2, 2010, 9:34 PM
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    // Define and initialize polynomial arrays
    // Note must leave at least half of the array with 0 padding
    const int SIZE = 6;
    int poly1[SIZE] = {1,1,1,0,0,0};
    int poly2[SIZE] = {1,1,1,0,0,0};
    int result[SIZE];
    int i,j,k;

    // Init result array to 0's
    for (i=0; i < SIZE; i++) result[i] = 0;

    // Main work loops
    for (k=0; k < SIZE; k++)
    {
        j = 0;
        for (i=0; i < SIZE; i++)
        {
            result[k] += poly1[i] * poly2[(i>=j?i-j:)];
            j++;
        }
    }
    
    
    return (EXIT_SUCCESS);
}

