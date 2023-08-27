#ifndef LOG_H
#define LOG_H

typedef enum { DEBUG, WARNING, ERROR } LogLevel;

void pulog(LogLevel level, const char *msg, const char *file,
           const int line_number, ...);

void set_loglevel(LogLevel level);

#ifdef PULOG_IMPLEMENTATION

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define LOG(level, msg, ...) pulog(level, msg, __FILE__, __LINE__, __VA_ARGS__)

static LogLevel LOG_LEVEL = DEBUG;

void set_loglevel(LogLevel level) { LOG_LEVEL = level; }

void pulog(LogLevel level, const char *msg, const char *file,
           const int line_number, ...) {
  if (level == DEBUG && LOG_LEVEL <= DEBUG) {
    printf("\033[0;34mDEBUG: ");
  } else if (level == WARNING && LOG_LEVEL <= WARNING) {
    printf("\033[1;33mWARNING: ");
  } else if (level == ERROR && LOG_LEVEL <= ERROR) {
    printf("\033[1;31mERROR: ");
  } else {
    return;
  }
  printf("\033[0m");

  printf("%s:%d: ", file, line_number);

  va_list args;
  va_start(args, line_number);
  vprintf(msg, args);
  va_end(args);

  if (level == DEBUG) {
    printf("...\n");
  } else if (level == WARNING) {
    printf(".\n");
  } else if (level == ERROR) {
    printf("!\n");
    exit(-1);
  }
}

#endif

#endif // !LOG_H
