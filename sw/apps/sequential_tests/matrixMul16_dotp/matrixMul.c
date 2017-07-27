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

#include "bench.h"
#include "utils.h"
#include "bar.h"
#include "timer.h"
#include "string_lib.h"

#include "dotMatrixMul16_stimuli.h"

void check_matrix_mul          (testresult_t *result, void (*start)(), void (*stop)());
void check_matrix_mul_dotp     (testresult_t *result, void (*start)(), void (*stop)());

void __attribute__ ((noinline)) matMul16(signed short * __restrict__ A, signed short * __restrict__ B, signed int * __restrict__ C, int N , int M);
void __attribute__ ((noinline)) matMul16_t_dot(signed short * __restrict__ A, signed short * __restrict__ B, signed int * __restrict__ C, int N , int M);

void __attribute__ ((noinline)) matrix_init(signed short * __restrict__ A, signed short * __restrict__ B, signed int * __restrict__ C);
unsigned int __attribute__ ((noinline)) matrix_check(signed int * __restrict__ C);


testcase_t testcases[] = {
  { .name = "matrixMul16"     , .test = check_matrix_mul      },
#ifdef USE_VEC
  { .name = "matrixMulDotp16" , .test = check_matrix_mul_dotp },
#endif
  {0, 0}
};

int main() {
  run_suite(testcases);
  return 0;
}


void check_matrix_mul(testresult_t *result, void (*start)(), void (*stop)()) {
  
  int N = SIZE;
  int M = SIZE;
  
  signed short matA[N*M];
  signed short matB[N*M];
  signed int  matC[N*M];

  matrix_init(matA,matB,matC);

  // start benchmark
  start();

  matMul16(matA, matB, matC, N, M);
  
  stop();

  result->errors = matrix_check(matC);
}

#ifdef USE_VEC
void check_matrix_mul_dotp(testresult_t *result, void (*start)(), void (*stop)()) {

  int N = SIZE;
  int M = SIZE;

  signed short matA[N*M];
  signed short matB[N*M];
  signed int  matC[N*M];

  matrix_init(matA, matB, matC);

  // start benchmark
  start();

  matMul16_t_dot(matA, matB, matC, N, M);
  
  stop();

  result->errors = matrix_check(matC);
}
#endif

// helper functions
void __attribute__ ((noinline)) matrix_init(signed short * __restrict__ A, signed short * __restrict__ B, signed int * __restrict__ C) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      A[i*SIZE+j] = m_a[i * SIZE + j];
      B[i*SIZE+j] = m_b[i * SIZE + j];
      C[i*SIZE+j] = 0;
    }
  }
}

unsigned int __attribute__ ((noinline)) matrix_check(signed int * __restrict__ C) {
  unsigned int errors = 0;
  // check
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (C[i*SIZE+j] != m_exp[i * SIZE + j]) {
        printf("At index %d, %d\n", i, j);
        errors++;
      }
    }
  }
  return errors;
}