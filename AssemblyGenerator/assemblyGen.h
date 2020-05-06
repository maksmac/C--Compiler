#ifndef ASSEMBLY_GEN_H
#define ASSEMBLY_GEN_H
#include <stdio.h>
#include <stdlib.h>
#include "../AST/ast.h"
#define WORDSIZE 4
//user the placeHldr for storing continuous character numbers
static char placeHldr[100];
//file pointer for the assembly instructions being streamed into it.
FILE *fp;

char *createLabel(); //function similar to CreateTemp()
void writeInst(FILE *, char *, char *, char*); //this will write to the file, label, command, and comment

void readVariable(ASTNode *); //read variable node
void readFunction(ASTNode *); //read function node
void readDeclaration(ASTNode *); //read declaration node
void readExpr(ASTNode *); //read expression node
void readStmt(ASTNode *); //read statement node 
void readDecision(ASTNode *); //read if else statement node
void readReturn(ASTNode *); //read return node
void readParam(ASTNode *); //read parameter node
void readItter(ASTNode *); //read while node
void readWrite(ASTNode *); //read write node
void readAssign(ASTNode *); //read assignment node
void readExprStmt(ASTNode *); //read expression stmt
void readCall(ASTNode *); //read call to func node
void readArgs(ASTNode *, int, int); //read arguments node
void readIdentifier(ASTNode *); //read identifier node

void readAST(ASTNode *); //function will analyze the entire AST and write the nessicary assembly

#endif