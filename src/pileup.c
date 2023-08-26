#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define STACK_CAPACITY 4000

typedef enum { PUSH_INT, PLUS, PRINT } TokenType;

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
  const char *code = "10 10 + print";
  printf("Code: %s\n", code);

  return 0;
}
