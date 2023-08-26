#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PULOG_IMPLEMENTATION
#include "pulog.h"

#define STACK_CAPACITY 4000
#define TOKEN_CAPACITY 100000

typedef enum { PUSH_INT, PLUS, PRINT, TOKEN_COUNT } TokenType;

typedef union {
  int64_t i;
} TokenValue;

typedef struct {
  TokenType type;
  TokenValue value;
  int line_number;
} Token;

typedef struct {
  int64_t stack[STACK_CAPACITY];
  int stack_index;
  Token tokens[TOKEN_CAPACITY];
  int token_index;
} PileupState;

void print_usage(const char *prgm);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    LOG(ERROR, "no input file provided");
  }
  const char *filename = argv[1];
  FILE *in_file = fopen(filename, "r"); // read only
  if (!in_file) // equivalent to saying if ( in_file == NULL )
    LOG(ERROR, "input file can't be read");

  uint8_t strmax;
  char line[100];
  int line_no = 0;
  char *next_token;
  char *token;
  const char *delim = " ";
  while (fgets(line, 100, in_file) != NULL) {
    printf("The line %d is: %s", line_no, line);
    token = strtok_r(line, delim, &next_token);
    while (token) {
      puts(token);
      token = strtok_r(NULL, delim, &next_token);
    }
    line_no++;
  }

  return 0;
}

void print_usage(const char *prgm) { printf("Usage: %s <input_file>\n", prgm); }
