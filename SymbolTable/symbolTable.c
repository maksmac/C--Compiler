#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

static int GTEMP = 0;

char * CreateTemp(){
	char hold[1000];
	char *s;
    sprintf(hold,"_t%d",GTEMP++);
    s = strdup(hold);
	return(s);
}


void printLines(lineList ll) {
	lineList curr = ll;
	while(curr != NULL) {
		printf("%d ", curr->lineno);
		curr = curr->next;
	}
}

// Hashing Function
int getHashCode ( char * key ){ 
	int temp = 0;
  	int i = 0;
  	while (key[i] != '\0')
	{ temp = ((temp << SHIFT) + key[i]) % SIZE;
		++i;
	}
	return temp;
}

//Creates empty line list recorder
lineList createLineListRec(int num) {
	lineList new = (lineList) malloc(sizeof(struct lineListRec));
	new->next = NULL;
	new->lineno = num;
	return new;
}

//return lineno of node symbol
int getLineno(hashEntry entry){
	return entry->lines->lineno;
}

//creates empty hash table of size SIZE
hashTable createHashTable() {
	printf("Creating Hash Table\n");
	hashTable new = (hashTable) malloc(sizeof(struct hashtbl));
	int i; 
	for(i = 0; i < SIZE; ++i) {
		new->hash[i] = createBlankHashEntry();
	}
	new->next = NULL;
	new->prev = NULL;
	return new;
}

//creates blank hash entry
hashEntry createBlankHashEntry() {
	hashEntry new = (hashEntry) malloc(sizeof(struct hashentry));
	new->name = NULL;
	new->lines = NULL;
	new->next = NULL;
	new->fparams = NULL;
	new->isAFunc = NULL;
	new->offset = NULL;
	new->type = -1;
	new->isUsed = 0;
	new->value = createBlankValue();
	return new;
}

Value createBlankValue(){
	Value new = (Value) malloc(sizeof(Value));
	new->intval = NULL;
	new->charval = NULL;
	return new;
}

//returns the scope level
int getScopeLevel(hashTable h) {
	int sl = 0;
	hashTable curr = h;
	while(curr->next != NULL) {
		++sl;
		curr = curr->next;
	}
	return sl+1;
}

//returns outer most scope
hashTable getOutermostScope(hashTable h) {
	hashTable curr = h;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	return curr;
}

hashTable goToHashLevel(hashTable h, int level) {
	hashTable curr = h;
	int temp = 0;
	while(curr->next != NULL) {
		if (temp == level){
			break;
		}
		curr = curr->next;
		temp += 1;
	}
	return curr;
}

//creates new hash entry with data provided
hashEntry createHashEntry( char * str, int mySize, int type, int lineno, int offset, hashEntry fparams) {
	hashEntry new = (hashEntry) malloc(sizeof(struct hashentry));

	char* newStr = malloc( strlen(str));
	strcpy(newStr, str);

	new->name = newStr;
	new->lines = createLineListRec(lineno);
	new->type = type;
	new->mySize = mySize;
	new->fparams = fparams;
	new->offset = offset;
	new->value = createValueEntry(NULL, NULL);
	new->next = NULL;
	return new;
}

Value createValueEntry(char *charval, int intval){
	Value new = (Value) malloc(sizeof(Value));
	new->intval = intval;
	new->charval = charval;
	return new;
}

//prints all contents of hash table in each scope
void printHashTable(hashTable h) {
	int i;
	int spaces = 0;
	int sl;
	hashTable curr = h;
	hashEntry currEntry;
	printf("******SYMBOL TABLE******\n");
	for(sl=0; sl < getScopeLevel(h); sl++) {
		printf("*");
		printSpaces(spaces);
		printf("--Scope level %d--\n",sl);
		for(i = 0; i < SIZE; ++i) {
			currEntry = curr->hash[i];
			while( currEntry != NULL ) {
				if(currEntry->name != NULL) {
				printf("*");
				printSpaces(spaces);
				printEntry(currEntry);
				printf("\n");
				}
				currEntry = currEntry->next;	
			}
			
		}
		curr = curr->next;
		spaces = spaces + 3;
	}
	printf("************************\n");
}

//prints individual entry
void printEntry(hashEntry h) {
	printf("ID: %s, type: %d lines: ", h->name, h->type);
	printLines(h->lines);
	printf("value: ");
	printValue(h->value);
}

