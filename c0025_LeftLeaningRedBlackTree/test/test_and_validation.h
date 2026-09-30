#ifndef TEST_VALIDATION
#define TEST_VALIDATION

#include "../include/log.h"
#include <stddef.h>

#define compare(T, E) strcmp(T, E)
#define validate(T, E, ...)                                                    \
  if (compare(T, E) != 0) {                                                    \
    log_e("Test failed, expect value is %s, but get the value %s.", E, T,      \
          ##__VA_ARGS__);                                                      \
  }

typedef enum { TEST_PASSED, TEST_FAILED } TestResult;

// typedef TestResult (*test_function)(void);

typedef struct {
  char *case_name;
  TestResult (*test_function)(void);
  // test_function function_name;
} TestCase;

void run_test_suites(TestCase *, size_t);

#endif // TEST_VALIDATION
