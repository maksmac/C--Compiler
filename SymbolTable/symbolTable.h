#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

//Size of hash table
#define SIZE 47

//Shift is used for the hashing function
#define SHIFT 4

#include "../AST/ast.h"

//line numbers containing variable refrences 
typedef struct lineListRec {
    int lineno;
    struct lineListRec *next;
} * lineList;

typedef struct hashentryvalue {
    int intval;
    char *charval;
} * Value;

//node within hash table
typedef struct hashentry{
    char *name;
    lineList lines;
    int type;
    int mySize;
    int isAFunc; // NULL = int, 1 = Function, 2 = Array
    int offset;
    int isUsed; //0 = not used, 1 = used; will use for dead code removal
    struct hashentryvalue *value;
    ASTNode *fparams;
    struct hashentry *next; //For collisions
} * hashEntry;

//Doubly linked list of hash tables
typedef struct hashtbl{
    struct hashtbl * next;
    struct hashtbl * prev;
    hashEntry hash[SIZE]; 
} * hashTable;

/* Function prototypes */
void printLines(lineList);
void printHashTable(hashTable);
int getHashCode( char * );
lineList createLineListRec(int);
int getLineno(hashEntry);
hashTable createHashTable();
hashEntry createBlankHashEntry();
Value createBlankValue();
hashEntry createHashEntry (char *, int, int, int, int, hashEntry);
Value createValueEntry(char *, int);
int getScopeLevel(hashTable);
void addScopeLevel(hashTable);
void removeScopeLevel(hashTable);
hashTable getRootNode(hashTable);
hashTable getOuterMostScope(hashTable);
int compareHashEntries(hashEntry, hashEntry);
int compareEntryToName(hashEntry, char *);
void printSpaces(int);
void addLine(hashEntry, int);
hashEntry lookup( hashTable, char *);
void printEntry(hashEntry);
void printValue(Value v);
hashEntry existsInLevel(hashTable, char *);
void insertEntry(hashTable, hashEntry);
void updateEntry(hashTable, hashEntry, hashEntry);
char * CreateTemp();

#endif
