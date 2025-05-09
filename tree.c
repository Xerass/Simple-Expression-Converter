#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

void initStack(Stack *stack) {
    stack->top = -1;
}

int isStackEmpty(Stack *stack) {
    return stack->top == -1;
}

//simple stack push
void pushStack(Stack *stack, TreeNode *node) {
    //if stack is not full, push the node onto the top
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->nodes[++stack->top] = node;
    } else { //else overflow
        printf("Stack overflow\n");
    }
}

TreeNode* popStack(Stack *stack){
    //if stack is not empty pop node from the top
    if(!isStackEmpty(stack)){
        return stack->nodes[stack->top--];
    } else{//else underflow
        printf("Stack underflow\n");
        return NULL;
    }
}

TreeNode* peekStack(Stack *stack) {
    //if stack is not empty, return the top node
    if (!isStackEmpty(stack)) {
        return stack->nodes[stack->top];
    } else { //else underflow
        printf("Stack underflow\n");
        return NULL;
    }
}

int precedence(char operator){
    //returns the precedence of an operator
    switch(operator){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^': //added exponentiation operator
            return 3;
        default:
            return 0; //invalid operator
    }
}

bool isRightAssociative(char operator){
    return (operator == '^');  
}

TreeNode* createNode(Token token){
    //creates a lone node
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/**
Algo Overview:
 Iterate through each token:
 OPERAND: push a new node onto operandStack.
 OPERATOR: pop and build subtrees for any operators on operatorStack with >= precedence, then push this operator.
 LPAREN: push onto operatorStack to denote a sub-expression start.
 RPAREN: pop and build subtrees until matching LPAREN is found.
 2. After all tokens, pop any remaining operators to build the final tree.
 3. If any stray parentheses remain, report mismatches.
 */

TreeNode* buildInfix(Token tokens[], int tokenCount) {
    Stack operandStack, operatorStack;
    initStack(&operandStack);
    initStack(&operatorStack);
    int operandCount = 0;
    TreeNode *root = NULL;

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        if (token.type == LPAREN) {
            // Start of sub-expression
            TreeNode *p = createNode(token);
            pushStack(&operatorStack, p);
            continue;
        }
        else if (token.type == RPAREN) {
            // End of sub-expression: pop until matching LPAREN
            while (!isStackEmpty(&operatorStack) &&
                   peekStack(&operatorStack)->token.type != LPAREN) {
                TreeNode *opNode = popStack(&operatorStack);
                if (operandCount < 2) {
                    printf("Error: Not enough operands for operator '%c'\n",
                           opNode->token.value);
                    return NULL;
                }
                // Build subtree: right and left children
                TreeNode *right = popStack(&operandStack);
                TreeNode *left  = popStack(&operandStack);
                operandCount -= 2;
                opNode->left  = left;
                opNode->right = right;
                pushStack(&operandStack, opNode);
                operandCount++;
            }
            if (isStackEmpty(&operatorStack)) {
                printf("Error: Mismatched parentheses\n");
                return NULL;
            }
            // Discard the matching LPAREN node
            TreeNode *leftParenNode = popStack(&operatorStack);
            free(leftParenNode);
            continue;
        }
        else if (token.type == OPERATOR) {
            // Handle preceding operators of higher/equal precedence
            while (!isStackEmpty(&operatorStack) &&
                   precedence(peekStack(&operatorStack)->token.value) >=
                   precedence(token.value)) {
                TreeNode *opNode = popStack(&operatorStack);
                if (operandCount < 2) {
                    printf("Error: Not enough operands for operator '%c'\n",
                           opNode->token.value);
                    return NULL;
                }
                TreeNode *right = popStack(&operandStack);
                TreeNode *left  = popStack(&operandStack);
                operandCount -= 2;
                opNode->left  = left;
                opNode->right = right;
                pushStack(&operandStack, opNode);
                operandCount++;
            }
            // Push this operator for later
            TreeNode *p = createNode(token);
            pushStack(&operatorStack, p);
            continue;
        }
        else if (token.type == OPERAND) {
            // Operand goes directly onto the operand stack
            TreeNode *p = createNode(token);
            pushStack(&operandStack, p);
            operandCount++;
            continue;
        }
    }

    // Pop any remaining operators to finish tree
    while (!isStackEmpty(&operatorStack)) {
        TreeNode *opNode = popStack(&operatorStack);
        if (opNode->token.type == LPAREN || opNode->token.type == RPAREN) {
            // stray parenthesis
            printf("Error: Mismatched parentheses\n");
            return NULL;
        }
        if (operandCount < 2) {
            printf("Error: Not enough operands for operator '%c'\n",
                   opNode->token.value);
            return NULL;
        }
        TreeNode *right = popStack(&operandStack);
        TreeNode *left  = popStack(&operandStack);
        operandCount -= 2;
        opNode->left  = left;
        opNode->right = right;
        pushStack(&operandStack, opNode);
        operandCount++;
    }

    if (operandCount == 1) {
        root = popStack(&operandStack);
    } else if (operandCount != 1) {
    printf("Error: Malformed expression (excess operands/operators)\n");
    return NULL;
    }

    return root;
}

