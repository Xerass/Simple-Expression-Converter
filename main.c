//test area for progmram
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "parser.h"
#include "tree.h"

void printHelp(){
    printf("Usage: ./prog \"expression\" [pre|in|post] [-e]\n\n");
    printf("  expression   Arithmetic expression using:\n");
    printf("               - digits (0-9)\n");
    printf("               - single-letter vars (a-z, A-Z)\n");
    printf("               - operators: + - * / ^\n");
    printf("               - parentheses: ()\n\n");
    printf("  pre          Convert to prefix notation\n");
    printf("  in           Convert to fully parenthesized infix\n");
    printf("  post         Convert to postfix notation\n");
    printf("  -e           Evaluate numeric expressions only\n\n");
    printf("Examples:\n");
    printf("  ./prog \"3+4*2\" post      -> 3 4 2 * +\n");
    printf("  ./prog \"(a+b)*c\" pre    -> * + a b c\n");
    printf("  ./prog \"3+(4*2)\" in -e  -> 11\n");
    printf("  ./prog                 (no args shows this help)\n");
}

void printGuide(){
    printf("WIP, please improve\n");
    printf("Format: ./prog \"expression\" [pre|post|in] [-e]\n");
}

void printType(int t) {
  switch(t) {
    case 1: puts("The input is in prefix notation."); break;
    case 2: puts("The input is in infix notation.");  break;
    case 3: puts("The input is in postfix notation.");break;
    default: puts("Unknown notation.");               break;
  }
}

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printHelp();
        return 0;
    }

    if (argc == 2){
        if(strcmp(argv[1], "--help") == 0){
            printHelp();
            return 0;
        } else if (strcmp(argv[1], "--guide") == 0){
            printGuide();
            return 0;
        }
    
        const char *expression = argv[1];
        Token tokens[MAX_TOKENS];
        int tokenCount = 0;
    
    //----------------------NO EVAL MODE--------------------//
        //tokenize the expression and check for errors
        if(tokenize(expression, tokens, &tokenCount)){
            
            int type = evalExpressionType(tokens, tokenCount);
            printType(type);            
            TreeNode *root = NULL;

            switch(type){
                case 1: root = buildPrefix(tokens, tokenCount); break;
                case 2: root = buildInfix(tokens, tokenCount); break;
                case 3: root = buildPostfix(tokens, tokenCount); break;
            }

            if (!root) {
                printf("Expression was Invalid, try checking your input!");
                return 1;
            }

            Token result[MAX_TOKENS];
            int index = 0;
            PrefixTraversal(root, result, &index);
            printf("No specified conversion, defaulting to prefix....\n");
            printf("Prefix Expression:\n");
            for (int i = 0; i < index; i++){
                printf("%c ", result[i].value);
            }
            printf("\n");

            freeTree(root);

        } else {
            printf("Expression was Invalid, try checking your input!");
        }
    } else if (argc >= 3){
        const char *expression = argv[1];
        const char *targetTypeStr = argv[2];
        //check if 4 is input, then check if -e 
        bool evalFlag = (argc == 4 && strcmp(argv[3], "-e") == 0);

        Token tokens[MAX_TOKENS];
        int tokenCount = 0;

        if (!tokenize(expression, tokens, &tokenCount)) {
            printf("Error tokenizing expression.\n");
            return 1;
        }

        int inputType = evalExpressionType(tokens, tokenCount);
        printType(inputType);
        int targetType = 0;

        if (strcmp(targetTypeStr, "pre") == 0) {
            targetType = 1;
        } else if (strcmp(targetTypeStr, "in") == 0) {
            targetType = 2;
        } else if (strcmp(targetTypeStr, "post") == 0) {
            targetType = 3;
        } else {
            printf("Invalid target type. Use 'pre', 'in', or 'post'.\n");
            return 1;
        }

        if (inputType == targetType && !evalFlag){
            printf("Input and target types are the same. No conversion needed!\n");
            return 0;
        }

        TreeNode *root = NULL;
        switch (inputType) {
            case 1: root = buildPrefix(tokens, tokenCount); break;
            case 2: root = buildInfix(tokens, tokenCount); break;
            case 3: root = buildPostfix(tokens, tokenCount); break;
            default:
                printf("Unrecognized input expression type.\n");
                return 1;
        }

        if (!root) {
            printf("Error building expression tree.\n");
            return 1;
        }

        Token result[MAX_TOKENS];
        int index = 0;

        printf("Converted Expression:\n");
        switch(targetType){
            case 1: PrefixTraversal(root, result, &index); break;
            case 2: InfixTraversal(root, result, &index, 0, false); break;
            case 3: PostfixTraversal(root, result, &index); break;
        }

        for (int i = 0; i < index; i++){
            printf("%c ", result[i].value);
        }
        printf("\n");

        //------------make eval file
        //-----------WHOEVER DOES IT, convert everything to postfix then use basic stack evaluation (safest method)!!!!!!
        
        if (evalFlag) {

        for (int i = 0; i < tokenCount; i++) {
            if (tokens[i].type == OPERAND && isalpha(tokens[i].value)) {
                printf("Error: Cannot evaluate expression with variables.\n");
                return 1;
            }
        }
            
            //Didnt add any isEmptyStack checks since program will only reach evaluation phase
            //if there had been no stack issues during initial conversion/expression tree building.
            //But tbh i just felt lazy, I'll add it in on the next pull req.
            Stack evalStack;
            initStack(&evalStack);
            Token eval[MAX_TOKENS];
            int result = 0;
            index = 0;

            PostfixTraversal(root, eval, &index);


            for (int i = 0; i < index; i++) {

                Token current = eval[i];


                if (current.type == OPERAND) {
                    int value = current.value - '0';
                    Token num = {OPERAND, value};
                    TreeNode* node = createNode(num);
                    pushStack(&evalStack, node);
                }


                if (current.type == OPERATOR) {

                    TreeNode* rightOperand = popStack(&evalStack);
                    TreeNode* leftOperand = popStack(&evalStack);
                    TreeNode* resultNode = createNode((Token){OPERAND, 0});

                    int leftValue = leftOperand->token.value;
                    int rightValue = rightOperand->token.value;

                    switch (current.value) {
                        case '+' : resultNode->token.value = leftValue + rightValue; break;
                        case '-' : resultNode->token.value = leftValue - rightValue; break;
                        case '*' : resultNode->token.value = leftValue * rightValue; break;

                        case '/' : 
                            if (rightValue == 0) {
                                printf("Math Error! Division by zero not allowed.\n");
                                free(rightOperand);
                                free(leftOperand);
                                free(resultNode);
                                freeTree(root);
                                return 1;
                            }
                            resultNode->token.value = leftValue / rightValue; break;

                        case '^' : resultNode->token.value = (int)pow(leftValue, rightValue); break;
                            
                    }

                    pushStack(&evalStack, resultNode);

                    free(leftOperand);
                    free(rightOperand);
                }
            }

            TreeNode* resultNode = popStack(&evalStack);
            result = resultNode->token.value;
            free(resultNode);

            printf("Result is : %d\n", result);
        }

        freeTree(root);

    } else {
        printf("Invalid usage. Use --help for instructions.\n");
        return 1;
    }

    return 0;
}
