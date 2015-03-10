/**********************************************************
* Paul Senatillaka		Date: 3/22/10												*
* 91.350: Excursions in CS																*			
* Assignment: Straightforward String Matching							*
* Modified Alg from handout to be 0 based and implements  *
* backup var in an easier manner													*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simpleScan(char P[], char T[], int m);

int main(int argc, char *argv[])
{
	char Pattern[20] = "World";
	char Text[20] = "Hello World";
	
	printf ("\nSearch Pattern: %s \n", Pattern);
	printf ("Search String: %s \n", Text);

	printf ("Position Found: %d \n", simpleScan(Pattern, Text, strlen(Pattern)) );
	
	
	return 0;
}

/*	Straight forward search function
		P - Search Pattern String
		T - Search Text String
 		m	-	Search Pattern String Size  */
int simpleScan(char P[], char T[], int m)
{
	
	// Initialize
	int match = -1; 			// Return value
	int backupStart = 0;
	int numComparisons = 0;
	int i = 1,						// i is the current guess at where P begins in T	
			j = 0,						// j is the index of the current character in T
			k = 0;						// k is the index of the current character in P
			
			
	while ( T[j] != '\0') {
		
		// If End of Pattern. Matched
		if ( k >= m  ) {
				
			match = i;	// Match found
			break;
		}
				
		// If Chars compare, Advance Strings
		if ( T[j] == P[k] ) { j++;	k++; }
		
		else {
			// Start at beggining of P. Start T at next index (backStart)
						
			j = backupStart;	k = 0;
			i = j + 1;
			
			backupStart++;	
		}
		
		numComparisons++;
		
	}
	printf ("Number of Char Comparisons: %d\n", numComparisons);
	
	return match;
}
