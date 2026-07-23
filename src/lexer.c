#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_token(Lexer *lexer, Token type, char *val);
void handle_identifier(Lexer *lexer);

int lex(Lexer *lexer) {
  while (*lexer->current_token != '\0') {
    //printf("Current token: %c\n", *lexer->current_token);
    switch (*lexer->current_token) {
      case ' ':
        break;
      case '\n':
        lexer->line_number++;
        lexer->line_start = lexer->current_token + 1;
        break;
      case '(':
        add_token(lexer, TOKEN_LEFT_PAREN, "(");
        fprintf(stdout, "TOKEN_LEFT_PAREN\n");
        break;
      case ')':
        add_token(lexer, TOKEN_RIGHT_PAREN, "(");
        fprintf(stdout, "TOKEN_RIGHT_PAREN\n");
        break;
      case '+':
        add_token(lexer, TOKEN_PLUS, "+");
        fprintf(stdout, "TOKEN_PLUS\n");
        break;
      case '-':
        add_token(lexer, TOKEN_MINUS, "-");
        fprintf(stdout, "TOKEN_MINUS\n");
        break;
      case '*':
        add_token(lexer, TOKEN_STAR, "*");
        fprintf(stdout, "TOKEN_STAR\n");
        break;
      case '/':
        if (*(lexer->current_token + 1) == '/') {
          while (*lexer->current_token != '\n') lexer->current_token++;
          continue;
        } else {
          add_token(lexer, TOKEN_SLASH, "/");
          fprintf(stdout, "TOKEN_SLASH\n");
        }
        break;
      default:
        if (isdigit(*lexer->current_token)) {
          char *string_start = lexer->current_token;

          while (isdigit(*lexer->current_token)) lexer->current_token++;

          int string_length = lexer->current_token - string_start;
          char *number = (char *)malloc(string_length + 1);

          strncpy(number, string_start, string_length);
          number[string_length] = '\0';

          add_token(lexer, TOKEN_NUMBER, number);
          fprintf(stdout, "TOKEN_NUMBER: %c\n", *number);
          continue;
        } else {
          fprintf(stderr, "Unknown token: %c\n", *lexer->current_token);
          return 1;
        }
        break;
    }

    // Advance token
    lexer->current_token++;
  }

  add_token(lexer, TOKEN_EOF, NULL);
  return 0;
}

void add_token(Lexer *lexer, Token type, char *value) {
  if (lexer->token_count == lexer->capacity) {
    size_t new_capacity = lexer->capacity == 0 ? 8 : lexer->capacity * 2;
    lexer->tokens = (TokenData *)realloc(lexer->tokens, new_capacity * sizeof(TokenData));
    if (!lexer->tokens) {
      perror("Error reallocating memory");
      exit(1);
    }

    lexer->capacity = new_capacity;
  }

  lexer->tokens[lexer->token_count].type = type;
  lexer->tokens[lexer->token_count].value = value;
  lexer->tokens[lexer->token_count].location.line = lexer->line_number;
  lexer->tokens[lexer->token_count].location.column = lexer->current_token - lexer->line_start;
  lexer->token_count++;
}

//void handle_identifier(Lexer *lexer) {
//  char *string_start = lexer->current_token;
//
//  while (isalnum(*lexer->current_token)) lexer->current_token++;
//
//  int string_length = lexer->current_token - string_start;
//  char *identifier = (char *)malloc(string_length + 1);
//
//  strncpy(identifier, string_start, string_length);
//  identifier[string_length] = '\0';
//
//}

void free_lexer(Lexer *lexer) {
  for (size_t i = 0; i < lexer->token_count; i++) {
    if(lexer->tokens[i].type == TOKEN_NUMBER) {
      free(lexer->tokens[i].value);
    }
  }
  free(lexer->tokens);
}
