#include <stdlib.h>
#include <stdio.h>
#include "ast.h"


ASTNode *createASTNode(enum treeNodeType type){
    ASTNode *new;
    new = (ASTNode * )malloc(sizeof(ASTNode));
    new->type = type;
    new->left = NULL;
    new->right = NULL;
    new->s1 = NULL;
    new->s2 = NULL;
    new->value = 0;
    new->fvalue = 0.0;
    new->name = NULL;
    new->str = NULL;
    new->symbol = NULL;
    new->isType = NULL;
    return new;
}

void printNode(ASTNode *node){
    printf("Name: %s\nStr: %s\nValue: %d\nType: %d\n", node->name, node->str, node->value, node->type);
}

void attatchLeft(ASTNode * base, ASTNode *attach){
    while (base->left !=NULL){
        base=base->left;
    }
    base->left=attach;
}

void printTabs(int ammt){
    int i;
    for (i=0; i < ammt; i++){
        printf("-");
    }
}

void printTree(int level, ASTNode *node){
    if (node == NULL ) return;
    else {
        printTabs(level);
        printf(">");
        switch (node->type) {
        case VARDECL :
            printf("Variable  "); 
            if ((node->op) == INTDECL)
                printf("INT ");

            if (node->op == CHARDECL)
                printf("CHAR ");

            if (node->op == FLOATDECL)
                printf("FLOAT ");

            printf("%s", node->name);
            if (node->value > 0) 
                printf("[%d]",node->value);

            printf("\n");
            break;

        case FUNCDECL:
            if (node->op == INTDECL)
                printf("INT ");

            if (node->op == CHARDECL)
                printf("CHAR ");

            if (node->op == FLOATDECL)
                printf("FLOAT ");

            printf("FUNCTION %s \n",node->name);

            if (node->s1 == NULL) {
                printTabs(level+2);
                printf( "(VOID)\n" );
            }
            else {
                printTabs(level+2);
                printf("( \n");

                printTree(level+2,node->s1);
                printTabs(level+2);
                printf(") \n");
            }
            printTree(level+2,node->right);
            break;

        case EXPR: printf("EXPR ");
            if (node->name != NULL)
                printf("  %s = ", node->name);

            printOpType(node);
            printf("\n");

            printTree(level+1, node->left);
            printTree(level+1, node->right);
            break;

        case  RETURNSTMT:
            printf("Return statement\n");
            
            printTree(level+1, node->right);
            break;

        case IDENTIFIER:
            printf("IDENTIFIER %s\n", node->name);
            if (node->right != NULL) {
                printTabs(level);
                printf("Array reference [\n");

                printTree(level+1,node->right);
                printTabs(level);
                printf("] end array\n");
            } 
            break;

        case BLOCK:
            printf("BLOCK STATEMENT\n");

            printTree(level+1,node->right);
            break;


        case READSTMT:
            printf("READ STATEMENT\n");

            printTree(level+1,node->right);
            break;

        case WRITESTMT:
            printf("WRITE STATEMENT\n");

            printTree(level+1,node->right);
            break;

        case ASSIGNSTMT:
            printf("Assignment STATEMENT\n");

            printTree(level+1,node->right);
            printTree(level+1,node->s1);
            break;

        case NUMBER:
            printf("NUMBER with value %d\n", node->value);
            break;
        
        case FLOATNUMBER:
            printf("Float number with value %f\n", node->fvalue);

        case ITTERSTMT:
            printf("WHILE STATEMENT\n");

            printTree(level+1,node->right);
            printf("\n");

            printTree(level+1,node->s1);
            printf("\n");
            break;

        case PARAMDECL:
            printf("PARAMETER ");
            if( node->op == INTDECL )
                printf("INT");

            if( node->op == CHARDECL )
                printf("CHAR");

            printf(" %s ",node->name);
            if(node->value == -1)
                printf("[]");

            printf("\n");
            break;

        case DECISIONSTMT:
            printf("IF STATEMENT\n");

            printTree(level+1,node->right);
            printf("\n");

            printTree(level+1,node->s1);
            printf("\n");

            if(node->s2 != NULL){
                printTabs(level);
                printf("ELSE \n");
                printTree(level+2,node->s2);
            }
            break;

        case CALL:
            printf("Function Call  %s\n" , node->name);
            if (node->right != NULL){
                printTree(level+2, node->right);
                printf("\n");
            }
            else{
                printTabs(level+2);
                printf("(VOID)\n");
            }
            break;
        case ARGLIST:
            printf("ARG\n");
            printTree(level+1, node->right);
            break;
        
        case EXPRSTMT:
            printf("Expression Statement\n");
            printTree(level+1, node->right);
            break;

        default: printf("Unknown type in printTree %d\n", node->type);
            break;

        } 

        if (node->type != EXPR)
            printTree(level, node->left);
    }
}

