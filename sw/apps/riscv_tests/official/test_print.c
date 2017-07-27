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


#include "string_lib.h"
#include "uart.h"
#include "utils.h"

unsigned int g_errors = 0;

void print_okay(const int testnr, const char *testsuite) {
  printf("Test suite OK: %s\n", testsuite);
}

void print_fail(const int testnr, const char *testsuite) {
  g_errors++;
  printf("Test FAIL: %d (suite %s)\n", testnr, testsuite);
}


void print_test_summary()
{

  printf("==== SUMMARY: ");

  if (g_errors == 0) {
    printf("OOOOOOK!!!!!!\n");
  } else {
    printf("NOT OK!!!!!\n");
  }

  uart_wait_tx_done();
  
  // signal end of computation
  eoc(g_errors);
}
