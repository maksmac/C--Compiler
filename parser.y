%{
    #include "SymbolTable/symbolTable.c"
    #include "AST/ast.c"
    #include "AssemblyGenerator/assemblyGen.c"
    void yyerror (char const *s) {
        extern int yylineno;
        printf ("ERROR IN PARSER: %s Line Number: %i\n", s, yylineno);
    }
    void yywarn(char const *s) {
        extern int yylineno;
        printf("WARNING IN PARSER: %s Line Number: %i\n", s, yylineno);
    }
    static int level=0;
    static int offset=0;
    static int goffset=0;
    static int maxoffset=0;
    static int debug = 0;
    lineList returnStorage = NULL;
    int test = 0;
    hashTable hash;
    void initSymTab();
    
%}

%code requires {
    #include "SymbolTable/symbolTable.h"
    #include "AST/ast.h"
    #include "AssemblyGenerator/assemblyGen.h"
}

%start Program_P

%union {
    int value;
    float fvalue;
    char * string;
    ASTNode * node;
    enum operatorType op;
}


%token <op> INT_P CHAR_P FLOAT_P
%token <string> ID_P 
%token <value> CONSTANT_INT_P 
%token <string> CONSTANT_CHAR_P
%token <fvalue> CONSTANT_FLOAT_P
%token <node> NEWLINE_P 

%token <op> IF_P ELSE_P WHILE_P RETURN_P READ_P WRITE_P WRITELN_P BREAK_P
%token <op> SEMICOLON_P LP_P RP_P LB_P RB_P LCB_P RCB_P COMMA_P
%token <op> ADD_P MINUS_P MULTIPLY_P DIVIDE_P AND_P OR_P NOT_P EQUAL_P EQUALTO_P NOTEQUALTO_P LESSTHANOREQUAL_P LESSTHAN_P GREATERTHAN_P GREATERTHANOREQUAL_P 

%type <node> varDecl_P declList_P declaration_P expr_P stmtList_P stmt_P localDecls_P decisionStmt_P returnStmt_P var_P Primary_P exprList_P addAssign_P exprStmt_P
%type <node> paramDecl_P paramDeclList_P funcDecl_P paramDeclListTail_P block_P itterStmt_P writeStmt_P Type_P readStmt_P exprListTail_P call_P assignExpr_P simpleExpression_P multiAssign_P
%type <op>   compareOP_P multiOP_P UnaryOp_P BinaryOp_P addOP_P


%%
Program_P: 
    //overall AST is set to declList
    declList_P { 
            if (strcmp($1->name, "main")){
                printNode($1);
                yyerror("main function is requried and should be last declared function");
                exit(1);
            }
            prog = $1;
        } 
    ;

declList_P:
        declaration_P   {$$ = $1;}
    |   declList_P declaration_P   {
            $2->left = $1;
            $$ = $2;
        }  
    ;

declaration_P:
        varDecl_P   { $$ = $1; }
    |   funcDecl_P  { $$ = $1; }//add scope level
    ;

varDecl_P: 
        Type_P ID_P SEMICOLON_P {
            if (lookup(hash, $2)){
                printf("Variable %s Exists in Symbol Table\n", $2);
                yyerror ("ERROR DUPLICATE VARIABLE");
                exit(1);
            }
            hashEntry entry = createHashEntry($2,0,$1, level, offset, NULL);
            insertEntry(hash, entry);
            $$ = createASTNode(VARDECL);
            $$->name = $2;
            $$->op = $1;
            $$->symbol = entry;
            $$->isType = $1;
            offset += 1;
            if (offset > maxoffset){
                maxoffset = offset;
            }
            if (debug){
                fprintf(stderr, "Added Variable to Abstract Syntax Tree with name %s\n", $2);
            }
        }
    |   Type_P ID_P LB_P CONSTANT_INT_P RB_P SEMICOLON_P {
            if (lookup(hash, $2)){
                printf("Variable %s Exists in Symbol Table\n", $2);
                yyerror ("ERROR DUPLICATE VARIABLE Array");
                exit(1);
            }
            if ($4 <= 0){
                printf("Array Size constant must be greater than 0\n");
                yyerror ($4);
                exit(1);
            }
            hashEntry entry = createHashEntry($2, $4, $1, level, offset, NULL);
            insertEntry(hash, entry);
            entry->isAFunc = 2;
            $$ = createASTNode(VARDECL);
            $$->name = $2;
            $$->op = $1;
            $$->value = $4;
            $$->symbol = entry;
            $$->isType = $1;
            offset += $4;
            if (offset > maxoffset){
                maxoffset = offset;
            }
            if (debug){
                fprintf(stderr, "Added Variable Array to Abstract Syntax Tree with name %s\n", $2);
            }
        }
    ;

