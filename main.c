//test area for progmram
#include <stdio.h>
#include "parser.h"
#include "tree.h"

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("For Simple Parser, please input an expression in the command line.\n");
        return 1;
    }
    
    const char *expression = argv[1];
    Token tokens[MAX_TOKENS];
    int tokenCount = 0;

//----------------------FOR DEBBBUGGING---------------------//
    //tokenize the expression and check for errors
    if(tokenize(expression, tokens, &tokenCount)){

        switch(evalExpressionType(tokens, tokenCount)) {
            case 1:
                printf("The input is in prefix notation.\n");
                break;
            case 2:
                printf("The input is in infix notation.\n");
                break;
            case 3:
                printf("The input is in postfix notation.\n");   
                break; 
            default:
                printf("Unknown notation.\n");
                break;
        }

        printf("Tokenization was successful!\n");
        printf("Tokens:\n");

        //print a simple token list
        for(int i = 0; i < tokenCount; i++){
            if (tokens[i].type == OPERAND){
                //print if its an operand
                printf("Operand: %c\n", tokens[i].value);
            } else if (tokens[i].type == OPERATOR){
                //print if its an operator
                printf("Operator: %c\n", tokens[i].value);
            }
        }

        TreeNode *root = buildPostfix(tokens, tokenCount);  //testing for postfix input

        Token result[MAX_TOKENS];
        int index = 0;
        InfixTraversal(root, result, &index);   //postfix to infix
        printf("Postfix Expression:\n");
        for(int i = 0; i < index; i++){
            printf("%c ", result[i].value);
        }
        printf("\n");

        freeTree(root); //free the tree after use

    } else{
        printf("There is an error in the expression. \n");
    }

    return 0;
}