/* Copyright (C) 2017 ETH Zurich, University of Bologna
 * All rights reserved.
 *
 * This code is under development and not yet released to the public.
 * Until it is released, the code is under the copyright of ETH Zurich and
 * the University of Bologna, and may contain confidential and/or unpublished
 * work. Any reuse/redistribution is strictly forbidden without written
 * permission from ETH Zurich.
 *
 * Bug fixes and contributions will eventually be released under the
 * SolderPad open hardware license in the context of the PULP platform
 * (http://www.pulp-platform.org), under the copyright of ETH Zurich and the
 * University of Bologna.
 */

#include "utils.h"
#include "string_lib.h"
#include "bench.h"

#define NR_PLATES 12

void ToH(int, char*, char*, char*);

void computeGold(int, char*, char*, char*);

static char A[NR_PLATES];
static char B[NR_PLATES];
static char C[NR_PLATES];

void check(testresult_t *result, void (*start)(), void (*stop)());

testcase_t testcases[] = {
  { .name = "towerofhanoi",   .test = check       },
  {0, 0}
};

int main()
{
  int error = 0;
  if(get_core_id()==0){
    error = run_suite(testcases);
  }
  return error;
}

void check(testresult_t *result, void (*start)(), void (*stop)()) {
  int i,j;
  printf("Start towerofhanoi\n");

  for (i=0;i<NR_PLATES;i++){
      A[i] = i;
      B[i] = 0;
      C[i] = 0;
  }
  start();
  computeGold(NR_PLATES, A, B, C);
  stop();

  for (i=0;i<NR_PLATES;i++) {
    if (B[i] != i) {
      printf("expected: %d, actual: %d\n",i,B[i]);
      result->errors++;
    }
  }
}
void computeGold(int n, char* A, char* B, char* C)
{
  ToH(n-1,A,B,C);
}

void ToH(int n, char* A, char* B, char* C)
{
  if(n==0)
    {
      B[n] = A[n];
      A[n] = 0;
    }
  else {
    ToH(n-1,A,C,B);
    B[n] = A[n];
    A[n] = 0;
    ToH(n-1,C,B,A);
  }
}
