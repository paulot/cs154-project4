typedef struct {
  int *stateTable; //contains small state machine for each entry
  int *predictTable;
  int accesses;
  int mispredictions;
  //int branchSize;
  int bitSize;
} Branch;

void *createAndInitialize(int numEntries);

int accessBranchPredictor(void *bp, int PC);

void updateBranchPredictor(void *bp, int PC, int result); // void *bp is struct returned from createandinitialize

int numAccesses(void *bp);

int numMispredictions(void *bp);
