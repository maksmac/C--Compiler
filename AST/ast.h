#ifndef ASTH
#define ASTH

#include <stdlib.h>

enum treeNodeType {
    PROGRAM,
    VARDECL,
    FUNCDECL,
    DECLARATION,
    EXPR,
    STMT,
    DECISIONSTMT,
    RETURNSTMT,
    PARAMDECL,
    ITTERSTMT,
    BREAKSTMT,
    WRITESTMT,
    WRITELN,
    ASSIGNSTMT,
    EXPRSTMT,
    CALL,
    ARGLIST,
    BLOCK,
    IDENTIFIER,
    READSTMT,
    NUMBER,
    FLOATNUMBER,
    CHARACTER
};

enum operatorType {
    ADD,
    MINUS,
    DIVIDE,
    MULTIPLY,
    EQUAL,
    EQUALTO,
    NOTEQUALTO,
    LESSTHANOREQUAL,
    LESSTHAN,
    GREATERTHAN,
    GREATERTHANOREQUAL,
    AND,
    OR,
    NOT,
    INTDECL,
    CHARDECL,
    FLOATDECL,
    null
};

typedef struct ASTnodetype
{
     enum treeNodeType type;
     enum operatorType op;
     enum operatorType isType;
     char * name;
     char * str;
     int value;
     float fvalue;
     struct hashentry * symbol;
     struct ASTnodetype *left,*right; //to hold left and right children
     struct ASTnodetype *s1,*s2 ; // to hold potential expressions in if statments or parameters in functions.
} ASTNode;

ASTNode * prog;

ASTNode * createASTNode(enum treeNodeType);
void attatchLeft(ASTNode *, ASTNode *);
void printTree(int , ASTNode *);
void printNode(ASTNode *);
int compareFormals(ASTNode * call, ASTNode * func);
int checkExprType(ASTNode *);
int compareReturn(int returnType, int funcType);
int checkForBreak(ASTNode *);

#endif