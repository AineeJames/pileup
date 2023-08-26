#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 4000

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
} PileupState;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Please provide a pu file\n");
    exit(-1);
  }
  const char *filename = argv[1];
  FILE *in_file = fopen(filename, "r"); // read only
  if (!in_file) // equivalent to saying if ( in_file == NULL )
  {
    printf("oops, file can't be read\n");
    exit(-1);
  }

  uint8_t strmax;
  char line[100];
  int line_no = 0;
  char *next_token;
  char *token;
  const char *delim = " ";
  while (fgets(line, 100, in_file) != NULL) {
    printf("The line %d is: %s", line_no, line);
    token = strtok_r(line, delim, &next_token);
    while(token) {
        puts(token);
        token = strtok_r(NULL, delim, &next_token);
    }
    line_no++;
  }

  return 0;
}
