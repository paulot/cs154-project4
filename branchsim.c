#include <stdlib.h>
#include "branchsim.h"

int NumberOfSetBits(int i) {
  i = i - ((i >> 1) & 0x55555555);
  i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
  return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

void *createAndInitialize(int numEntries) {
  Branch *b = (Branch *) malloc(sizeof(Branch));
  b->stateTable  = (int *) malloc(numEntries * sizeof(int));
 
  b->accesses = 0;
  b->mispredictions = 0;

  b->bitSize = NumberOfSetBits(numEntries - 1);
  int i = 0;
  for (i; i < numEntries; i++) {
    b->stateTable[i] = 0; //set all entries in the table to not-taken (0)
  }
  return (void *) b;
}

int accessBranchPredictor(void *bp, int PC) {
  Branch *b = (Branch *) bp;
  
  int index = (PC >> 2) & ~(-1 << b->bitSize);

  if (b->stateTable[index] == 0 || b->stateTable[index] == 1) {
    return 0; //predict taken
  } else {
    return 1; //not
  }
}

void updateBranchPredictor(void *bp, int PC, int result) {
  Branch *b = (Branch *) bp;
 
  accessBranchPredictor(b, PC);
  b->accesses++;
 
  int index = (PC >> 2) & ~(-1 << b->bitSize);
  
  if (result == 0) { // if result is not taken
  	switch (b->stateTable[index]) {
      case 0: // predict not taken
        b->stateTable[index] = 0;
        break;
      case 1: // predict not taken 
        b->stateTable[index] = 0;
        break;
      case 3:
        b->stateTable[index] = 2;
        b->mispredictions++;
        break;
      case 2:
        b->stateTable[index] = 0;
        b->mispredictions++;
        break;
    }
  }
  if (result == 1) {
    switch (b->stateTable[index]) {
      case 0:
        b->stateTable[index] = 1;
        b->mispredictions++;
        break;
      case 1:
        b->stateTable[index] = 3;
        b->mispredictions++;
        break;
      case 3:
        b->stateTable[index] = 3;
        break;
      case 2:
        b->stateTable[index] = 3;
        break;
    }
  }
}

int numAccesses(void *bp) {
  return ((Branch *) bp)->accesses;
}

int numMispredictions(void *bp) {
  return ((Branch *) bp)->mispredictions;
}


