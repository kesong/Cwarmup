#ifndef LOGGER_FUNC
#define LOGGER_FUNC

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef enum { INFO, DEBUG, WARN, ERROR, FATAL } LOG_LEVEL;

typedef void (*log_function)();

typedef struct {
  LOG_LEVEL log_level;
  log_function log_f;
} LOGGER;

#endif // LOGGER_FUNC
