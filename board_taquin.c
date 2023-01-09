#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

#define MAX_VECTOR 4

typedef struct {
 int len;
 unsigned int valid[MAX_VECTOR];
} move_t;

const move_t moves[MAX_BOARD] = {
 /* 0 */ { 2, {1, 3} },
 /* 1 */ { 3, {0, 2, 4} },
 /* 2 */ { 2, {1, 5} },
 /* 3 */ { 3, {0, 4, 6} },
 /* 4 */ { 4, {1, 3, 5, 7} },
 /* 5 */ { 3, {2, 4, 8} },
 /* 6 */ { 2, {3, 7} },
 /* 7 */ { 3, {4, 6, 8} },
 /* 8 */ { 2, {5, 7} } 
 };


// Initialize a new Game for the nQueens problem: an empty board..
Item *initGameTaquin(int level)
{
  char easy[MAX_BOARD] = {1, 2, 5, 3, 0, 4, 7, 8, 6};
  char medium[MAX_BOARD] = {7, 4, 8, 2, 5, 6, 3, 1, 0};
  char difficult[MAX_BOARD] = {8, 0, 7, 5, 6, 1, 3, 2, 4};

  int i;
  Item *node;
  node = nodeAlloc();

  switch (level)
  {
  case 0:
    initBoard(node, easy);
    node->blank = 4;
    break;
  case 1:
    initBoard(node, medium);
    node->blank = 8;
    break;
  
  default:
    initBoard(node, difficult);
    node->blank = 1;
    break;
  }
  
  node->depth = 0;

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
  char target[MAX_BOARD] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  int i,n=0;
  for(i=0; i<MAX_BOARD; i++){
    if(node->board[i] != target[i])
      n++;
  }
  return n;
}

//teste si pos est dans le board et si pos correspond au positions valides 
  //selon le tableau moves en fonction du blank courant
int isValidPosition( Item *node, int pos )
{
  int i;
  int b = node->blank;
  
  for(i=0; i<moves[b].len; i++){
    if(pos >= 0 && pos < MAX_BOARD && pos == moves[b].valid[i])
      return 1;
  }
  return 0;
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