void freeTree(TreeNode *node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// Postfix traversal of the expression tree, saving it to an array
void PostfixTraversal(TreeNode *node, Token output[], int *index) {
    if (node == NULL) {
        return;
    }
    else if (node != NULL) {
        //visit left child, then right child, then root
        PostfixTraversal(node->left, output, index);
        PostfixTraversal(node->right,output, index);    
        //use index to save then increment its pointer up by one
        output[(*index)++] = node->token;
    }
}
//added prefix traversal
void PrefixTraversal(TreeNode *node, Token output[], int *index) {
    if (node == NULL)
        return;
    else {
        output[(*index)++] = node->token;
        PrefixTraversal(node->left, output, index);
        PrefixTraversal(node->right, output, index);
    }
}
//added infix traversal
void InfixTraversal(TreeNode *node,Token output[], int *index,int parentPrec,bool isRightChild){
    if (!node) return;

    if (node->token.type == OPERATOR) {
        int myPrec = precedence(node->token.value);

        // decide if we need parentheses around this subtree
        bool needParen = false;
        if (myPrec < parentPrec) {
            needParen = true;
        }
        else if (myPrec == parentPrec) {
            // for left-assoc ops, right child at same prec needs parens
            // for right-assoc ops, left child at same prec needs parens
            if (isRightChild && !isRightAssociative(node->token.value))
                needParen = true;
            if (!isRightChild &&  isRightAssociative(node->token.value))
                needParen = true;
        }

        if (needParen) {
            output[(*index)++] = (Token){ LPAREN, '(' };
        }

        // Recurse into children, passing our own precedence and side
        InfixTraversal(node->left,  output, index, myPrec, false);
        output[(*index)++] = node->token;
        InfixTraversal(node->right, output, index, myPrec, true);

        if (needParen) {
            output[(*index)++] = (Token){ RPAREN, ')' };
        }
    }
    else {
        // Simple operand
        output[(*index)++] = node->token;
    }
}


//builds an expression tree for conversions from prefix notation
TreeNode* buildPrefix(Token tokens[], int tokenCount) {
    Stack operandStack;
    initStack(&operandStack);
    int operandCount = 0;

    for (int i = tokenCount -1 ; i >= 0; i--) {
        Token token = tokens[i];
        if(token.type == OPERAND){

            TreeNode *node = createNode(token);
            pushStack(&operandStack, node); 
            operandCount++;

        } else if (token.type == OPERATOR){

            // Check if there are enough operands for the operator
            if (operandCount < 2) {
                printf("Error: Not enough operands for operator '%c'\n", token.value);
                return NULL;  // Too many operators
            }
            
            TreeNode *operatorNode = createNode(token);
            TreeNode *leftNode = popStack(&operandStack);
            TreeNode *rightNode = popStack(&operandStack);

            operatorNode->left = leftNode;
            operatorNode->right = rightNode;

            pushStack(&operandStack, operatorNode);
            operandCount--;

        }
    }

    if (operandCount != 1) {
        printf("Error: Excess operands or operators\n");
        return NULL;  // There should be exactly one operand (the result of the expression)
    }

    
    //added a check for empty stacks, if not empty then expression is invalid
    TreeNode* result = popStack(&operandStack);
    if (!isStackEmpty(&operandStack)) {
        // Stack is not empty, expression is invalid
        return NULL;
    }

    return result;
}

//tree builder for conversions from postfix notation
TreeNode* buildPostfix(Token tokens[], int tokenCount) {

    Stack operandStack;
    initStack(&operandStack);
    int operandCount = 0;

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        if (token.type == OPERAND) {
            TreeNode *node = createNode(token);
            pushStack(&operandStack, node);
            operandCount++;
        }
        else if (token.type == OPERATOR) {

            // Check if there are enough operands for the operator
            if (operandCount < 2) {
                printf("Error: Not enough operands for operator '%c'\n", token.value);
                return NULL;  // Too many operators
            }

            TreeNode *operatorNode = createNode(token);
            TreeNode *rightNode = popStack(&operandStack);
            TreeNode *leftNode = popStack(&operandStack);
            
            operatorNode->left = leftNode;
            operatorNode->right = rightNode;

            pushStack(&operandStack, operatorNode);
            operandCount--;
        }
    }

    if (operandCount != 1) {
        printf("Error: Excess operands or operators\n");
        return NULL;  // There should be exactly one operand (the result of the expression)
    }

    //if there are any remaining ops after all that, still error
    TreeNode* result = popStack(&operandStack);
    if (!isStackEmpty(&operandStack)) {
        printf("Stack is not empty, expression is invalid\n");
        return NULL;
    }

    return result;
}