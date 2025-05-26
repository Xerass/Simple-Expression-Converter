<h1 align="center">Simple Expression Converter in C</h1>

<p align="center">A program that converts an arithmetic expression from one notation to another by transforming the expression as a binary expression tree and
<br>utilizing tree traversal techniques for conversion. Evaluation is also done using the stack data structure.</p>

<hr>

## Prerequisites

Before compiling or running the program, make sure the following tools are installed:

### GNU Compiler Collection (GCC) Setup

1.   **Open Terminal**

#### On Linux:  
To do that, press the Ctrl + Alt + T.

#### On Windows:  
To do that, press the Windows key + X, then select PowerShell or Terminal.

#### On MacOS:  
To do that, Cmd + Space to open Spotlight search, then type "terminal" and press Enter.

2.   **GCC Installation**  

#### On Linux:
-    Update package lists:
```
sudo apt update
```

-    Install GCC:
```
sudo apt install gcc
```

-   For GCC install verification:
```
gcc --version
```

#### On Windows:
Install GCC by downloading [MSYS2](https://www.msys2.org) and follow the instructions on their website.

#### On MacOS:
-   Install Homebrew and follow further instructions on-screen:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

-   Install GCC once Homebrew is downloaded:
```
brew install gcc
```

-   For GCC install verification:
```
gcc --version
```

3.   **Edit Environment Variables (For Windows Only)** 

-   Search for "Environment Variables in Start Menu

-   Click Edit the system environment variables

-   Under System Properties → Advanced → Environment Variables

-   Under System variables, find and edit Path, then add:
```
C:\msys64\mingw64\bin
```

### Git Setup

1.   **Open Terminal**

#### On Linux:  
To do that, press the Ctrl + Alt + T.

#### On Windows:  
To do that, press the Windows key + X, then select PowerShell or Terminal.

#### On MacOS:  
To do that, Cmd + Space to open Spotlight search, then type "terminal" and press Enter.

2.   **Git Installation**  

#### On Linux:
-    Install Git:
```
sudo apt install git
```

-   For Git install verification:
```
git --version
```

#### On Windows:
-    Install Git:
```
winget install --id Git.Git -e --source winget
```

-   For Git install verification:
```
git --version
```

#### On MacOS:
-    Install Git:
```
brew install git
```

-   For Git install verification:
```
git --version
```

---

## How to compile the program?

1.   **Open Terminal**

#### On Linux:  
To do that, press the Ctrl + Alt + T.

#### On Windows:  
To do that, press the Windows key + X, then select PowerShell or Terminal.

#### On MacOS:  
To do that, Cmd + Space to open Spotlight search, then type "terminal" and press Enter.

2.    **Program Compilation**

#### On Linux and MacOS:  
-	Navigate to the project's directory:
```
cd path-to/Simple-Expression-Converter
```
Replace path-to with the path where the project is located.

-	Compile the program:
```
gcc -o prog main.c
```

#### On Windows:  

-	Navigate to the project's directory:
```
cd path-to\Simple-Expression-Converter
```
Replace path-to with the path where the project is located.

-	Compile the program:
```
gcc -o prog.exe main.c
```

---

## How to run the program?

#### Method 1: Adequate Execution
-	Requires changing the directory into the program's path everytime a new terminal is open.

#### On Linux and MacOS:  
-	Navigate to the project's directory:
```
cd path-to/Simple-Expression-Converter
```
Replace path-to with the path where the project is located.

-	Execution of program:
```
./prog "[expression]" [pre|in|post] [-e]
```
The double quotes (" ") are optional.

#### On Windows:  
-	Navigate to the project's directory:
```
cd path-to\Simple-Expression-Converter
```
Replace path-to with the path where the project is located.

-	Execution of program:
```
prog "[expression]" [pre|in|post] [-e]
```
The double quotes (" ") are optional.

#### Method 2: Adding the Program's Path to System PATH Environment Variable
-	The program can run from any directory in the terminal - no need to change the directory which makes for a cleaner workflow.
  Ideal for custom CLI programs such as this one.

#### On Linux and MacOS: 
-   Move the executable to a directory already in your PATH (like /usr/local/bin)
```
sudo mv prog /usr/local/bin/
```

-   Now you can run the program from anywhere

-	Execution of program:
```
./prog "[expression]" [pre|in|post] [-e]
```
The double quotes (" ") are optional.

#### On Windows:
-   Search for "Environment Variables in Start Menu

-   Click Edit the system environment variables

-   Under System Properties → Advanced → Environment Variables

-   Under System variables, find and edit Path, then add:
```
path-to\Simple-Expression-Converter
```
Replace path-to with the path where the project is located.

-   Now you can run the program from anywhere and without changing the directory every time a new terminal is open

-	Execution of program:
```
prog "[expression]" [pre|in|post] [-e]
```
The double quotes (" ") are optional.

#### Arguments:

-	**expression** -> Arithmetic expression that is composed of:
	- digits (0-9)
	- single-letter vars (a-z, A-Z)
	- operators: + - * /
	- parentheses: ()

-	**pre** -> Convert to prefix notation.

-	**in** -> Convert to fully parenthesized infix.

-	**post** -> Convert to postfix notation.

-	**-e** -> Evaluate numeric expressions only.

#### Examples:

1.	Converting the expression **"3 + 4 * 2"** into postfix notation.

-	Input:

```
./prog "3+4*2" post
```
Remove ./ if on Windows.

-	Output:

```
3 4 2 * +
```

2.	Converting the expression **"( a + b ) * c"** into prefix notation.

-	Input:

```
./prog "(a+b)*c" pre
```
Remove ./ if on Windows.

-	Output:

```
* + a b c
```

3.	Converting the expression **"3 + ( 4 * 2 )"** into infix notation and evaluating it.

-	Input:

```
./prog "3+(4*2)" in -e
```
Remove ./ if on Windows.

-	Output:

```
11
```

4.	Special case when no expression is included or when --help is appended.

-	Input:

```
./prog 
```
or
```
./prog --help
```
Remove ./ if on Windows.

-	Output:

```
Usage: ./prog "expression" [pre|in|post] [-e]
   expression   Arithmetic expression using:
                - digits (0-9)
                - single-letter vars (a-z, A-Z)
                - operators: + - * / ^
                - parentheses: ()
   pre          Convert to prefix notation
   in           Convert to fully parenthesized infix
   post         Convert to postfix notation
   -e           Evaluate numeric expressions only
 Examples:
   ./prog "3+4*2" post      -> 3 4 2 * +
   ./prog "(a+b)*c" pre    -> * + a b c
   ./prog "3+(4*2)" in -e  -> 11
   ./prog                 (no args shows this help)
```

5.	Special case when --guide is appended.

-	Input:

```
./prog --guide
```
Remove ./ if on Windows.

-	Output:

```
    The Simple Expression Converter is a utility used for converting a given arithmetic expression into its equivalent form in a different
    notation. Arithmetic expressions can be represented using three different notations. Those are the infix, prefix, and postfix notations.

    DEFINITIONS
    Infix Notation
    - The infix notation is the most commonly used representation for mathematical expressions. An expression is said to be in infix notation
    when an operator is placed between two operands. Although infix notation is convenient and easy to read, it can be challenging for 
    computers to evaluate due to factors such as operator precedence and the existence of parentheses in the expression. 
    (Examples : " 2 + 2 " , " X - Y " , "A / B")

    Prefix Notation
    In prefix notation (also known as Polish Notation), expressions are represented by placing the operators before their operands. In this
    representation, the position of the operands and operators determine the order of operations thus eliminating the dependency on
    parentheses. (Examples : "+ 2 2 ", "- X Y ", " / A B ")

    Postfix Notation
    - The postfix notation (also known as Reverse Polish Notation) represents mathematical expressions by having the operator succeed its
    operands. Similar to prefix notation, postfix is also non-ambiguous as the order of operations can be determined from operator and operand
    positions alone. It is most widely used by computers for evaluating arithmetic expressions.
    (Examples : " 2 2 + ", " X Y - ", " A B / ")

    HOW EXPRESSION CONVERSION IS DONE
    Input expressions taken from the command line are tokenized and checked for validity and type. An expression tree builder procedure is
    then invoked for that particular expression's type. Since each notation is interpreted differently (i.e., infix parentheses
    interpretation, prefix right-to-left scan), the utility has separate tree builders for each known notation.

    Expression trees represent arithmetic expressions as binary trees where the operator acts as the parent or root node and its two operators
    act as its children. Regardless of its type or notation used, any given expression can be converted to its equivalent in other notations
    as long as its expression tree has been built. Conversion is primarily done by performing tree traversal techniques on the expression trees.

    An in-order traversal of an expression tree results in the infix representation of an expression. This is due to its traversal behavior
    where the left child node, parent/root node, and right child node are visited in that specific order. Prefix notation can also be achieved
    by performing a pre-order traversal. This traversal visits the root node first and then its children from left to right. Finally, a post-
    order traversal, where the left and right child nodes are visited first before the root node, produce the postfix notation.


    HOW EXPRESSIONS ARE EVALUATED
    The most efficient method of evaluating arithmetic expressions on a computer is by converting the said expression into postfix notation
    and then evaluating it using the stack data structure. The evaluation process for postfix expressions is straightforward. If an incoming
    character is an operand, it is pushed onto the stack. If it is an operator, two operands are popped from the stack, the operation is
    applied to both operands, and the result is pushed back onto the stack. This process continues until only one element is left on the stack
    which is the result of the evaluation.


    SAMPLE USAGE
    ./prog					- Prints a simple help guide.
    ./prog 3+4*2				- Infix input. No conversion specified; defaults to prefix conversion.
    ./prog 3+4*2 post  			- Infix input. Conversion specified; converts to postfix.
    ./prog 3+(4*2) post			- Infix expression inputs with parentheses are also valid.
    ./prog 78+3- in				- Postfix input. Converts to infix.
    ./prog /+462 in -e			- Prefix input. Converts to infix. Evaluates the expression.
```

---

## Limitations

-   Only single-digit operands (0–9) are supported. Expressions such as 12 3 + will not work correctly.

-   Only basic operators are supported: +, -, *, and /.

-	Multi-character variables or numbers are not supported.

---

## Language and Dependencies

- **Language**: C 
- **Compiler**: GNU Compiler Collection (GCC) 
- **Dependencies**: Utilizes Standard C Libraries
