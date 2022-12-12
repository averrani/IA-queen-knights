#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"


// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame()
{
  int i;
  Item *node;

	char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
	for (int i=0; i<MAX_BOARD; i++) initial[i] = 0;
      node = nodeAlloc();

	initBoard(node, initial);
  
  node->depth = 0;
  node->f = 0;
  node->board[0] =1; 

  return node;
}

// print a board
void printBoard( Item *node )
{
  assert(node);
	printf("\n");
	for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
	for (int i = 0 ; i < MAX_BOARD ; i++) {
    if (i%WH_BOARD == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WH_BOARD) == 0) {
			printf("\n");
			for (int j=0; j<WH_BOARD; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
		}
  }
	printf("\n");
}


// initialize node's state from a given board
void initBoard(Item *node, char *board) {
	assert( node );
	int i=0;
	node->size = MAX_BOARD;
    node->board = calloc(MAX_BOARD, sizeof(char));
  
  // copy board

  for(i=0; i<MAX_BOARD; i++){
    node->board[i] = board[i];
  }

}

// Return 0 if all queens are placed. Positive otherwise
// ie: nb queens that still need to be placed.
double evaluateBoard(Item *node) {
  /*
  int pos =0;
  while(node->board[pos] == 0){
      pos++;
    }
  int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;

  int i = WH_BOARD - ii -1;
  int j = WH_BOARD - jj -1;

  return j+i;
  */
  if(node->board[MAX_BOARD-1] == 1)
        return 0 ; 
    else
        return 1 ;
}

// Test if position pos is valid with respect to node's state
// n  Queens -> not same row ; not same column ; not same diagonal
int isValidPosition( Item *node, int pos )
{
  int i;
  int j;
  int p;
	int ii = pos / WH_BOARD;
	int jj = pos % WH_BOARD;

  //on cherche le cavalier dans le board
  for (i=0; i<WH_BOARD; i++) {
    for (j=0; j<WH_BOARD; j++) {
      // on verifie si il peut se deplacer a pos
      if(node->board[i*WH_BOARD+j] == 1){
          if((((abs(i-ii) == 1 )&& (abs(j-jj) == 2))) || (((abs(i-ii) == 2) && (abs(j-jj) == 1 ))))
            return 1; 
          else
            return 0;
    }
  }
  }
  
}

// Return a new item where a new queen is added at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int pos )
{
  Item *child_p = NULL;
  int i=0;
  if ( isValidPosition(node, pos) ) {

    /* allocate and init child node */
    child_p = nodeAlloc();

    initBoard(child_p, node->board);
    /* Make move */
    while(child_p->board[i] == 0){
      i++;
    }
    child_p->board[i] = 0;
    child_p->board[pos] = 1;
    child_p->depth = node->depth +1 ;
    child_p->f = node->f + 1;
    
		/* link child to parent for backtrack */
    child_p->parent = node;

  }

  return child_p;
}