Type_P:
        INT_P { $$ = INTDECL; }
    |   CHAR_P { $$ = CHARDECL; }
    |   FLOAT_P { $$ = FLOATDECL; }
    ;

funcDecl_P:
        Type_P ID_P {
             if (lookup(hash, $2)){
                printf("Name %s Already used\n", $2);
                yyerror ("DUPLICATE NAME FOR FUNCTION");
                exit(1);
            }
            hashEntry entry = createHashEntry($2, 0, $1, level, offset, NULL);
            entry->isAFunc = 1;
            insertEntry(hash, entry);
            goffset = offset;
            offset = 2;
            if (offset > maxoffset){
                maxoffset = offset;
            }
        }LP_P paramDeclList_P {
            // Add parameters list to the fparams pointer for later comparison.
            (lookup(hash, $2))->fparams = $5;
        }RP_P block_P {
            $$ = createASTNode(FUNCDECL);
            $$->name = $2;
            $$->op = $1;
            $$->s1 = $5;
            $$->right = $8;
            $$->symbol = lookup(hash, $2);
            level = 0;
            $$->value = maxoffset;
            $$->symbol->mySize = maxoffset;
            offset = goffset;
            maxoffset = 0;
            if(returnStorage == NULL){
                yyerror("Function must return declared type\n");
                exit(1);
            }
            while(returnStorage != NULL){
                
                if (compareReturn(returnStorage->lineno, $1) == 0){
                    yyerror("Incompatible Return Type\n");
                    exit(1);
                }
                returnStorage = returnStorage->next;
            }
            if (debug){
                printf("Making Function with name %s\n",$2);
                printNode($$);
                printHashTable(hash);
            }
            returnStorage = NULL;
        }
    ;


paramDeclList_P:
        /*epsilon*/ {
            $$ = NULL; 
        }
    |   paramDeclListTail_P {
            $$ = $1;
        }
    ;

paramDeclListTail_P:
        paramDecl_P {
            $$ = $1;
        }
    |   paramDecl_P COMMA_P paramDeclListTail_P {
            $1->left = $3;
            $$ = $1;
        }
    ;
paramDecl_P:
        Type_P ID_P {
            if(lookup(hash, $2)){
                printf("Duplicate Variable Name\n");
                yyerror($2);
                yyerror("Change Argument Name\n");
                exit(1);
            }
            $$ = createASTNode(PARAMDECL);
            $$->name = $2;
            $$->op = $1;
            $$->value = 0;
            $$->isType = $1;
            hashEntry entry = createHashEntry($2, 1, $1, level+1, offset, NULL);
            insertEntry(hash, entry);
            $$->symbol = entry;
            offset += 1;
            if (offset>maxoffset)
                maxoffset = offset;
            if (debug){
                printf("Adding Parameter with name %s\n",$2);
                printNode($$);
                printHashTable(hash);
            }
        }
    |   Type_P ID_P LB_P RB_P {
            if(lookup(hash, $2)){
                printf("Duplicate Variable Name\n");
                yyerror($2);
                yyerror("Change Argument Name\n");
                exit(1);
            }
            $$ = createASTNode(PARAMDECL);
            $$->name = $2;
            $$->op = $1;
            $$->value = 1;
            $$->isType = $1;
            hashEntry entry = createHashEntry($2, 1, $1, level+1, offset, NULL);
            insertEntry(hash, entry);
            $$->symbol = entry;
            offset += 1;
            if (offset>maxoffset)
                maxoffset = offset;
            if (debug){
                printf("Adding Array Parameter with name %s\n",$2);
                printNode($$);
                printHashTable(hash);
            }
        }
    ;

