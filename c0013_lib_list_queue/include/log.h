#ifndef LOG_FORMAT
#define LOG_FORMAT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define COLOR_RESET "\033[0m"
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

#define CHARAC 100
// #define paste_charac((x), (y)) (x)##(y)

#define LOG_LEVEL_I "INFO"
#define LOG_LEVEL_D "DEBUG"
#define LOG_LEVEL_W "WARN"
#define LOG_LEVEL_E "ERROR"
#define LOG_LEVEL_F "FATAL"

#define print_seperator(color, x)                                              \
  ({                                                                           \
    for (int i = CHARAC; i > 0; i--) {                                         \
      printf("%s%s", color, x);                                                \
    }                                                                          \
    printf(COLOR_RESET "\n");                                                  \
  })

// define后面用({})将要实现的多行代码写在内部的花括号里面，也是宏定义的一种新写法
#define __current_time__                                                       \
  ({                                                                           \
    time_t timep;                                                              \
    time(&timep);                                                              \
    struct tm *ptr_time;                                                       \
    ptr_time = localtime(&timep);                                              \
    char time_buf[80];                                                         \
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", ptr_time);       \
    time_buf;                                                                  \
  })

// 打印带毫秒的时间
#define __current_millisecond__                                                \
  ({                                                                           \
    struct timeval *time_v = (struct timeval *)malloc(sizeof(struct timeval)); \
    struct tm *ptr_time;                                                       \
    time_t timep;                                                              \
    static char time_buf[80] = "";                                             \
    char str_mil_sec[20] = "";                                                 \
    char str_buf[20] = "";                                                     \
    char *str_time = ".";                                                      \
    time(&timep);                                                              \
    ptr_time = localtime(&timep);                                              \
    gettimeofday(time_v, NULL);                                                \
    int mil_sec = time_v->tv_usec / 1000;                                      \
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", ptr_time);       \
    sprintf(str_mil_sec, "%d", mil_sec);                                       \
    strcat(str_buf, str_time);                                                 \
    strcat(str_buf, str_mil_sec);                                              \
    strcat(time_buf, str_buf);                                                 \
    free(time_v);                                                              \
    time_buf;                                                                  \
  })

// 打印带毫秒的时间，方法二
#define __current_millis_2__                                                   \
  ({                                                                           \
    struct timeval *time_v = (struct timeval *)malloc(sizeof(struct timeval)); \
    gettimeofday(time_v, NULL);                                                \
    struct tm *p_time = localtime(&time_v->tv_sec);                            \
    static char time_buf[32] = "";                                             \
    snprintf(time_buf, sizeof(time_buf), "%02d-%02d-%02d %02d:%02d:%02d.%03d", \
             p_time->tm_year % 100, p_time->tm_mon + 1, p_time->tm_mday,       \
             p_time->tm_hour, p_time->tm_min, p_time->tm_sec,                  \
             (int)(time_v->tv_usec / 1000));                                   \
    free(time_v);                                                              \
    time_buf;                                                                  \
  })

#define log(color, loglevel, fmt, ...)                                         \
  do {                                                                         \
    printf("%s%s %-6s %-10s %-10s:%-5d: " fmt COLOR_RESET "\n", color,         \
           __current_millisecond__, loglevel, __FILE__, __func__, __LINE__,    \
           ##__VA_ARGS__);                                                     \
  } while (0)

#define log_other_way(color, loglevel, fmt, ...)                               \
  do {                                                                         \
    printf("%s%s %-6s %-10s %-10s:%-5d: " fmt COLOR_RESET "\n", color,         \
           __current_millis_2__, loglevel, __FILE__, __func__, __LINE__,       \
           ##__VA_ARGS__);                                                     \
  } while (0)

#define log_i(fmt, ...) log(COLOR_GREEN, LOG_LEVEL_I, fmt, ##__VA_ARGS__)
#define log_d(fmt, ...) log(COLOR_BLUE, LOG_LEVEL_D, fmt, ##__VA_ARGS__)
#define log_w(fmt, ...) log(COLOR_YELLOW, LOG_LEVEL_W, fmt, ##__VA_ARGS__)
#define log_e(fmt, ...) log(COLOR_RED, LOG_LEVEL_E, fmt, ##__VA_ARGS__)
#define log_f(fmt, ...) log(COLOR_MAGENTA, LOG_LEVEL_F, fmt, ##__VA_ARGS__)

#define log_new(fmt, ...)                                                      \
  log_other_way(COLOR_CYAN, LOG_LEVEL_I, fmt, ##__VA_ARGS__)

// 可变参数的新写法，更加简单，不用__VA_ARGS__这个系统宏定义
#define log_t(fmt, args...) log(COLOR_MAGENTA, LOG_LEVEL_I, fmt, args)

#endif
