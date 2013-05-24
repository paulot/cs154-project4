#include <stdlib.h>
#include "branchsim.h"

int NumberOfSetBits(int i) {
  i = i - ((i >> 1) & 0x55555555);
  i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
  return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

void *createAndInitialize(int numEntries) {
  Branch *b = (Branch *) malloc(sizeof(Branch));
  b->table  = (int *) malloc(numEntries * sizeof(int));
  
  b->branchSize = NumberOfSetBits(numEntries - 1); //size of bits for branch = log2(numEntries)

  int i = 0;
  for (i; i < numEntries; i++) {
    b->table[i] = 0; //set all entries in the table to not-taken (0)
  }
  return (void *) b;
}

/*
int accessBranchPredictor(void *bp, int PC) {
  int index = (PC >> bp->bitSize) & 
  if (bp->table[index] == 
}
**/

void updateBranchPredictor(void *bp, int PC, int result) {
  //update entry in the table
}

int numAccess(void *bp) {
  return ((Branch *) bp)->accesses;
}

int numMispredictions(void *bp) {
  return ((Branch *) bp)->mispredictions;
}


