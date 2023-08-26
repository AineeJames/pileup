#ifndef LOG_H
#define LOG_H

typedef enum { INFO, WARNING, ERROR } LogLevel;

void pulog(LogLevel level, const char *msg, const char *file,
           const int line_number);

#ifdef PULOG_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

#define LOG(level, msg) pulog(level, msg, __FILE__, __LINE__)

void pulog(LogLevel level, const char *msg, const char *file,
           const int line_number) {
  printf("%s:%d: ", file, line_number);
  switch (level) {
  case INFO:
    printf("INFO: %s...\n", msg);
    break;
  case WARNING:
    printf("WARNING: %s.\n", msg);
    break;
  case ERROR:
    printf("ERROR: %s!\n", msg);
    exit(-1);
    break;
  default:
    __builtin_unreachable();
  }
}

#endif

#endif // !LOG_H
