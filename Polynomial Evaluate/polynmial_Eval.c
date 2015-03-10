/**********************************************************
* Paul Senatillaka		Date: 2/2/10												*
* 91.350: Excursions in CS																*			
* Assignment 3b: Polynomial Evaluate											*
* Function to eval a polynomial for given x								*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float evalPoly(float* a, int n, float x);

void printVector(float* vector, int size)
{
    int i;

    for (i=0; i < size; i++) printf( " %f\n", vector[i]);
}

int main(int argc, char *argv[])
{
	// Create test data
	float poly[3] = {1,1,1}; 	// Polynomial equivalent to 1x^2 + 1x + 1
	float x = 2; 							// Eval poly when x = 2
	
	printVector(poly, 3);

	printf ("Poly evaled at %f = %f\n", x, evalPoly(poly, 3, x));

	return 0;
}

float evalPoly(float* poly, int polySize, float x)
{
	float result, xpower;
	int i;

	result = poly[0];
	xpower = 1;

	for ( i = 1; i < polySize; i++ ) {
		xpower = xpower * x;
		result += poly[i] * xpower;
	}
	
	return result;
}

