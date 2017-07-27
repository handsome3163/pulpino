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
#ifndef __ML_SVD_H__
#define __ML_SVD_H__

/////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////

// include the shared header for ml kernels
#include "mlShared.h"


/////////////////////////////////////////////////////////
// subfunctions
/////////////////////////////////////////////////////////

void b_eml_xaxpy(int n, float a, const float x[25], int ix0, float y[5], int iy0);
float b_eml_xnrm2(int n, const float x[5], int ix0);
void c_eml_xaxpy(int n, float a, const float x[5], int ix0, float y[25], int iy0);
void eml_xaxpy(int n, float a, int ix0, float y[25], int iy0);
float eml_xdotc(int n, const float x[25], int ix0, const float y[25], int iy0);
void eml_xgesvd(const float A[25], float U[25], float S[5], float V[25]);
float eml_xnrm2(int n, const float x[25], int ix0);
void eml_xrot(float x[25], int ix0, int iy0, float c, float s);
void eml_xrotg(float *a, float *b, float *c, float *s);
void eml_xscal(float a, float x[25], int ix0);
void eml_xswap(float x[25], int ix0, int iy0);

/////////////////////////////////////////////////////////
// main testing function 
/////////////////////////////////////////////////////////
int main(int argc, const char * const argv[]);


#endif

