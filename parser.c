#include "parser.h"
#include <stdio.h>
#include <ctype.h>

int tokenize(const char *expr, Token tokens[], int *tokenCount) {
    int i = 0, count = 0;
    char c;

    //takes in a string expression and tokenizes it
    //iterates over the input string while it is not yet \0
    while ((c = expr[i]) != '\0') {
        //simple checks for valid chars
        if (isdigit(c)) {
            //if it is a digit, it must be an operand
            tokens[count].type = OPERAND;
            tokens[count].value = c;
            count++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            //if it is one of these, it must be an operator
            tokens[count].type = OPERATOR;
            tokens[count].value = c;
            count++;
        } else if (c == ' ') {
            // Skip spaces
        } else {
            printf("Invalid character: %c\n", c);
            return 0;  // Error
        }
        // check if we have reached the maximum number of tokens
        if (count >= MAX_TOKENS) {
            printf("Too many tokens!\n");
            return 0;
        }

        i++;
    }

    *tokenCount = count;
    return 1;  // Success
}

//simply checks the type of notation input is written in
//had no idea why I wrote this lol, i mistook this for an evaluator
//as in 'evaluate'/'identify' the type of expression
//think imma leave it in here though just in case
int evalExpressionType(Token tokens[], int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        
        if (tokens[i].type == OPERATOR)
            return 1;
            
        if (i + 2 < tokenCount && tokens[i].type == OPERAND &&
            tokens[i + 1].type == OPERATOR && tokens[i + 2].type == OPERAND)
            return 2;

        if (tokens[i].type == OPERAND && tokens[i].type == OPERAND)
            return 3;
        
    }
}