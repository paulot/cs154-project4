typedef struct {
  int *table;
  int accesses;
  int mispredictions;
  int branchSize;
} Branch;

void *createAndInitialize(int numEntries);

int accessBranchPredictor(int numEntries);

void updateBranchPredictor(void *bp, int PC, int result);

int numAccesses(void *bp);

int numMispredictions(void *bp);
