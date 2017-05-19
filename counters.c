/* 
 * counter.c - CS50 'counter' module
 *
 * see counter.h for more information.
 *
 * Anders Bando-Hess, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "counters.h"
#include "memory.h"

/**************** local types ****************/
typedef struct countertreenode {
  const int *key;		           			// search key for this item
  int *count;		           			// pointer to data for this item
  struct countertreenode *left, *right;   // children
} countertreenode_t;

/**************** global types ****************/
typedef struct counterTree {
  struct countertreenode *root;                     // root of the tree
} counters_t;

/**************** local functions ****************/
static countertreenode_t *countertreenode_new(const int key);
static countertreenode_t *counters_add_helper(countertreenode_t *node, const int key);
static void counters_print_helper(counters_t *ctrs, countertreenode_t *node, int depth, FILE *fp);
static void counters_delete_helper(counters_t *ctrs, countertreenode_t *node);
static int counters_get_helper(countertreenode_t *node, const int key);
static void counters_set_helper(countertreenode_t *node, const int key, const int count);
static void counters_iterate_helper(countertreenode_t *node, void *arg, 
									void (*itemfunc)(void *arg, const int key, int count)	);

/**************** tree_new() ****************/
counters_t *
counters_new(void)
{
	counters_t *counterTree = count_malloc(sizeof(counters_t));

	if (counterTree == NULL) return NULL;	// error allocating tree
	// initialize contents of tree structure
	else {
		counterTree->root = NULL;
    	return counterTree;
	}
}

/**************** setnode_new() ****************/
/* Allocate and initialize a setnode */
static countertreenode_t *
countertreenode_new(const int key)
{
	countertreenode_t *node = count_malloc(sizeof(countertreenode_t));
	if (node == NULL) return NULL; //error allocating memory for node
    // create new node to store key/count pair
	else {
		int *k = count_malloc(sizeof(int));
		*k = key;
		node->key = k;
		int *j = count_malloc(sizeof(int));
    	*j = 1;
		node->count = j;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

/**************** counters_add() ****************/
void 
counters_add(counters_t *ctrs, const int key)
{
    // if key and counter are valid, insert at root and recurse down
	if (ctrs != NULL && key >= 0) {
		if (ctrs != NULL) {
			ctrs->root = counters_add_helper(ctrs->root, key);
		}
	}
}

/**************** counters_add_helper() ****************/
static countertreenode_t *
counters_add_helper(countertreenode_t *node, const int key)
{
	// if tree is empty create and return a new node
	if (node == NULL){
		return countertreenode_new(key);
	}
	// else if key already exists, increment counter
	else if (key == *node->key) {
		*node->count += 1;
		return node;
	}
	// else recursively insert right or left
	else {
		if (key < *node->key) node->left = counters_add_helper(node->left, key);
		else node->right = counters_add_helper(node->right, key);
	}
	return node;
}

/**************** counters_get() ****************/
int 
counters_get(counters_t *ctrs, const int key)
{	
	int found = 0;
	if (ctrs == NULL) return found;
	else return counters_get_helper(ctrs->root, key);
}	

/**************** counters_get_helper() ****************/
static int
counters_get_helper(countertreenode_t *node, const int key)
{
	// if we couldn't find it return 0
	if (node == NULL) return 0;
	// if we find the correct ket, return its count
	else if (*node->key == key) return *node->key;
	// otherwise continue the search
	else {
		if (key < *node->key) return counters_get_helper(node->left, key);
		else return counters_get_helper(node->right, key);
	}
}

/**************** counters_set() ****************/
void 
counters_set(counters_t *ctrs, const int key, int count)
{
	if (ctrs != NULL && key >= 0) {
		counters_set_helper(ctrs->root, key, count);
	}
}

/**************** counters_set_helper() ****************/
static void 
counters_set_helper(countertreenode_t *node, const int key, const int count)
{	
	// if we've found the correct node
	if (*node->key == key) {
		//free old count
		count_free(node->count);
		//allocate new count
		int *j = count_malloc(sizeof(int));
    	*j = count;
		node->count = j;
		return;
	}
	// keep searching
	else {
		if (key < *node->key) counters_set_helper(node->left, key, count);
		else counters_set_helper(node->right, key, count);
	}
}

/**************** counters_iterate() ****************/
void 
counters_iterate(counters_t *ctrs, void *arg, 
                      void (*itemfunc)(void *arg, const int key, int count))
{
	if (ctrs != NULL) {
		counters_iterate_helper(ctrs->root, arg, (*itemfunc));
	}
}

/**************** counters_iterate_helper() ****************/
static void
counters_iterate_helper(countertreenode_t *node, void *arg, 
									void (*itemfunc)(void *arg, const int key, int count)	)
{
	if (itemfunc != NULL) {
		if (node != NULL) {
			// iterate down left side of tree
			counters_iterate_helper(node->left, arg, (*itemfunc));
			// perform operation on node
			(*itemfunc)(arg, *node->key, *node->count);
			//iterate down right side of tree
			counters_iterate_helper(node->right, arg, (*itemfunc));
		}
		return;
	}
}

/**************** counters_print() ****************/
void 
counters_print(counters_t *ctrs, FILE *fp)
{
	if (fp != NULL) {
		if (ctrs == NULL) fprintf(fp, "(null)");
		else {
			counters_print_helper(ctrs, ctrs->root, 0, fp);
		}
	}
}

/**************** counters_print_helper() ****************/
static void
counters_print_helper(counters_t *ctrs, countertreenode_t *node, int depth, FILE *fp)
{
	if (node != NULL) {
		// print the left subtree
		counters_print_helper(ctrs, node->left, depth + 1, fp);
		//print the current node
		//fprintf(fp, "%*s", depth+1, " ");	//indent one space per depth
		fprintf(fp, "(%d:%d)", *node->key, *node->count);

		//print the right subtree
		counters_print_helper(ctrs, node->right, depth + 1, fp);
	}
	return;
}

/**************** counters_delete() ****************/
void 
counters_delete(counters_t *ctrs)
{
	if (ctrs != NULL) {
		counters_delete_helper(ctrs, ctrs->root);
	}
	count_free(ctrs);

	#ifdef TESTING
		count_report(stdout, "End of tree_delete");
	#endif
}

/**************** counters_delete_helper() ****************/
static void
counters_delete_helper(counters_t *ctrs, countertreenode_t *node)
{
	if (node != NULL) {
		// delete left subtree
		counters_delete_helper(ctrs, node->left);
		// delete right subtree
		counters_delete_helper(ctrs, node->right);
		//delete current node
		free((int*)node->key);
		free(node->count);
		free(node);
	}
	return;
}
