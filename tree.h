#ifndef TREE_H
#define TREE_H

#include "parser.h"

typedef struct TreeNode {
    Token token;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* buildExpressionTree(Token tokens[], int tokenCount);
TreeNode* createNode(Token token);
void freeTree(TreeNode *node);
void PostfixTraversal(TreeNode *node, Token output[], int *index);

#endif

