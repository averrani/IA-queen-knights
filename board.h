#include "list.h"

#define RANDINIT()  srand(time(NULL))
#define RANDOM()  ((float)rand() / (float)RAND_MAX)
#define RANDMAX(x)  (int)((float)(x)*rand()/(RAND_MAX+1.0))

#define MAX_BOARD 9 //25
#define WH_BOARD 3 //5



Item *initGame();

Item *initGameTaquin(int level);

void initBoard(Item *node, char *board);

Item *getChildBoard( Item *node, int pos );

double evaluateBoard( Item *node );

int isValidPosition( Item *node, int pos );
	
void printBoard( Item *board );
