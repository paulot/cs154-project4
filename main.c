#include <stdio.h>
#include "branchsim.c"


int main() {

	void *p = createAndInitialize(16);
	
	//printf("Branch originally is: %d\n", accessBranchPredictor(p, 11));
  int test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no  
	updateBranchPredictor(p, 0, 1);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no 
  updateBranchPredictor(p, 0, 1);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no
  updateBranchPredictor(p, 0, 1);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no 
  updateBranchPredictor(p, 0, 0);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no
  updateBranchPredictor(p, 0, 0);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no 
  updateBranchPredictor(p, 0, 0);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no
  updateBranchPredictor(p, 0, 1);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no 
  updateBranchPredictor(p, 0, 1);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no
  updateBranchPredictor(p, 0, 0);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no 
  updateBranchPredictor(p, 0, 0);
  test = accessBranchPredictor(p, 0);
  printf("predict? %d\n", test); //no
  updateBranchPredictor(p, 0, 1);

	int j = numAccesses(p);
  int m = numMispredictions(p);
	printf("NumAccesses is: %d\n", j);
  printf("mispredictions: %d\n", m);
	
  //printf("Branch 1 is: %d\n", accessBranchPredictor(p, 12));
	updateBranchPredictor(p, 30, 1);
	//printf("Branch 2 is: %d\n", accessBranchPredictor(p, 12));
	updateBranchPredictor(p, 8, 1);
	//printf("Branch 3 is: %d\n", accessBranchPredictor(p, 12));
	updateBranchPredictor(p, 12, 1);
	updateBranchPredictor(p, 16, 1);
	updateBranchPredictor(p, 20, 1);
  return 0;
	
}
