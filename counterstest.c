/* 
 * counterstest.c - test program for CS50 counters module
 *
 * usage:
 *   track frequencies of integer keys
 *
 *   tets functionality of methods outlined in counters.h
 *
 * Anders Bando-Hess, 2017
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "readlinep.h"


//prototypes
static void highcounts(void *arg, const int key, int count);

int main(int argc, char const *argv[]) 
{
	counters_t *counterTree;
	counterTree = counters_new();

  if (counterTree == NULL) {
    fprintf(stderr, "counters_new failed\n");
    exit(1);
  }

  printf("adding nodes...\n");
  counters_add(counterTree, 5);
  counters_add(counterTree, 5);
  counters_add(counterTree, 5);
  counters_add(counterTree, 3);
  counters_add(counterTree, 4);
  counters_add(counterTree, 5);
  counters_add(counterTree, 2);
  counters_add(counterTree, 2);
  counters_add(counterTree, 1);
  counters_add(counterTree, 9);
  counters_add(counterTree, 2);
  counters_add(counterTree, 2);
  counters_add(counterTree, 1);
  counters_add(counterTree, 9);
  counters_add(counterTree, 2);
  counters_add(counterTree, 2);
  counters_add(counterTree, 1);
  counters_add(counterTree, 9);
  counters_add(counterTree, 2);
  counters_add(counterTree, 1);
  counters_add(counterTree, 9);
  counters_add(counterTree, 2);
  counters_add(counterTree, 2);
  counters_add(counterTree, 1);
  counters_add(counterTree, 9);


  printf("printing counter...\n");
  counters_print(counterTree, stdout);

  printf("\nfinding 5s; we should find four of them...\n");
  int fives = counters_get(counterTree, 5);
  printf("we have found %d fives\n", fives);

  printf("attempting to set count of fives to 1000...\n");
  counters_set(counterTree, 5, 1000);
  printf("reprinting tree...\n");
  counters_print(counterTree, stdout);

  printf("\nattempting to increment count of threes...\n");
  counters_add(counterTree, 3);
  printf("reprinting tree...\n");
  counters_print(counterTree, stdout);

  printf("\ntesting counters_iterate...should print all numbers with counts greater than 5\n");
  int *num = malloc(sizeof(int));
  *num = 5;
  counters_iterate(counterTree, num, highcounts);

	printf("\ndeleting counters...\n");
	counters_delete(counterTree);
  free(num);
}

//test function for set_iterate
//if count of a node is greater than arg, print "holy moly, item with key: [key] has a high count"
static void 
highcounts(void *arg, const int key, int count)
{
  int *i = arg;
  if (count > *i) fprintf(stdout, "holy moly, item with key:%d has a high count of %d!\n", key, count);
}