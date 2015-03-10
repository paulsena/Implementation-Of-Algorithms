/**********************************************************
* Paul Senatillaka		Date: 3/22/10												*
* 91.350: Excursions in CS																*			
* Assignment: Straightforward String Matching							*
* 																												*
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simpleScan(char P[], char T[], int m);

int main(int argc, char *argv[])
{
	char Pattern[20] = " World";
	char Text[20] = " Hello World";

	printf ("%d \n", simpleScan(Pattern, Text, 5) );
	
	
	return 0;
}

/*	Straight forward search function
		P - Search Pattern String
		T - Search Text String
 		m	-	Search Pattern String Size  */
int simpleScan(char P[], char T[], int m)
{
	
	// Declare
	int match; 	// Return value
	int backupStart;
	int i,			// i is the current guess at where P begins in T	
			j,			// j is the index of the current character in T
			k;			// k is the index of the current character in P
			
	// Initialize
	match = -1;
	backupStart = 1;
	j = 1;	k = 1;
	i = 1;
	
	while ( T[j-1] != '\0') {
		
		// If End of Pattern. Matched
		if ( k > m  ) {
				
			match = i;	// Match found
			break;
		}
				
		// If Chars compare, Advance Strings
		if ( T[j] == P[k] ) { j++;	k++; }
		
		else {
			// Start at beggining of P. Start T at next index (backStart)
			backupStart++;			
			j = backupStart;	k = 1;
			i = j;
						
		}
		
		
	}
	
	return match;
}
