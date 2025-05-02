#ifndef TREE_H
#define TREE_H

#include "parser.h"

#define MAX_STACK_SIZE 100

typedef struct TreeNode {
    Token token;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    TreeNode *nodes[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack *stack);
int isStackEmpty(Stack *stack);
void pushStack(Stack *stack, TreeNode *node);
TreeNode* popStack(Stack *stack);
TreeNode* peekStack(Stack *stack);


TreeNode* buildInfix(Token tokens[], int tokenCount);
TreeNode* buildPrefix(Token tokens[], int tokenCount);
TreeNode* buildPostfix(Token tokens[], int tokenCount);
TreeNode* createNode(Token token);
void freeTree(TreeNode *node);
void PostfixTraversal(TreeNode *node, Token output[], int *index);
void PrefixTraversal(TreeNode *node, Token output[], int *index);
void InfixTraversal(TreeNode *node, Token output[], int *index);
#endif

