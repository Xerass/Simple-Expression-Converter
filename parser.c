#include "parser.h"
#include <stdio.h>
#include <ctype.h>

int tokenize(const char *expr, Token tokens[], int *tokenCount) {
    int count = 0;
    for (int i = 0; expr[i] != '\0'; ++i) {
        char c = expr[i];

        if (isdigit(c) || isalpha(c)) {
            tokens[count].type = OPERAND;
            tokens[count].value = c;
            count++;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens[count].type = OPERATOR;
            tokens[count].value = c;
            count++;
        }
        else if (c == '(') {
            tokens[count].type = LPAREN;
            tokens[count].value = c;
            count++;
        }
        else if (c == ')') {
            tokens[count].type = RPAREN;
            tokens[count].value = c;
            count++;
        }
        else if (c == ' ') {
            /* skip */
        } else {
            printf("Invalid character: %c\n", c);
            return 0;
        }
    }
    *tokenCount = count;
    return 1;
}


//modified eval to work with parens
int evalExpressionType(Token tokens[], int tokenCount) {
    if (tokenCount == 0) return 0;  // empty

    //Parentheses always imply infix
    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == LPAREN || tokens[i].type == RPAREN)
            return 2;  // infix
    }

    //First token = operator → prefix
    if (tokens[0].type == OPERATOR)
        return 1;

    //Last token = operator → postfix
    if (tokens[tokenCount - 1].type == OPERATOR)
        return 3;

    //Any operator in the middle → infix
    for (int i = 1; i < tokenCount - 1; i++) {
        if (tokens[i].type == OPERATOR)
            return 2;
    }

    // 5) No operators at all?  Treat as “unknown”
    return 0;
}