block_P:
        LCB_P {
            level++;
            addScopeLevel(hash);
        }localDecls_P stmtList_P RCB_P {
            $$ = createASTNode(BLOCK);
            $$->name = "B";
            //if localDecls_P is null then theres only statements
            if($3 == NULL){
                $$->right = $4;
            }
            //if not then attach right
            else {
                attatchLeft($3, $4);
                $$->right = $3;
            }
            if(debug) {
                fprintf(stderr,"\ntable before deleting\n");
                printHashTable(hash);
            }
            removeScopeLevel(hash);
            offset -= 1;
            level--;
            if (debug) {
                fprintf(stderr,"\nEnd of Block, deleting symbols\n");
                fprintf(stderr,"     current table...\n");
                printHashTable(hash);/*Display after*/
            }
        }
    ;

localDecls_P:
        /*epsilon*/ { $$ = NULL; }
    |   varDecl_P localDecls_P  {
        if($1 != NULL){
            $1->left=$2;
            $$=$1;
        }
        else
            $$=$2;
    }
    ;

stmtList_P:
        stmt_P stmtList_P {
            if($1 != NULL){
                $1->left=$2;
                $$=$1;
            }
            else
                $$=$2;
        }
    |   /*epsilon*/ { $$ = NULL; }
    ;

stmt_P:
        /*epsilon*/ {
            $$ = NULL;
        }
    |   exprStmt_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a expression Statement\n");
            }
        }
    |   returnStmt_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a Return Statement\n");
            }
        }
    |   writeStmt_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a Write Statement\n");
            }
        }
    |   readStmt_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a Read Statement\n");
            }
        }
    |   itterStmt_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a Itteration Statement\n");
            }
        }
    |   decisionStmt_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a Decision Statement\n");
            }
        }
    |   block_P {
            $$ = $1;
            if (debug){
                fprintf(stderr, "Converting a Block Statement\n");
            }
        }
    |   assignExpr_P { 
            $$ = $1; 
            printf("Converting an Assign Statement\n");
        }
    ;

decisionStmt_P:
        IF_P LP_P expr_P RP_P stmt_P {
            printf("if statement found\n");
            $$ = createASTNode(DECISIONSTMT);
            if (checkExprType($3) != 1){
                printf("Error, non binary comparison operators\n");
                yyerror($3);
                exit(1);
            }
            $$->name = "IF";
            //set right to the expression in if stmt
            $$->right = $3;
            $$->s1 = $5;
        }
    |   IF_P LP_P expr_P RP_P stmt_P ELSE_P stmt_P {
            printf("if else statement\n");
            $$ = createASTNode(DECISIONSTMT);
            $$->name = "IFE";
            if (checkExprType($3) != 1){
                printf("Error, non binary comparison operators\n");
                yyerror($3);
                exit(1);
            }
            //set right to the expression in if stmt
            $$->right = $3;
            //set the if child pointer to the if stmt
            $$->s1 = $5;
            //set the else child pointer to the else stmt
            $$->s2 = $7;
        }
    ;

itterStmt_P:
        WHILE_P LP_P expr_P RP_P stmt_P {
            $$ = createASTNode(ITTERSTMT);
            if (checkExprType($3) != 1){
                printf("Error, non binary comparison operators\n");
                yyerror($3);
                exit(1);
            }
            $$->right = $3;
            printf("%d", checkForBreak($5));
            $$->s1 = $5;
            /*
                need to check $5 for a break statement, since $5 can be a block
                this means we may need to recursively check the block for a break
                statement. or 
            */
        }
    |   BREAK_P SEMICOLON_P {
            printf("break statement\n");
            $$ = createASTNode(BREAKSTMT);
            if (level <= 1){
                yyerror("Break statment not in while loop\n");
                exit(1);
            }
            /*
                The break statement must be in a scope that is greater than 1
                this is because 0 is global and 1 is a function, anything greater
                than that indicates a scope within a function. once we verify the
                scope then we can verify the node is a while node and therefore 
                the break statement will be valid.
            */
        }
    ;

writeStmt_P:
        WRITE_P expr_P SEMICOLON_P {
            printf("write statement\n");
            $$ = createASTNode(WRITESTMT);
            $$->name = "W";
            $$->right = $2;
            if ($2->type == IDENTIFIER){
                $2->symbol->isUsed = 1;
            }
        }
    |   WRITELN_P LP_P RP_P SEMICOLON_P {
            printf("write line statement");
            $$ = createASTNode(WRITELN);
        }
    ;

readStmt_P:
        READ_P Primary_P SEMICOLON_P {
            printf("read statement\n");
            $$ = createASTNode(READSTMT);
            $$->right = $2;
        }
    ;

