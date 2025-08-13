#include <check.h>
#include <stdlib.h>
#include <stdio.h>

/* External suite declarations */
extern Suite *token_suite(void);
extern Suite *lexer_suite(void);

int main(void)
{
    int number_failed = 0;
    SRunner *sr;
    
    /* Create test runner */
    sr = srunner_create(token_suite());
    
    /* Add additional test suites */
    srunner_add_suite(sr, lexer_suite());
    
    /* Set output to verbose mode */
    srunner_set_log(sr, "test_results.log");
    srunner_set_xml(sr, "test_results.xml");
    
    /* Run all tests */
    printf("Running lexer test suite...\n");
    srunner_run_all(sr, CK_VERBOSE);
    
    /* Get results */
    number_failed = srunner_ntests_failed(sr);
    
    /* Print summary */
    printf("\n=== Test Summary ===\n");
    printf("Tests run: %d\n", srunner_ntests_run(sr));
    printf("Tests passed: %d\n", srunner_ntests_run(sr) - number_failed);
    printf("Tests failed: %d\n", number_failed);
    
    if (number_failed == 0) {
        printf("✅ All tests passed!\n");
    } else {
        printf("❌ %d test(s) failed\n", number_failed);
    }
    
    /* Cleanup */
    srunner_free(sr);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
