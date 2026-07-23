#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum token {
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_EOF,
  TOKEN_ERROR
} Token;

typedef struct location {
  size_t  line;
  size_t  column;
} Location;

typedef struct token_data {
  Token     type;       // Type of the token
  char      *value;     // Value of the token
  Location  location;   // Location of the token
} TokenData;

typedef struct lexer {
  char      *start_token;
  char      *current_token;
  TokenData *tokens;
  size_t    line_number;
  char      *line_start;
  size_t    token_count;
  size_t    capacity;
} Lexer;

int lex(Lexer *lexer);

void free_lexer(Lexer *lexer);

char *token_to_string(Token token);

#endif
