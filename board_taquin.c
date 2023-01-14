#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

#define MAX_VECTOR 4

typedef struct {
 int x,y;
} Point;

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
	int i;
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

double get_simple_heuristic(Item *node) { 
  char target[MAX_BOARD] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  int i,n=0;
  for(i=0; i<MAX_BOARD; i++){
    if(node->board[i] != target[i])
      n++;
  }
  return n;
}

// cherche la position d'une case pos
int getPos(Item *node, int pos){
  int i;

  for(i=0; i<MAX_BOARD; i++){
    if(node->board[i] == pos)
      return i;
  }
  return -1;
}

double get_Manhattan_heuristic(Item *node) {
  Point i, f; // coordonnées pour le calcul de Manhattan
  int pos_i, pos_f; // position actuelle de la case et position finale
  int j;
  int res =0;

  for(j=0; j<MAX_BOARD; j++){
    pos_i = getPos(node, j); //cherche la position actuelle de la case étudiée
    pos_f = (j-1)%MAX_BOARD; // et sa position finale
    
    if(pos_i != pos_f){ // calcul coordonnées
      i.x = pos_i/WH_BOARD;
      i.y = pos_i%WH_BOARD;
      f.x = pos_f/WH_BOARD;
      f.y = pos_f%WH_BOARD;

      res = res + abs(f.x - i.x) + abs(f.y - i.y); //calcul de la fonction de Manhattan
    }
  }
  return res;
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

    // allocate and init child node 
    child_p = nodeAlloc();
    initBoard(child_p, node->board);

    // Make move
    child_p->board[node->blank] = child_p->board[pos];
    child_p->board[pos] = 0;
    child_p->blank = pos;
    //printBoard(child_p);
    
    child_p->depth = node->depth +1 ;
    
    //Cost calculation
    child_p->g = child_p->depth;
    child_p->h = get_Manhattan_heuristic(child_p);
    child_p->f = child_p->h + child_p->g;
    
		// link child to parent for backtrack 
    child_p->parent = node;

  }

  return child_p;
} 