returnStmt_P:
        RETURN_P expr_P SEMICOLON_P {
            test++;
            printf("%d RETURN", test);
            $$ = createASTNode(RETURNSTMT);
            $$->name = "RETURN";
            $$->s2 = $2;
            if ($2->type == IDENTIFIER){
                $2->symbol->isUsed = 1;
            }
            if (returnStorage != NULL)
                addLineToReturn(returnStorage, $2->isType);
            else 
                returnStorage = createLineListRec($2->isType);
        }
    ;

assignExpr_P:
        var_P EQUAL_P exprStmt_P {
            if ($1->isType != $3->isType){
                yyerror("Type Mismatch\n");
                exit(1);
            }
            $$ = createASTNode(ASSIGNSTMT);
            $$->name = $1->name;
            $$->right = $1;
            $$->s1 = $3;
            $$->s1->name = $1->name;
            $$->isType = $1->isType;
            $$->name = CreateTemp();
            hashEntry entry = createHashEntry($$->name, 1, $$->isType, level, offset, NULL);
            entry->value->charval = $3->name;
            insertEntry(hash, entry);
            $$->symbol = entry;
            offset+=1;
            if(offset>maxoffset)
                maxoffset = offset;
            if(debug){
                printNode($$);
                printf("%d operator\n", $$->op);
                printf("%s = %s\n", $1->name, $3->name);
            }
        }
    ;
exprStmt_P:
        expr_P SEMICOLON_P {
            $$ = createASTNode(EXPRSTMT);
            $$->name = $1->name;
            $$->right = $1;
            $$->isType = $1->isType;
            if (debug){
                printNode($1);
                fprintf(stderr, "Finished creating an expression Statement\n");
            }
        }
    ;

expr_P:
        simpleExpression_P { $$ = $1; }
    /*|   simpleExpression_P BinaryOp_P simpleExpression_P {
            $$ = createASTNode(EXPR);
            $$->op = $2;
            $$->right = $3;
            $$->left = $1;
        }*/
    ;
var_P:
        ID_P {
            hashEntry s;
            if (debug)
                printf("Searching for variable named %s\n", $1);
                if ((s = lookup(hash, $1)) != NULL){
                    if (s->isAFunc == 2){
                    yyerror($1);
                    yyerror("Variable is an array, syntax error");
                }
                if (debug)
                    printf("%s found in symbol table\n", $1);
                $$ = createASTNode(IDENTIFIER);
                $$->name = $1;
                $$->symbol = s;
                $$->isType = s->type;
            }
            else {
                yyerror($1);
                printf("Variable is Undeclared\n");
                exit(1);
            }
        }
    |   ID_P LB_P expr_P RB_P {
            hashEntry s;
            if((s = lookup(hash, $1)) != NULL){
                if(s->isAFunc != 2){
                    yyerror($1);
                    yyerror("Variable is not an array, syntax error");
                }
                $$ = createASTNode(IDENTIFIER);
                $$->name = $1;
                switch(s->type){
                    case FLOATDECL:
                        $3->type = FLOATNUMBER;
                        break;
                    default:
                        $3->type = NUMBER;
                        break;
                }
                $$->right = $3;
                $$->symbol = s;
                $$->isType = s->type;
            }
            else {
                printf("Undeclared variable used\n");
                yyerror($1);
                exit(1);
            }
        }
    ;

simpleExpression_P: 
        addAssign_P { $$ = $1; }
    |   simpleExpression_P compareOP_P addAssign_P {
            if ($1->isType != $3->isType) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            $$ = createASTNode(EXPR);
            $$->op = $2;
            $$->left = $1;
            $$->right = $3;
            $$->isType = $1->isType;
            $$->name = CreateTemp();
            hashEntry entry = createHashEntry($$->name, 0, $$->isType, level, offset+1, NULL);
            insertEntry(hash, entry);
            $$->symbol = entry;
            offset+=1;
            if(offset>maxoffset)
                maxoffset = offset;
        }
    ;