printOpType(ASTNode *node){
    switch (node->op){
        case ADD: printf("+");
        break;

        case MINUS: printf("-");
        break;

        case DIVIDE: printf("/");
        break;

        case MULTIPLY: printf("*");
        break;

        case EQUAL: printf("=");
        break;

        case EQUALTO: printf("==");
        break;

        case NOTEQUALTO: printf("!=");
        break;

        case LESSTHANOREQUAL: printf("<=");
        break;

        case LESSTHAN: printf("<");
        break;

        case GREATERTHAN: printf(">");
        break;

        case GREATERTHANOREQUAL: printf(">=");
        break;

        case AND: printf("&");
        break;

        case OR: printf("||");
        break;

        case NOT: printf("!");
        break;

        case INTDECL:
        case CHARDECL:
        case null:

        break;
    } 
}

printOperator(enum operatorType op){
    switch (op){
        case ADD: printf("+");
        break;

        case MINUS: printf("-");
        break;

        case DIVIDE: printf("/");
        break;

        case MULTIPLY: printf("*");
        break;

        case EQUAL: printf("=");
        break;

        case EQUALTO: printf("==");
        break;

        case NOTEQUALTO: printf("!=");
        break;

        case LESSTHANOREQUAL: printf("<=");
        break;

        case LESSTHAN: printf("<");
        break;

        case GREATERTHAN: printf(">");
        break;

        case GREATERTHANOREQUAL: printf(">=");
        break;

        case AND: printf("&");
        break;

        case OR: printf("||");
        break;

        case NOT: printf("!");
        break;

        case INTDECL:
        case CHARDECL:
        case null:

        break;
    } 
}

//compare parameters in call to ensure proper parameters.
int compareFormals(ASTNode * call, ASTNode * func){
    if((call==NULL) && (func==NULL)){
        return(1); //true
    }
    else if ((call==NULL) || (func==NULL)){
        return (0); //false
    }
    else if(call->isType == func->right->isType){
        return (compareFormals(call->left, func->left)); //check the next parameter
    }
    else
    {
        printf ("Comparing call %d and func %d \n",call->isType,func->isType);
        return(0);
    }
}

//recursively check each operator type that is also a type EXPR
int checkExprType(ASTNode *node){
    switch(node->op){
        case ADD:
            return 0;
        case MINUS:
            return 0;
        case DIVIDE:
            return 0;
        case MULTIPLY:
            return 0;
        case EQUAL:
            return 0;
        case CHARDECL:
            return 0;
        default:
            return 1;
    }
}

int compareReturn(int returnType, int funcType){
    if (returnType != funcType){
        return 0;
    }
}

int checkForBreak(ASTNode * node){
    //gotta go right if var decl is null
    //or right then left if not
    if (node->type == BREAKSTMT){
        printf("Found break statement\n");
        return 1;
    }
    else {
        if (node->right != NULL){
            printf("checking right\n");
            return checkForBreak(node->right);
        }
        if (node->left != NULL) {
            printf("checking Left\n");
            return checkForBreak(node->left);
        }
    }
    return 0;
}