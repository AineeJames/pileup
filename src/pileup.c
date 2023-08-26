#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PULOG_IMPLEMENTATION
#include "pulog.h"

#define STACK_CAPACITY 4000
#define TOKEN_CAPACITY 100000
#define LOOP_CAPACITY 1000
#define MAX_LOOPS 10000

#define FOREACH_TOKEN(TOKEN)                                                   \
  TOKEN(PUSH_INT)                                                              \
  TOKEN(PLUS)                                                                  \
  TOKEN(MINUS)                                                                 \
  TOKEN(PRINT)                                                                 \
  TOKEN(DUMP_STACK)                                                            \
  TOKEN(LINE_END)                                                              \
  TOKEN(LOOPSTART)                                                             \
  TOKEN(CURLY_START)                                                           \
  TOKEN(CURLY_END)                                                             \
  TOKEN(DUPE2)                                                             \
  TOKEN(DUPE)                                                             \
  TOKEN(TOKEN_COUNT)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum { FOREACH_TOKEN(GENERATE_ENUM) } TokenType;

static const char *TOKEN_STRING[] = {FOREACH_TOKEN(GENERATE_STRING)};

typedef union {
  int64_t i;
} TokenValue;

typedef struct {
  TokenType type;
  TokenValue value;
  int line_number;
} Token;

typedef struct {
  int start_index;
  int end_index;
  int loop_count;
} Loop;

typedef struct {
  int64_t stack[STACK_CAPACITY];
  int stack_index;
  Token tokens[TOKEN_CAPACITY];
  Loop loops[LOOP_CAPACITY];
  int loop_index;
  int token_index;
  char filename[100];
} PileupState;

void print_usage(const char *prgm);

PileupState init_state(char *filename) {
  PileupState state;
  state.stack_index = 0;
  state.token_index = 0;
  state.loop_index = 0;
  strcpy(state.filename, filename);
  return state;
}

void removeChar(char *str, char c) {
  int i, j;
  int len = strlen(str);
  for (i = j = 0; i < len; i++) {
    if (str[i] != c) {
      str[j++] = str[i];
    }
  }
  str[j] = '\0';
}

bool is_num(char *string) {
  if (string == NULL) {
    return false;
  }
  char *next;
  long val = strtol(string, &next, 10);

  // Check for empty string and characters left after conversion.

  if (next == string || (*next != '\0')) {
    return false;
  } else {
    return true;
  }
}

Token Get_Token(PileupState *state, char *string, int line_number) {
  // TODO might destroy newline in string literal
  removeChar(string, '\n');
  bool is_number = is_num(string);
  Token token;
  if (is_number) {
    token.type = PUSH_INT;
    token.value.i = atoi(string);
  } else if (strcmp(string, "+") == 0) {
    token.type = PLUS;
  } else if (strcmp(string, "-") == 0) {
    token.type = MINUS;
  } else if (strcmp(string, "print") == 0) {
    token.type = PRINT;
  } else if (strcmp(string, "dumps") == 0) {
    token.type = DUMP_STACK;
  } else if (strcmp(string, "loop") == 0) {
    token.type = LOOPSTART;
  } else if (strcmp(string, "{") == 0) {
    token.type = CURLY_START;

  } else if (strcmp(string, "}") == 0) {
    token.type = CURLY_END;
  } else if (strcmp(string, "dupe2") == 0){
    token.type = DUPE2;
  } else if (strcmp(string, "dupe") == 0){
    token.type = DUPE;
  }

  else {
    printf("%s:%d: ERROR: word '%s' not recognized!\n", state->filename,
           line_number, string);
    exit(-1);
  }
  token.line_number = line_number;
  return token;
}

void Print_All_Tokens(PileupState state) {
  for (int i = 0; i < state.token_index; i++) {
    printf("%s:%d %s token_index = %d: ", state.filename,
           state.tokens[i].line_number, TOKEN_STRING[state.tokens[i].type], i);
    if (state.tokens[i].type == PUSH_INT)
      printf("%d\n", (int)state.tokens[i].value.i);
    else
      printf("\n");
  }
}

int8_t Add_Loop(PileupState *state, int loop_start, int loop_end) {
  printf("creating loop\n");
  Print_All_Tokens(*state);
  // check if there is a loop that matches
  for (int i = 0; i < state->loop_index; i++) {
    // TODO  this will exploded if curlys on same line
    if (state->loops[i].start_index == loop_start) {
      // found a loop that already exists
      return -1;
    }
  }
  state->loops[state->loop_index].start_index = loop_start;
  state->loops[state->loop_index].end_index = loop_end;
  state->loops[state->loop_index].loop_count = 0;
  state->loop_index++;
  printf("found loop correctly made starting at %d ending at %d\n", loop_start,
         loop_end);
  return 0;
}

