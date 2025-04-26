#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define MAX_STACK_SIZE 100

typedef struct {
    TreeNode *nodes[MAX_STACK_SIZE];
    int top;
} Stack;

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
        default:
            return 0; //invalid operator
    }
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

TreeNode* buildExpressionTree(Token tokens[], int tokenCount){
    Stack operandStack, operatorStack;
    initStack(&operandStack);
    initStack(&operatorStack);  


    for (int i = 0; i < tokenCount; i++){
        Token token = tokens[i];
        if(token.type == OPERAND){
            //if token type is an operand, create a node and push it to the operand stack
            TreeNode *node = createNode(token);
            pushStack(&operandStack, node); 
        } else if (token.type == OPERATOR){
            //it it is an operator, pop two nodes from the operand stack
            //and create a new node with the operator as the root
            //and the two popped nodes as the left and right children

            //key point in the shunting yard algorithm. If we push a lower precedence operator onto the stack, we need to pop the higher precedence operators first
            while(!isStackEmpty(&operatorStack) && precedence(peekStack(&operatorStack)->token.value) >= precedence(token.value)){
                TreeNode *operatorNode = popStack(&operatorStack);
                //pop two nodes from the operand stack
                TreeNode *rightNode = popStack(&operandStack);
                TreeNode *leftNode = popStack(&operandStack);
                
                //assign left and right children to the operator node
                operatorNode->left = leftNode;
                operatorNode->right = rightNode;

                //push the operator node back onto the operand stack
                pushStack(&operandStack, operatorNode);
            }

            //push the current operator onto the operator stack
            TreeNode *operatorNode = createNode(token);
            pushStack(&operatorStack, operatorNode);
        }
    }

    //after all tokens have been processed, pop any remaining operators from the operator stack
    while(!isStackEmpty(&operatorStack)){
        TreeNode *operatorNode = popStack(&operatorStack);
        TreeNode *rightNode = popStack(&operandStack);
        TreeNode *leftNode = popStack(&operandStack);

        operatorNode->left = leftNode;
        operatorNode->right = rightNode;

        //push the operator node back onto the operand stack
        pushStack(&operandStack, operatorNode);
    }

    //the final node of the operand stack is root node of the expression
    return popStack(&operandStack);
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
void InfixTraversal(TreeNode *node, Token output[], int *index) {
    if (node == NULL)
        return;
    else {
        InfixTraversal(node->left, output, index);
        output[(*index)++] = node->token;
        InfixTraversal(node->right, output, index);
    }
}

//builds an expression tree for conversions from prefix notation
TreeNode* buildPrefix(Token tokens[], int tokenCount) {
    Stack operandStack;
    initStack(&operandStack);

    for (int i = tokenCount -1 ; i >= 0; i--) {
        Token token = tokens[i];
        if(token.type == OPERAND){

            TreeNode *node = createNode(token);
            pushStack(&operandStack, node); 

        } else if (token.type == OPERATOR){
            
            TreeNode *operatorNode = createNode(token);
            TreeNode *leftNode = popStack(&operandStack);
            TreeNode *rightNode = popStack(&operandStack);

            operatorNode->left = leftNode;
            operatorNode->right = rightNode;

            pushStack(&operandStack, operatorNode);

        }
    }
    
    return popStack(&operandStack);
}

//tree builder for conversions from postfix notation
TreeNode* buildPostfix(Token tokens[], int tokenCount) {

    Stack operandStack;
    initStack(&operandStack);

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        if (token.type == OPERAND) {
            TreeNode *node = createNode(token);
            pushStack(&operandStack, node);
        }
        else if (token.type == OPERATOR) {

            TreeNode *operatorNode = createNode(token);
            TreeNode *rightNode = popStack(&operandStack);
            TreeNode *leftNode = popStack(&operandStack);
            
            operatorNode->left = leftNode;
            operatorNode->right = rightNode;

            pushStack(&operandStack, operatorNode);

        }

    }

    return popStack(&operandStack);
}