addAssign_P:
        multiAssign_P { $$ = $1; }
    |   addAssign_P addOP_P multiAssign_P {
            if ($1->isType != $3->isType) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            if ($1->type == IDENTIFIER){
                $1->symbol->isUsed = 1;
            }
            if ($3->type == IDENTIFIER){
                $3->symbol->isUsed = 1;
            }
            /*

                Constant Folding:
                    We need to check both sides of the expression for a Number
                    If the expression is a number on both sides
                        then we can perform constant Folding
                        In here we have to check the operator type
                        if plus
                            node type shouldnt be expression anymore and instead should be an assignment
                            if we get all the way up to the top and both are numbers we know the whole equation
                            contained numbers and therefore are an assignment node and not an expression node
                            do addition
                        else
                            do subtraction
                    Else 
                        we can just do the normal process

            */
            if ($1->type == NUMBER && $3->type == NUMBER){
                if(debug){
                    printf("Attempting Constant Fold\n");
                    printf("%d ", $1->value);
                    printOperator($2);
                    printf(" %d\n", $3->value);
                }
                switch($2){
                    case ADD:
                        $1->value = $1->value + $3->value;
                        $$ = $1;
                        break;
                    case MINUS:
                        $1->value = $1->value - $3->value;
                        $$ = $1;
                        break;
                }
            }
            else{
                $$ = createASTNode(EXPR);
                $$->op = $2;
                $$->right = $3;
                $$->left = $1;
                $$->isType = $1->isType;
                $$->name = CreateTemp();
                hashEntry entry = createHashEntry($$->name, 0, $$->isType, level, offset, NULL);
                insertEntry(hash, entry);
                $$->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
            
        }
    |   UnaryOp_P addAssign_P{
            if ( $2->isType != INTDECL ) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            $$ = createASTNode(EXPR);
            $$->op = $1;
            $$->right = $2;
            $$->isType = $2->isType;
            $$->name = CreateTemp();
            hashEntry entry = createHashEntry($$->name, 0, $$->isType, level, offset, NULL);
            insertEntry(hash, entry);
            $$->symbol = entry;
            offset+=1;
            if(offset>maxoffset)
                maxoffset = offset;
        }
    ;

multiAssign_P:
        Primary_P { $$ = $1; }
    |   multiAssign_P multiOP_P Primary_P {
            if ($1->isType != $3->isType) {
                printf("Type Mismatch\n");
                yyerror(" ");
                exit(1);
            }
            if ($1->type == IDENTIFIER){
                $1->symbol->isUsed = 1;
            }
            if ($3->type == IDENTIFIER){
                $3->symbol->isUsed = 1;
            }
            /*

                Constant Folding:
                    We need to check both sides of the expression for a Number
                    If the expression is a number on both sides
                        then we can perform constant Folding
                        In here we have to check the operator type
                        if multiply
                            node type shouldnt be expression anymore and instead should be an assignment
                            if we get all the way up to the top and both are numbers we know the whole equation
                            contained numbers and therefore are an assignment node and not an expression node
                            do addition
                        else
                            do division
                            Note: Since we are only handling Ints then we will just take the rounding that C does
                    Else 
                        we can just do the normal process

            */
            if ($2 == DIVIDE && $1->isType == INTDECL){
                yywarn("Divison on INT can cause FLOAT. Consider changing variable type to float.");
            }
            if ($1->type == NUMBER && $3->type == NUMBER){
                if(debug){
                    printf("Attempting Constant Fold\n");
                    printf("%d ", $1->value);
                    printOperator($2);
                    printf(" %d\n", $3->value);
                }
                switch($2){
                    case MULTIPLY:
                        $1->value = $1->value * $3->value;
                        $$ = $1;
                        break;
                    case DIVIDE:
                        yywarn("Dividing Two Integers will result in a rounded value");
                        $1->value = $1->value / $3->value;
                        $$ = $1;
                        break;
                }
            }
            /*
                Strenght Reduction:
                    check if left is variable and right is a number
                        switch to check for multiplication operator
                            if it is then just make it add variable to itself
                            will only work if the number is 2
            */
            if ($1->type == IDENTIFIER && $3->type == NUMBER && $2 == MULTIPLY && $3->value == 2){
                $$ = createASTNode(EXPR);
                $$->op = ADD;
                $$->right = $1;
                $$->left = $1;
                $$->isType = $1->isType;
                $$->name = CreateTemp();
                hashEntry entry = createHashEntry($$->name, 0, $$->isType, level, offset, NULL);
                insertEntry(hash, entry);
                $$->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
            if ($3->type == IDENTIFIER && $1->type == NUMBER && $2 == MULTIPLY && $1->value == 2){
                $$ = createASTNode(EXPR);
                $$->op = ADD;
                $$->right = $3;
                $$->left = $3;
                $$->isType = $3->isType;
                $$->name = CreateTemp();
                hashEntry entry = createHashEntry($$->name, 0, $$->isType, level, offset, NULL);
                insertEntry(hash, entry);
                $$->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
            else {
                $$ = createASTNode(EXPR);
                $$->op = $2;
                $$->right = $3;
                $$->left = $1;
                $$->isType = $1->isType;
                $$->name = CreateTemp();
                hashEntry entry = createHashEntry($$->name, 0, $$->isType, level, offset, NULL);
                insertEntry(hash, entry);
                $$->symbol = entry;
                offset+=1;
                if(offset>maxoffset)
                    maxoffset = offset;
            }
        }
    ;
Primary_P:    
        CONSTANT_INT_P {
            $$ = createASTNode(NUMBER);
            $$->name = CreateTemp();
            $$->value = $1;
            $$->op = INTDECL;
            $$->isType = INTDECL;
            printf("%d", $1);
            if (debug){
                fprintf(stderr, "The Number is: %d\n",$1);
            }
        }
    |   CONSTANT_CHAR_P {
            $$ = createASTNode(CHARACTER);
            $$->name = CreateTemp();
            $$->isType = CHARDECL;
            $$->str = $1;
        }
    |   CONSTANT_FLOAT_P {
            $$ = createASTNode(FLOATNUMBER);
            $$->name = CreateTemp();
            $$->fvalue = $1;
            $$->op = FLOATDECL;
            $$->isType = FLOATDECL;
            if (debug){
                fprintf(stderr, "The Float is: %f\n",$1);
            }
        }
    |   LP_P expr_P RP_P { $$ = $2; }
    |   call_P { $$ = $1; }
    |   var_P { $$ = $1; }
    ;

call_P:
        ID_P LP_P exprList_P RP_P {
            hashEntry s;
            if ((s = lookup(hash, $1)) != NULL){
                //Add if statment to check type to make sure we are calling a function and not a variable.
                if (s->isAFunc != 1){
                    printf("Error: %s is not a function\n", s->name);
                    yyerror(s->name);
                    exit(1);
                }
                if (compareFormals(s->fparams, $3) != 1){
                    printf("Variables in call dont match function\n");
                    yyerror($3);
                    exit(1);
                }

                $$ = createASTNode(CALL);
                $$->right = $3;
                $$->name = $1;
                $$->symbol = s;
                $$->value = s->value;
                $$->isType = s->type;

                if(debug){
                    printNode($$);
                    printf("Added Call to Function to AST\n");
                }
            }
            else{
                    yyerror($1);
                    yyerror("Function not defined in symbol table");
                    exit(1);
            }
        }
    ;
exprList_P:
        /*epsilon*/ { $$ = NULL; }
    |   exprListTail_P { $$ = $1; }
    ;


exprListTail_P:
        expr_P {
            $$ = createASTNode(ARGLIST);
            $$->right = $1;
        }
    |   expr_P COMMA_P exprListTail_P {
            $$ = createASTNode(ARGLIST);
            $$->left = $3;
            $$->right = $1;
        }
    ;

UnaryOp_P:
        MINUS_P { $$ = MINUS; }
    |   NOT_P { $$ = NOT; }
    ;

compareOP_P:
        EQUALTO_P { $$ = EQUALTO; } //pull
    |   NOTEQUALTO_P { $$ = NOTEQUALTO; } //pull
    |   LESSTHANOREQUAL_P { $$ = LESSTHANOREQUAL; } //pull
    |   LESSTHAN_P { $$ = LESSTHAN;} //pull
    |   GREATERTHAN_P { $$ = GREATERTHAN;} //pull
    |   GREATERTHANOREQUAL_P { $$ = GREATERTHANOREQUAL;} //pull
    |   AND_P { $$ = AND;}
    |   OR_P { $$ = OR;}
    ;

addOP_P:
        ADD_P { $$ = ADD; }
    |   MINUS_P { $$ = MINUS; }
    ;

multiOP_P:
        DIVIDE_P { $$ = DIVIDE; }
    |   MULTIPLY_P { $$ = MULTIPLY; }
    ;

BinaryOp_P:
        AND_P { $$ = AND;}
    |   OR_P { $$ = OR;}
    ;


%%
void initSymTab(){
    hash = createHashTable();
    printf("Hash Table Created Successfully\n");
}