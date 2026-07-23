#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_token(Lexer *lexer, Token type);
void handle_identifier(Lexer *lexer);
const char *token_type_name(Token type);
void print_token(const TokenData *token);

static char advance(Lexer *lexer) {
    return *lexer->current_token++;
}

static char peek(const Lexer *lexer) {
    return *lexer->current_token;
}

static char peek_next(const Lexer *lexer) {
    if (*lexer->current_token == '\0') {
        return '\0';
    }
    return lexer->current_token[1];
}

int lex(Lexer *lexer) {
    while (peek(lexer) != '\0') {
        lexer->start_token = lexer->current_token;

        char c = advance(lexer);

        switch (c) {
            case ' ':
            case '\t':
            case '\r':
                break;

            case '\n':
                lexer->line_number++;
                lexer->line_start = lexer->current_token;
                break;

            case '(':
                add_token(lexer, TOKEN_LEFT_PAREN);
                break;

            case ')':
                add_token(lexer, TOKEN_RIGHT_PAREN);
                break;

            case '+':
                add_token(lexer, TOKEN_PLUS);
                break;

            case '-':
                add_token(lexer, TOKEN_MINUS);
                break;

            case '*':
                add_token(lexer, TOKEN_STAR);
                break;

            case '/':
                if (peek(lexer) == '/') {
                    while (peek(lexer) != '\n' &&
                           peek(lexer) != '\0') {
                        advance(lexer);
                    }
                } else {
                    add_token(lexer, TOKEN_SLASH);
                }
                break;

            default:
                if (isdigit((unsigned char)c)) {
                    while (isdigit(
                        (unsigned char)peek(lexer))) {
                        advance(lexer);
                    }

                    add_token(lexer, TOKEN_NUMBER);
                } else {
                    fprintf(
                        stderr,
                        "%zu:%zu: unknown character '%c'\n",
                        lexer->line_number,
                        (size_t)(lexer->start_token -
                                 lexer->line_start),
                        c
                    );

                    return 1;
                }
                break;
        }
    }

    lexer->start_token = lexer->current_token;
    add_token(lexer, TOKEN_EOF);
    return 0;
}

void add_token(Lexer *lexer, Token type) {
    if (lexer->token_count == lexer->capacity) {
        size_t new_capacity = lexer->capacity == 0 ? 8 : lexer->capacity * 2;
        TokenData *new_tokens = realloc(lexer->tokens, new_capacity * sizeof(*new_tokens));

        if (new_tokens == NULL) {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }

        lexer->tokens = new_tokens;
        lexer->capacity = new_capacity;
    }

    TokenData *token = &lexer->tokens[lexer->token_count++];

    token->type = type;
    token->start = lexer->start_token;
    token->length = (size_t)(lexer->current_token - lexer->start_token);
    token->location.line = lexer->line_number;
    token->location.column = (size_t)(lexer->start_token - lexer->line_start);
}

//void handle_identifier(Lexer *lexer) {
//    char *string_start = lexer->current_token;
//
//    while (isalnum(*lexer->current_token)) lexer->current_token++;
//
//    int string_length = lexer->current_token - string_start;
//    char *identifier = (char *)malloc(string_length + 1);
//
//    strncpy(identifier, string_start, string_length);
//    identifier[string_length] = '\0';
//}

void free_lexer(Lexer *lexer) {
    free(lexer->tokens);
}

const char *token_type_name(Token type)
{
    switch (type) {
        case TOKEN_NUMBER:      return "TOKEN_NUMBER";
        case TOKEN_PLUS:        return "TOKEN_PLUS";
        case TOKEN_MINUS:       return "TOKEN_MINUS";
        case TOKEN_STAR:        return "TOKEN_STAR";
        case TOKEN_SLASH:       return "TOKEN_SLASH";
        case TOKEN_LEFT_PAREN:  return "TOKEN_LEFT_PAREN";
        case TOKEN_RIGHT_PAREN: return "TOKEN_RIGHT_PAREN";
        case TOKEN_EOF:         return "TOKEN_EOF";
        case TOKEN_ERROR:       return "TOKEN_ERROR";
    }

    return "TOKEN_UNKNOWN";
}

void print_token(const TokenData *token)
{
    printf(
        "%zu:%zu %-20s '%.*s'\n",
        token->location.line,
        token->location.column,
        token_type_name(token->type),
        (int)token->length,
        token->start
    );
}
