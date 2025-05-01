#ifndef TREE_H
#define TREE_H

#include "parser.h"

typedef struct TreeNode {
    Token token;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* buildInfix(Token tokens[], int tokenCount);
TreeNode* buildPrefix(Token tokens[], int tokenCount);
TreeNode* buildPostfix(Token tokens[], int tokenCount);
TreeNode* createNode(Token token);
void freeTree(TreeNode *node);
void PostfixTraversal(TreeNode *node, Token output[], int *index);
void PrefixTraversal(TreeNode *node, Token output[], int *index);
void InfixTraversal(TreeNode *node, Token output[], int *index);
#endif

