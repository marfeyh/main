/*!
 * @File:		unitmain.c
 * @Brief:	main file of the CUnit testing
 * @Author:	Alina Butko
 * @Date:		2011-05-09
 * @Version:	0.1
 * @History:	2011-05-09 create the file
 * @Detail:
 */

#include "CUnit/Basic.h"
#include "test_ca.c"

int main(void) {
  CU_pSuite pSuite1 = NULL;

  /* Initialize CUnit test registry */
  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add suite to the registry */
  pSuite1 = CU_add_suite("Suite 1: Testing filters", init_suite, clean_suite);
  if(NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add tests to suite */
  if(NULL == CU_add_test(pSuite1, "Test case 1: Testing 'dangerzone'", testCase1)
		|| NULL == CU_add_test(pSuite1, "Test case 2: Testing distance filter", testCase2)
		|| NULL == CU_add_test(pSuite1, "Test case 3: Testing ir filter", testCase3)
		|| NULL == CU_add_test(pSuite1, "Test case 4: Testing current direction filter", testCase4)
		|| NULL == CU_add_test(pSuite1, "Test case 5: Testing moving closer filter", testCase5)
		|| NULL == CU_add_test(pSuite1, "Test case 6: Testing final direction", testCase6)
	) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using console interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
