#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

/* Item Functions */

Item *nodeAlloc()
{
  Item *node;

  node = (Item *) malloc( sizeof(Item) );
  assert(node);

  node->board = NULL;
  node->parent = NULL;
  node->prev = NULL;
  node->next = NULL;
  node->f = node->g = node->h = (double)0.0;

  return node;
}

void freeItem( Item *node )
{
  if (node && node->board) free(node->board);
	if (node) free(node);
}


void initList( list_t *list_p )
{
  //if (list_p == NULL) list_p = malloc(sizeof(list_t));
	assert(list_p);

  list_p->numElements = 0;
  list_p->first = NULL;
  list_p->last = NULL;
}

int listCount( list_t *list )
{
	return list->numElements;
}

// return an item with corresponding board , or null
Item* onList( list_t *list, char *board)
{
	int j;

    assert(list);  assert(board);
	Item *cur = list->first;
	while (cur) {
        for (j = 0 ; j < cur->size ; j++) {
    	    if (cur->board[j] != board[j]) break;
        }
        if (j == cur->size) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// return and remove first item
Item *popFirst( list_t *list ) //
{
  /*
	Item *item = list->first;
  list->first = list->first->next;
  list->first->prev = NULL;
  list->numElements--;
	return item;
  */
  Item *item = NULL;
	if (list->first) {
		item = list->first;
		list->first = item->next;
		if (list->first) list->first->prev = NULL;
		else list->last = NULL;
		item->next = NULL;
		item->prev = NULL;
		list->numElements--;
	}
	return item;
}

// return and remove last item
Item *popLast( list_t *list ) //
{
	Item *item = list->last;
  list->last = list->last->prev;
  list->last->next = NULL;
  list->numElements--;
	return item;
}

// remove a node from list
void delList( list_t *list, Item *node) {
    assert( node );
	// remove
    if (node->prev) {
        node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
    } else {
        assert( node == list->first );
        if (node->next) {
            list->first = node->next;
            if (list->first) list->first->prev = NULL;
        }
    }
    if (node->next == NULL) {
        assert( node == list->last );
        list->last = node->prev;
    }
	node->next = node->prev = NULL;
    list->numElements--;
	if (list->numElements == 0) {
		list->first = NULL;
		list->last = NULL;
	}
  
}

// return and remove best item with minimal f value
Item *popBest(list_t *list) // and remove the best board from the list.
{
  Item *tmp = list->first;
  Item *value;
  float best;

  if (list->numElements == 0)
  {
    value = NULL;
  }
  else
  {
    value = list->first;
    best = value->f;
    tmp = tmp->next;
    while (tmp)
    {         
            if (tmp->f < best)
            {
              best = tmp->f;
              value = tmp;
            }
            tmp = tmp->next;
    }
    delList(list, value);
  }
  return value;
}

 // add item in top
void addFirst( list_t *list, Item *node ) // add in head
{
  if(listCount(list) == 0){
    list->first = node;
    list->last = node;
    list->numElements++;
  }else {
    list->first->prev = node;
    node->next = list->first;
    node->prev = NULL;
    list->first = node;
    list->numElements++;
  }
}

 // add item in queue
void addLast( list_t *list, Item *node ) // add in tail
{
  if(listCount(list) ==0){
    list->first = node;
    list->last = node;
    list->numElements++;
  }else {
    list->last->next = node;
    node->prev = list->last;
    node->next = NULL;
    list->last = node;
    list->numElements++;
  }
}

void cleanupList( list_t *list )
{
  while(listCount(list) != 0 ){
    Item * tmp = list->first;
    list->first = list->first->next;
    freeItem(tmp);
    list->numElements--;
  }
  list->first = NULL;
  list->last = NULL;
}

void printList( list_t list ) {

	Item *item = list.first;
  while (item) {
    printf("%.2f [%s] - ", item->f, item->board);
    item = item->next;
  }
  printf(" (nb_items: %d)\n", list.numElements);

}


// TEST LIST
/*
int main()
{
  Item *item;
  char str[3];

  list_t openList;
  
  initList( &openList );

  for (int i=0; i<10; i++) {
    item = nodeAlloc();
    item->f = i;
    item->size = 3;
    sprintf(str, "%2d", i);
    item->board = strdup(str);
    addLast( &openList, item );
  }
  
  for (int i=20; i<25; i++) {
    item = nodeAlloc();
    item->f = i;
    item->size = 3;
    sprintf(str, "%2d", i);
    item->board = strdup(str);
    addFirst( &openList, item );
  }	
  
  printList(openList);
  printf("\n");

  
  Item *node = popBest( &openList );
  
  printf("best node = %.2f\n", node->f);
  
  printList(openList);
  printf("\n");

  strcpy(str, "23");
  node = onList(&openList, str);
  if (node) printf("found %s: %.2f!\n", str, node->f); 
  printList(openList);
  printf("\n");

  node = popFirst(&openList);
	
  item = nodeAlloc();
  item->f = 50;
  item->size = 3;
  sprintf(str, "50");
  item->board = strdup(str);
  addLast( &openList, item );

  node = popFirst(&openList);
  if (node) printf("first: %.2f\n", node->f); 
  printList(openList);
  printf("\n");

  node = popLast(&openList);
  if (node) printf("last: %.2f\n", node->f); 
  printList(openList);
  printf("\n");

  printf("clean\n");	
  cleanupList(&openList);
  printList(openList);
  printf("\n");
  
  return 0;
}

*/