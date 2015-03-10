/* 
 * Paul Senatillaka
 * Excursions in CS
 * Tromino Tiling
 */

#include <stdio.h>
#include <stdlib.h>


void printTiles(char **tiles, int size);
void TrominoTile(char **tiles, int size, int x, int y, int x_Missing, int y_Missing);

char tileChar = '!';

int main(int argc, char** argv) {

    //int N = atoi(argv[1]);
    int size = 8;
    char **tiles;
    tiles =  malloc(sizeof (char *) * size);
    int i, j;

    // Dynamically allocate space for a two dimensional array of ints
    for (i = 0; i < size; i++) {
        tiles[i] = (char *) malloc(sizeof (char) * size);
    }

    // Fill board with 0s
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            tiles[i][j] = '0';
        }
    }

    //Test Tile
    tiles[size/2-1][size/2-1] = ' ';
    
    
    TrominoTile(tiles, size,0,0,4,3);


    printTiles(tiles, size);


    return (EXIT_SUCCESS);
}


void printTiles(char **tiles, int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf(" %c", tiles[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void TrominoTile(char **tiles, int size, int x, int y, int x_Missing, int y_Missing) {
		
		

		if ( size == 2 ) {
			// Fill remaining 3 tiles
		}
		else {
			tileChar++;
			// Place starter tiles
			
			
			//Missing is in top half
			if (x_Missing < size/2) {
			
				//First Quadrant
				if (y_Missing >= size/2) {
				
					tiles[x + size/2-1][y + size/2-1] = tileChar; // Upper Left
					tiles[x + size/2][y + size/2-1] = tileChar; // Lower Left
					tiles[x + size/2][y + size/2] = tileChar;	// Lower Right
					
					TrominoTile(tiles, size/2,x,y,x_Missing,y_Missing); // Upper Left
					TrominoTile(tiles, size/2,x,y+size/2,size/2-1,size/2); // Upper Right
					TrominoTile(tiles, size/2,x+size/2,y,size/2,size/2-1);	// Lower Left
    			TrominoTile(tiles, size/2,x+size/2,y+size/2,size/2,size/2);	// Lower Right
    			
				}
				//Second Quandrant
				else {
				
					tiles[x + size/2-1][y + size/2] = tileChar; // Upper Right
					tiles[x + size/2][y + size/2-1] = tileChar; // Lower Left
					tiles[x + size/2][y + size/2] = tileChar;	// Lower Right
					
					TrominoTile(tiles, size/2,0,0,size/2-1,size/2); // Upper Right
					TrominoTile(tiles, size/2,0,0,x_Missing,y_Missing); // Upper Left
					TrominoTile(tiles, size/2,0,0,size/2,size/2-1);	// Lower Left
    			TrominoTile(tiles, size/2,0,0,size/2,size/2);	// Lower Right
				}
			
			}
			//bottom half
			else {
			
				//Third Quad
				if (y_Missing < size/2) {
				
					tiles[x + size/2-1][y + size/2] = tileChar; // Upper Right
					tiles[x + size/2-1][y + size/2-1] = tileChar; // Upper Left
					tiles[x + size/2][y + size/2] = tileChar;	// Lower Right
					
					TrominoTile(tiles, size/2,x+size/2,y+size/,size/2-1,size/2); // Upper Right
					TrominoTile(tiles, size/2,x+,0,size/2-1,size/2-1); // Upper Left
					TrominoTile(tiles, size/2,0,0,x_Missing,y_Missing);	// Lower Left
    			TrominoTile(tiles, size/2,0,0,size/2,size/2);	// Lower Right
				}
				//Fourth Quad
				else {
				
					tiles[x + size/2-1][y + size/2] = tileChar; // Upper Right
					tiles[x + size/2-1][y + size/2-1] = tileChar; // Upper Left
					tiles[x + size/2][y + size/2-1] = tileChar; // Lower Left
					
					TrominoTile(tiles, size/2,0,0,size/2-1,size/2); // Upper Right
					TrominoTile(tiles, size/2,0,0,size/2-1,size/2-1); // Upper Left
					TrominoTile(tiles, size/2,0,0,size/2,size/2-1);	// Lower Left
    			TrominoTile(tiles, size/2,0,0,x_Missing,x_Missing);	// Lower Right
				}
			
			}
			
    	
    }
    
    
}