void printValue(Value v) {
	Value curr = v;
	if (curr->intval != NULL){
		printf("%d", curr->intval);
		return;
	}
	if (curr->charval != NULL){
		printf("%s", curr->charval);
		return;
	}
	else{
		printf("(null)");
		return;
	}
}

void printSpaces(int n) {
	int t;
	char* space = " ";
	for(t = 0; t < n; ++t)
		printf("%s",space);
}

//adds new scope and hash table, basically new node in dll 
void addScopeLevel(hashTable base) {
	hashTable curr = base;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = createHashTable();
	curr->next->prev = curr;
}

// removes the outermost scope
void removeScopeLevel(hashTable base) {
	hashTable tmp;
	hashTable curr = base;
	if (curr->next != NULL){
		while(curr->next != NULL) {
			curr = curr->next;
		}
		tmp = curr;
		curr = curr->prev;
		curr->next = NULL;
		free(tmp);
	}
	else{
		printf("No outer scopes detected\n");
	}
}

//compare entries for duplicate, returns -1, 1, 0;
int compareHashEntries(hashEntry a, hashEntry b) {
	if(a->name == NULL)
		return -1;
	else if(b->name == NULL)
		return -1;
	else 
		return strcmp(a->name, b->name);
}

int compareEntryToName(hashEntry a, char * b) {
	if(a->name == NULL)
		return -1;
	else if(b == NULL)
		return 1;
	else 
		return strcmp(a->name, b);
}

void addLine(hashEntry h, int x) {
	lineList ll = h->lines;
	lineList new = createLineListRec(x);
	while(ll->next != NULL) {
		ll = ll->next;
	}
	ll->next = new;
}

void addLineToReturn(lineList ll, int x) {
	lineList new = createLineListRec(x);
	while(ll->next != NULL) {
		ll = ll->next;
	}
	ll->next = new;
}

//search hastable within scope first if not checks other scope
hashEntry lookup( hashTable base, char * name) {
	hashTable hashitr = getOutermostScope(base);
	hashEntry match = NULL;

	while( hashitr != NULL) {
		match = existsInLevel( hashitr, name );
		if(match != NULL)
			break;
		hashitr = hashitr->prev;
	}
	return match;
}

hashEntry lookupInLevel(hashTable base, char *name, int level){
	hashTable levels;
	hashTable curr = base;
	if ((levels = goToHashLevel(curr, level)) != NULL){
		return existsInLevel(levels, name);
	}
	return NULL;
}

//does the key exist within the current scope
hashEntry existsInLevel( hashTable level, char * name) {
	hashEntry match = NULL;
	hashEntry itr = level->hash[getHashCode(name)];
	while( itr != NULL) {
		if( compareEntryToName(itr, name) == 0 ) {
			match = itr;
		}
		if(match != NULL)
			break;
		itr = itr->next;
	}

	return match;
}

//insert new entry into hash table
void insertEntry( hashTable base, hashEntry h ) {
	hashTable hashitr = getOutermostScope(base);
	hashEntry existing;
	
	if(hashitr->hash[getHashCode(h->name)]->type == -1) // empty spot
		hashitr->hash[getHashCode(h->name)] = h; // no collision insert as planned
	else {
		existing = existsInLevel(hashitr, h->name); // check if it exists already within scope
		if(existing != NULL)
			addLine(existing, h->lines->lineno); // if it does add +1 to lineno
		else { // this indicates collision so it will add to the end of the table.
			existing = hashitr->hash[getHashCode(h->name)];
			while(existing->next != NULL)
				existing = existing->next;
			existing->next = h;
			printf("Inserted %s as a linked item\n", h->name);
		}
	}
}

void updateEntry(hashTable base, hashEntry old, hashEntry new){
	hashTable hashitr = getOutermostScope(base);

	if (hashitr->hash[getHashCode(old->name)]->type != -1){
		hashitr->hash[getHashCode(old->name)] = new;
	}
	else{
		hashEntry match = NULL;
		while(hashitr != NULL){
			match = existsInLevel(hashitr, old->name);
			if (match != NULL){
				hashitr->hash[getHashCode(old->name)] = new;
			}
		}
	}
	free(old);
	printf("Successfully Updated Hash Entry %s\n", new->name);
}
