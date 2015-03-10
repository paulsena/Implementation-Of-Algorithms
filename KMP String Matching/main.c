/**********************************************************
* Paul Senatillaka		Date: 3/24/10												*
* 91.350: Excursions in CS																*			
* Assignment: Knuth-Morris-Pratt String Matching					*
* 																												*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void kmpSetup (char P[], int m, int fail[]);
int kmpScan (char P[], char T[], int m, int fail[]);

int main(int argc, char *argv[])
{

	char Pattern[20] = " World";
	char Text[20] = " Hello World";
	int fail[6];
	int m = strlen(Pattern) - 1;	// - 1 due to 0 base

	printf ("\nSearch Pattern: %s \n", Pattern);
	printf ("Search String: %s \n", Text);

	kmpSetup ( Pattern, m, fail );
	printf ("Position Found: %d \n", 	kmpScan ( Pattern, Text, m, fail ) );

	return 0;
}

void kmpSetup (char P[], int m, int fail[])
{
	int k, s;
	fail[1] = 0;
	
	for (k = 2; k <= m; k++ ) {
		
			s = fail[k-1];
			while ( s >= 1 ) {
			
				if ( P[s] == P[k-1] ) { break; }
				
				s = fail[s];
			
			}
	
			fail[k] = s + 1;
	}

}

int kmpScan ( char P[], char T[], int m, int fail[] )
{
	int match = -1;
	int j = 1, 	// Indexes text characters
			k = 1;	// Indexes the pattern and fail array
	int numComparisons = 0;
	
	while ( T[j-1] != '\0' ) {
	
		if ( k > m ) {
			match = j - m;	// Match found
			break;
		}
		
		if ( k == 0 ){
			j++;
			k = 1;					// Start pattern over		
		}
		
		else if (numComparisons++ && T[j] == P[k] ) {
			j++;
			k++;
		}
		
		else {
			// Follow fail arrow
			k = fail[k];
		}
	
	}
	
	printf("Number of Comparisons: %d \n", numComparisons);
	
	return match;
}


