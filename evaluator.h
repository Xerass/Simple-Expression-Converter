#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "parser.h"
#include "tree.h"

int evaluateExpression(Token tokens[],int tokenCount, TreeNode *root, int index);

#endif