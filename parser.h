#ifndef PARSER_H
#define PARSER_H

#define MAX_TOKENS 100

//header file for simple expression parser
// This parser can handle basic arithmetic expressions with +, -, *, / operators
// and single-digit operands (0-9). It ignores whitespace and checks for invalid characters.
typedef enum {
    OPERAND,
    OPERATOR
} TokenType;

typedef struct {
    TokenType type;
    char value;
} Token;

int tokenize(const char *expr, Token tokens[], int *tokenCount);
int evalExpressionType(Token tokens[], int tokenCount);

#endif