void Add_Token(PileupState *state, Token token) {
  state->tokens[state->token_index] = token;
  state->token_index++;
  if (token.type == CURLY_END) {
    int loop_end = state->token_index - 1;
    for (int i = loop_end; i > 0; i--) {
      if (state->tokens[i].type == CURLY_START){
        int8_t err = Add_Loop(state, i, loop_end);
        if(!err){
            break;
        }
      }
    }
  }
}



void Print_Stack(PileupState *state) {
  for (int i = 0; i < state->stack_index; i++) {
    printf("Stack index %d = %d\n", i, (int)state->stack[i]);
  }
  printf("\n");
}

Loop *Find_Loop(PileupState *state,int end_index){
  for (int i = 0; i < state->loop_index; i++) {
    // TODO  this will exploded if curlys on same line
    if (state->loops[i].end_index == end_index) {
      // found a loop that already exists
      return &state->loops[i];
    }
  }
  return NULL;
}

int8_t Run_Token(PileupState *state) {
  Token cur_token = state->tokens[state->token_index - 1];
  printf("running token %s\n", TOKEN_STRING[state->tokens[state->token_index-1].type]);
  if (cur_token.type == PUSH_INT) {
    state->stack[state->stack_index] = cur_token.value.i;
    state->stack_index++;
  } else if (cur_token.type == PLUS) {
    // pop off top two nums
    if (state->stack_index < 1)
      LOG(ERROR, "Less than two numbers on stack in plus");
    state->stack_index--;
    int firstnum = state->stack[state->stack_index];
    state->stack_index--;
    int secondnum = state->stack[state->stack_index];
    state->stack[state->stack_index] = firstnum + secondnum;
    state->stack_index++;
  } else if (cur_token.type == MINUS) {
    // pop off top two nums
    // TODO add line number for error
    if (state->stack_index < 1)
      LOG(ERROR, "Less than two numbers on stack in minus");
    state->stack_index--;
    int firstnum = state->stack[state->stack_index];
    state->stack_index--;
    int secondnum = state->stack[state->stack_index];
    state->stack[state->stack_index] = secondnum - firstnum;
    state->stack_index++;
  } else if (cur_token.type == PRINT) {
    state->stack_index--;
    int top_stack_int = state->stack[state->stack_index];
    printf("%d\n", top_stack_int);
  } else if (cur_token.type == DUMP_STACK) {
    Print_Stack(state);
  } else if (cur_token.type == CURLY_END) {
    Loop* loop = Find_Loop(state,state->token_index-1);
    if(loop != NULL){ 
        printf("found loop\n");
        state->token_index = loop->start_index+2;
        loop->loop_count++;
        while(Run_Token(state) && loop->loop_count < MAX_LOOPS){
            state->token_index++;
        }
    }
  } else if (cur_token.type == DUPE2) {
    state->stack[state->stack_index] = state->stack[state->stack_index-2];
    state->stack[state->stack_index+1] = state->stack[state->stack_index-1];
    state->stack_index += 2;
  } else if (cur_token.type == DUPE) {
    state->stack[state->stack_index] = state->stack[state->stack_index-1];
    state->stack_index++;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    LOG(ERROR, "no input file provided");
  }
  char *filename = argv[1];
  FILE *in_file = fopen(filename, "r"); // read only
  if (!in_file) // equivalent to saying if ( in_file == NULL )
    LOG(ERROR, "input file can't be read");
  PileupState state = init_state(filename);

  uint8_t strmax;
  char line[100];
  int line_no = 0;
  char *next_token;
  char *token;
  const char *delim = " ";
  Token cur_token;
  while (fgets(line, 100, in_file) != NULL) {
    token = strtok_r(line, delim, &next_token);
    cur_token = Get_Token(&state, token, line_no);
    Add_Token(&state, cur_token);
    Run_Token(&state);
    while (token) {
      token = strtok_r(NULL, delim, &next_token);
      if (token == NULL) {
        break;
      }
      cur_token = Get_Token(&state, token, line_no);
      Add_Token(&state, cur_token);
      Run_Token(&state);
    }
    line_no++;
  }
  Print_All_Tokens(state);
  Print_Stack(&state);

  return 0;
}

void print_usage(const char *prgm) { printf("Usage: %s <input_file>\n", prgm); }
