#include <stdio.h>
#include "branchsim.c"


int main() {

	void *p = createAndInitialize(16);
	
	//printf("Branch originally is: %d\n", accessBranchPredictor(p, 11));
	updateBranchPredictor(p, 0, 1);
	//printf("Branch 1 is: %d\n", accessBranchPredictor(p, 12));
	updateBranchPredictor(p, 4, 1);
	//printf("Branch 2 is: %d\n", accessBranchPredictor(p, 12));
	updateBranchPredictor(p, 8, 1);
	//printf("Branch 3 is: %d\n", accessBranchPredictor(p, 12));
	updateBranchPredictor(p, 12, 1);
	updateBranchPredictor(p, 16, 1);
	updateBranchPredictor(p, 20, 1);
	int j = numAccesses(p);
	printf("NumAccesses is: %d\n", j);
	return 0;
	
}
