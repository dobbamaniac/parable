#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenKind;

typedef struct {
    size_t  line;
    size_t  column;
} Location;

typedef struct {
    TokenKind   kind;       // Kind of the token
    const char  *start;     // Start of the token
    size_t      length;     // Length of the token
    Location    location;   // Location of the token
} Token;

typedef struct {
    char        *start_token;
    char        *current_token;
    Token       *tokens;
    size_t      line_number;
    char        *line_start;
    size_t      token_count;
    size_t      capacity;
} Lexer;

Lexer *init_lexer(Lexer *lexer, char *buffer);

int lex(Lexer *lexer);

void free_lexer(Lexer *lexer);

const char *token_type_name(TokenKind token);

void print_token(const Token *token);

#endif
