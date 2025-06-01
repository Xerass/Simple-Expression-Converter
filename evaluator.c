#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "evaluator.h"


// a simple function used to evaluate the entered arithmetic expression 

int evaluateExpression(Token tokens[],int tokenCount, TreeNode *root, int index) {

    //loops through the tokenized expression
    //if variables are present, evaluation results in failure
    for (int i = 0; i < tokenCount; i++) {
            if (tokens[i].type == OPERAND && isalpha(tokens[i].value)) {
                printf("Error: Cannot evaluate expression with variables.\n");
                return 0;   //return evaluation failure status
            }
        }

    Stack evalStack;
    initStack(&evalStack);
    Token eval[MAX_TOKENS];
    int result = 0;
    index = 0;

    // postfix traversal is used to evaluate expressions
    // due to its efficiency and simple stack-based implementation
    PostfixTraversal(root, eval, &index);


    //loops through the 'eval' array which holds the tokens to be evaluated
    for (int i = 0; i < index; i++) {

        Token current = eval[i];


        //if the current token is an operand, create a node for that operand
        // and push it into the evaluation stack
        if (current.type == OPERAND) {
            int value = current.value - '0';    //subtracting ASCII '0' converts a character into its integer equivalent
            Token num = {OPERAND, value};       //assigns struct members 'OPERAND' and 'value'
            TreeNode* node = createNode(num);
            pushStack(&evalStack, node);
        }

        //if the current token is an operator, pop two operands from
        //the evaluation stack and let those operands be the right and left
        //operands respectively. A result node is also created to store the value
        //of the evaluation result later on.
        if (current.type == OPERATOR) {

            TreeNode* rightOperand = popStack(&evalStack);      //pops the right operand
            TreeNode* leftOperand = popStack(&evalStack);       //pops left operand
            TreeNode* resultNode = createNode((Token){OPERAND, 0});     //result node to be used for later

            int leftValue = leftOperand->token.value;
            int rightValue = rightOperand->token.value;


            //switch case to determine the type of operation to be performed
            switch (current.value) {
                case '+' : resultNode->token.value = leftValue + rightValue; break;
                case '-' : resultNode->token.value = leftValue - rightValue; break;
                case '*' : resultNode->token.value = leftValue * rightValue; break;

                case '/' : 
                    if (rightValue == 0) {
                        //checks for division by zero. Ends the program if the divisor is zero.
                        printf("Math Error! Division by zero not allowed.\n");
                        free(rightOperand);
                        free(leftOperand);
                        free(resultNode);
                        freeTree(root);
                        return 0;
                    }
                    resultNode->token.value = leftValue / rightValue; break;

                case '^' : resultNode->token.value = (int)pow(leftValue, rightValue); break;

            }

                //result node is pushed onto the evaluation stack and
                //the left and right opreand nodes are then freed
                pushStack(&evalStack, resultNode);

                free(leftOperand);
                free(rightOperand);
        }
    }

    //the last node in the stack is the result of 
    //the arithmetic expression evaluation. The result
    //node is popped and freed, and finally the result value is printed.
    TreeNode* resultNode = popStack(&evalStack);
    result = resultNode->token.value;
    free(resultNode);

    printf("Result is : %d\n", result); 

    //return successful evaluation status
    return 1;

}