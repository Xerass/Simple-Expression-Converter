//test area for progmram
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "parser.h"
#include "tree.h"
#include "evaluator.h"

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
    
    printf("\n\n\nThe Simple Expression Converter is a utility used for converting a given arithmetic expression into its equivalent form in a different\n");
    printf("notation. Arithmetic expressions can be represented using three different notations. Those are the infix, prefix, and postfix notations.");

    printf("\n\nDEFINITIONS\n\n");
    printf("Infix Notation\n");
    printf("- The infix notation is the most commonly used representation for mathematical expressions. An expression is said to be in infix notation\n");
    printf("when an operator is placed between two operands. Although infix notation is convenient and easy to read, it can be challenging for \n");
    printf("computers to evaluate due to factors such as operator precedence and the existence of parentheses in the expression. \n");
    printf("(Examples : \" 2 + 2 \" , \" X - Y \" , \"A / B\")\n\n\n");

    printf("Prefix Notation\n");
    printf("In prefix notation (also known as Polish Notation), expressions are represented by placing the operators before their operands. In this\n");
    printf("representation, the position of the operands and operators determine the order of operations thus eliminating the dependency on\n");
    printf("parentheses. (Examples : \"+ 2 2 \", \"- X Y \", \" / A B \")\n\n\n");

    printf("Postfix Notation\n");
    printf("- The postfix notation (also known as Reverse Polish Notation) represents mathematical expressions by having the operator succeed its\n");
    printf("operands. Similar to prefix notation, postfix is also non-ambiguous as the order of operations can be determined from operator and operand\n");
    printf("positions alone. It is most widely used by computers for evaluating arithmetic expressions.\n");
    printf("(Examples : \" 2 2 + \", \" X Y - \", \" A B / \")\n\n\n");

    printf("HOW EXPRESSION CONVERSION IS DONE\n\n");
    printf("Input expressions taken from the command line are tokenized and checked for validity and type. An expression tree builder procedure is\n");
    printf("then invoked for that particular expression's type. Since each notation is interpreted differently (i.e., infix parentheses\n");
    printf("interpretation, prefix right-to-left scan), the utility has separate tree builders for each known notation.\n\n");

    printf("Expression trees represent arithmetic expressions as binary trees where the operator acts as the parent or root node and its two operators\n");
    printf("act as its children. Regardless of its type or notation used, any given expression can be converted to its equivalent in other notations\n");
    printf("as long as its expression tree has been built. Conversion is primarily done by performing tree traversal techniques on the expression trees.\n\n");

    printf("An in-order traversal of an expression tree results in the infix representation of an expression. This is due to its traversal behavior\n");
    printf("where the left child node, parent/root node, and right child node are visited in that specific order. Prefix notation can also be achieved\n");
    printf("by performing a pre-order traversal. This traversal visits the root node first and then its children from left to right. Finally, a post-\n");
    printf("order traversal, where the left and right child nodes are visited first before the root node, produce the postfix notation.\n\n");


    printf("HOW EXPRESSIONS ARE EVALUATED\n\n");
    printf("The most efficient method of evaluating arithmetic expressions on a computer is by converting the said expression into postfix notation\n");
    printf("and then evaluating it using the stack data structure. The evaluation process for postfix expressions is straightforward. If an incoming\n");
    printf("character is an operand, it is pushed onto the stack. If it is an operator, two operands are popped from the stack, the operation is\n");
    printf("applied to both operands, and the result is pushed back onto the stack. This process continues until only one element is left on the stack\n");
    printf("which is the result of the evaluation.\n\n\n");


    printf("SAMPLE USAGE\n\n");
    printf("./prog					- Prints a simple help guide.\n");
    printf("./prog 3+4*2				- Infix input. No conversion specified; defaults to prefix conversion.\n");
    printf("./prog 3+4*2 post  			- Infix input. Conversion specified; converts to postfix.\n");
    printf("./prog 3+(4*2) post			- Infix expression inputs with parentheses are also valid.\n");
    printf("./prog 78+3- in				- Postfix input. Converts to infix.\n");
    printf("./prog /+462 in -e			- Prefix input. Converts to infix. Evaluates the expression.\n\n\n");

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

       //----------------------WITH EVALUATION--------------------//
        //The if-block below executes when the user wishes to evaluate the entered expression
        //success_flag = 1 denotes a successful evaluation and failure if success_flag = 0
        
        if (evalFlag) {

            int success_flag = evaluateExpression(tokens, tokenCount, root, index);
           
            if (!success_flag) {
                printf("\nEvaluation failure. Program terminated.\n");
                freeTree(root);
                return 1;
            }

        }

        freeTree(root);

    } else {
        printf("Invalid usage. Use --help for instructions.\n");
        return 1;
    }

    return 0;
}
