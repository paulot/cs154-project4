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
  b->predictTable = (int *) malloc(numEntries * sizeof(int));
  
  //b->branchSize = NumberOfSetBits(numEntries - 1); //size of bits for branch = log2(numEntries)
  b->bitSize = numEntries;
  //printf("bitSize is: %d\n", b->bitSize);
  int i = 0;
  for (i; i < numEntries; i++) {
    b->stateTable[i] = 0; //set all entries in the table to not-taken (0)
    b->predictTable[i] = 0;
  }
  return (void *) b;
}


int accessBranchPredictor(void *bp, int PC) {
  ((Branch *) bp)->accesses++;
  int index = (PC>>2) & (((Branch *)bp)->bitSize-1);
  //printf("INDEX IS: %d\n", index);
  return ((Branch *) bp) ->predictTable[index];

}


void updateBranchPredictor(void *bp, int PC, int result) {
  //update entry in the table
  int index = (PC>>2) & (((Branch *)bp)->bitSize-1);
  if (result == 0) { // if result is not taken
  	switch (accessBranchPredictor(bp, PC)) {
  		case 0: // predict not taken
  			if (((Branch *)bp)->stateTable[index] == 3) {
  				((Branch *)bp)->stateTable[index] = 0;
  			}
  			break;
  		case 1: // predict taken
  			((Branch *)bp)->mispredictions++;
  			if (((Branch *)bp)->stateTable[index] == 1) {
  				((Branch *)bp)->stateTable[index] = 2;
  			}
  			else if (((Branch *)bp)->stateTable[index] == 2) {
  				((Branch *)bp)->stateTable[index] = 0;
  				((Branch *)bp)->predictTable[index] = 0;
  			}
  			break;
  	}
  	 
  }
  if (result == 1) { // if result is taken
  	switch (accessBranchPredictor(bp, PC)) {
  		case 0: // predict not taken
  			((Branch *)bp)->mispredictions++;
  			if (((Branch *)bp)->stateTable[index] == 0) {
  				((Branch *)bp)->stateTable[index] = 3;
  			}
  			else if (((Branch *)bp)->stateTable[index] == 3) {
  				((Branch *)bp)->stateTable[index] = 1;
  				((Branch *)bp)->predictTable[index] = 1;
  			}
  			break;
  		case 1: // predict taken
  			if (((Branch *)bp)->stateTable[index] == 2) {
  				((Branch *)bp)->stateTable[index] = 1;
  			}
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


