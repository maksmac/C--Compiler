#include "assemblyGen.h"

static int LTEMP;
int stackValue;


char *createLabel(){
    char temp[100];
    char *a;
    sprintf(temp, "_L%d", LTEMP++);
    a = strdup(temp);
    return a;
}

int readIdType(ASTNode *node){
    switch(node->isType){
        case INTDECL:
            return 1;
        case FLOATDECL:
            return 2;
        case CHARDECL:
            return 11;
    }
}

void writeInst(FILE * fp, char * label, char * command, char *comment){
    char temp[100];
    sprintf(temp, "%s \t%s \t\t%s\n", label, command, comment);
    fprintf(fp, temp);
} //this will write to the file, label, command, and comment

void readVariable(ASTNode *node){
    switch(node->isType){
        case INTDECL:
            if (node->symbol->mySize != 0){
                writeInst(fp, ".data", "", "#This indicates data segment");
                sprintf(placeHldr, "%s: .word %d", node->name, node->value*WORDSIZE);
                writeInst(fp, "", placeHldr, "");
                writeInst(fp, ".text", "", "");
            }
            else {
                writeInst(fp, ".data", "", "#This indicates data segment");
                sprintf(placeHldr, "%s: .word  %d", node->name, node->symbol->mySize*WORDSIZE);
                writeInst(fp, "", placeHldr, "");
                writeInst(fp, ".text", "", "");
            }
            break;
        case CHARDECL:
            if (node->symbol->mySize != 0){
                //first we create the label as well as the size label for the array
                writeInst(fp, ".data", "", "#This indicates data segment");
                sprintf(placeHldr, "%s: .asciiz  \"\"", node->name);
                writeInst(fp, "", placeHldr, "");
                sprintf(placeHldr, "%s: .word   %d", strcat(node->name, "size"), node->symbol->mySize*WORDSIZE);
                writeInst(fp, "", placeHldr, "");
                writeInst(fp, ".text", "", "");
            }
            else {
                writeInst(fp, ".data", "", "#This indicates data segment");
                sprintf(placeHldr, "%s: .byte  %d", node->name, node->symbol->mySize*WORDSIZE);
                writeInst(fp, "", placeHldr, "");
            }
            break;
        case FLOATDECL: 
            if (node->symbol->mySize != 0){
                double f = (float) node->symbol->mySize*WORDSIZE;
                writeInst(fp, ".data", "", "#This indicates data segment");
                sprintf(placeHldr, "%s: .float  %f", node->name, f);
                writeInst(fp, "", placeHldr, "");
            }
            else {
                writeInst(fp, ".data", "", "#This indicates data segment");
                sprintf(placeHldr, "%s: .float  %f", node->name, 0.0);
                writeInst(fp, "", placeHldr, "");
            }
            break;
    }
} // end read variable

void readFunction(ASTNode *node){
    /*
        In order to write a function in mips there are a few things
        we need to do. I dont know any of the things
        .text indicates the start of instruction
        function name: indicates the start of the function
    */
    writeInst(fp, ".text", "", "#start instruction");
    sprintf(placeHldr, ".globl %s", node->name);
    writeInst(fp, "", placeHldr, "#Global decleration for function");

    //Now we add the stub for the function in mips
    sprintf(placeHldr, "%s:", node->name);
    writeInst(fp, placeHldr, "", "#begin function");

    //Create stack frame for data storage
    //printf("Function Activation Record Offset: %d\n", node->value*WORDSIZE);
    sprintf(placeHldr, "subu $t0, $sp, %d", node->value*WORDSIZE);
    writeInst(fp, "", placeHldr, "#add offset for stack");
    sprintf(placeHldr, "sw $ra, %d($t0)", 1*WORDSIZE);
    writeInst(fp, "", placeHldr, "#store return address in stack");
    writeInst(fp, "", "sw $sp, ($t0)", "#save old sp");
    writeInst(fp, "", "addu $sp, $t0, 0", "#move sp back up");

    //go right
    readAST(node->right);
    
    //always write return stmt, removing for now
    readReturn(node);
} //end function node

void readExpr(ASTNode *node){
    //expressions go from left to right so we need to read left side first
    //we are going to use $t0 to store the left
    switch(node->left->type){
        case NUMBER:
            sprintf(placeHldr, "li  $t0, %d", node->left->value);
            writeInst(fp, "", placeHldr, "#load value into $t0");
            break;
        case IDENTIFIER:
            readIdentifier(node->left);
            writeInst(fp, "", "lw $t0, ($t2)", "#load word from left into t0");
            break;
        case CALL:
            readCall(node->left);
            writeInst(fp,"","addu $t0, $v0, 0","#Get call for left side");
            break;
        case EXPR:
            readExpr(node->left);
            sprintf(placeHldr,"lw  $t0, %d($sp)",node->left->symbol->offset*WORDSIZE);
            writeInst(fp,"",placeHldr,"#load word from left to $t0");
            break;
        default:
            printf("Error In Code Generator, Unrecognized Expression Type on Left\n");
            exit(1);
    }

    //store stack pointer at offset size into $t0
    sprintf(placeHldr, "sw  $t0, %d($sp)", node->symbol->offset*WORDSIZE);
    writeInst(fp, "", placeHldr, "#first store value from stack into t0");

    //next we need to do the right side of the expression
    switch (node->right->type){
        case NUMBER:
            sprintf(placeHldr, "li  $t1, %d", node->right->value);
            writeInst(fp, "", placeHldr, "#load value into $t1");
            break;
        case IDENTIFIER:
            readIdentifier(node->right);
            writeInst(fp, "", "lw $t1, ($t2)", "#load word from right into t0");
            break;
        case CALL:
            readCall(node->right);
            writeInst(fp,"","addu $t1, $v0, 0","#Get call for right side");
            break;
        case EXPR:
            readExpr(node->right);
            sprintf(placeHldr,"lw  $t1, %d($sp)",node->right->symbol->offset*WORDSIZE);
            writeInst(fp,"",placeHldr,"#load word from right into $t1");
            break;
        default:
            printf("Error In Code Generator, Unrecognized Expression Type on Right\n");
            exit(1);
    }

    //load back the value from stack pointer
    sprintf(placeHldr, "lw  $t0, %d($sp)", node->symbol->offset*WORDSIZE);
    writeInst(fp, "", placeHldr, "#second load value back from stack into t0");

    //next we need to check the operation that we are doing in the expression
    //since we are doing a 3 register system and we are storing left in $t0 and right in $t1
    //we can just store the answer in $t3
    switch (node->op){
        case ADD:
            writeInst(fp, "", "add  $t0, $t0, $t1", "#add t0 + t1 and store in t0");
            break;
        case MINUS:
            writeInst(fp, "", "sub  $t0, $t0, $t1", "#sub t0 - t1 and store in t0");
            break;
        case MULTIPLY:
            writeInst(fp, "", "mult $t0, $t1", "#multiply t0 and $t1");
            writeInst(fp, "", "mflo $t0", "#move contents into $t0");
            break;
        case DIVIDE:
            writeInst(fp, "", "div $t0, $t1", "#divied t0 by t1");
            writeInst(fp, "", "mflo $t0", "#move contents into $t0");
            break;
        case EQUALTO:
            writeInst(fp, "", "seq  $t0, $t0, $t1", "#statement equal t0 == t1 will be 1");
            break;
        case NOTEQUALTO:
            writeInst(fp,"","sne $t0, $t0, $t1","#If not equal will be 1");
            break;
        case LESSTHANOREQUAL:
            writeInst(fp,"","addi $t1, $t1, 1","#Add one for the lt equal");
            writeInst(fp,"","slt $t0, $t0, $t1","#Will be 1 if LT equal");
            break;
        case LESSTHAN:
            writeInst(fp,"","slt $t0, $t0, $t1","#will be 1 if less than");
            break;
        case GREATERTHAN:
            writeInst(fp,"","slt $t0, $t1, $t0","#will be 1 if greater than");
            break;
        case GREATERTHANOREQUAL:
            writeInst(fp,"","addi $t0, $t0, 1","#add one for GT equal");
            writeInst(fp,"","slt $t0, $t1, $t0","#will be 1 if GT equal");
            break;
        case AND:
            break;
        case OR:
            break;
        case NOT:
            break;
    }

    //store stack pointer at offset size into $t0
    sprintf(placeHldr, "sw  $t0, %d($sp)", node->symbol->offset*WORDSIZE);
    writeInst(fp, "", placeHldr, "#third store value back into stack pointer");

} //end expression node

void readDecision(ASTNode *node){
    /*
                                        MIPS

        if(x == 1) x = x + 1;       bne $t0, 1, ELSE  ---|
                                    add $t0, $t0, 1      |
        else x = x - 1                                   |
                                ELSE: <------------------|
                                    addi $t0, $t0, -1
    */

    char *temp1;
    char *temp2;

    temp1 = createLabel();
    temp2 = createLabel();

    switch(node->right->type) {
            case NUMBER:
                sprintf(placeHldr, "li  $t0, %d", node->right->value);
                writeInst(fp, "", placeHldr, "#load value into $t0 for if stmt");
                break;
            case EXPR:
                readExpr(node->right);
                sprintf(placeHldr, "lw  $t0, %d($sp)", node->right->symbol->offset*WORDSIZE);
                writeInst(fp, "", placeHldr, "#load back the number into $a0");
                break;
            case IDENTIFIER:
                readIdentifier(node->right);
                writeInst(fp, "", "lw  $t0, ($t2)", "#load value from stack");
                break;
            case CALL:
                readCall(node->right);
                break;
    }

    sprintf(placeHldr, "beq $t0, $0, %s", temp1);
    writeInst(fp, "", placeHldr, "#add label for else stmt");

    readAST(node->s1);  
    sprintf(placeHldr, "j   %s", temp2);
    writeInst(fp, "", placeHldr, "#jump over the else statement");

    sprintf(placeHldr, "%s:     ", temp1);
    writeInst(fp, "", placeHldr, "#label for Else");

    //check else statement for a block
    if (node->s2 != NULL){
        readAST(node->s2);
    }

    sprintf(placeHldr, "%s:     ", temp2);
    writeInst(fp, "", placeHldr, "#label for IF");

} //end if else statement node

void readReturn(ASTNode *node){
    //check s2 for an expression, since we dont currently 3/3 have void s2 should never be null
    if (node->s2 != NULL){
        switch(node->s2->type){
            case CALL:
                readCall(node->s2);
                break;
            case NUMBER:
                sprintf(placeHldr, "li $v0, %d", node->s2->value);
                writeInst(fp, "", placeHldr, "#load value into return address $v0");
                break;
            case FLOATNUMBER:
                printf("Return float type mips\n");
                break;
            case CHARACTER:
                printf("Return character type mips\n");
                break;
            case EXPR:
                readAST(node->s2);
                sprintf(placeHldr,"lw  $v0, %d($sp)",node->s2->symbol->mySize*WORDSIZE);
                writeInst(fp,"",placeHldr,"#load word from sp into v0");
                break;
            case IDENTIFIER:
                readIdentifier(node->s2);
                writeInst(fp,"","lw  $v0, ($t2)","#load word from t2 into v0");
                break;
        }
    }
    else {
        //future add for void return

    }
    sprintf(placeHldr, "lw  $ra, %d($sp)", 1*WORDSIZE);
    writeInst(fp, "", placeHldr, "#load 4($sp) into $ra");
    writeInst(fp, "", "lw   $sp, ($sp)", "#load the value at $sp back into ($sp)");
    writeInst(fp, "", "jr   $ra", "");

} //end return node

void readItter(ASTNode *node){
    char * L3;
    char * L4;

    L3 = createLabel();
    L4 = createLabel();

    sprintf(placeHldr, "%s: ", L3);
    writeInst(fp, placeHldr, "      ", "#Start While loop");

    switch (node->right->type) {
        case NUMBER:
            sprintf(placeHldr,"li  $t0, %d",node->right->value);
            writeInst(fp,"",placeHldr,"#Load number into $t0 for while stmt");
            break;
        case EXPR:
            readAST(node->right);
            //sprintf(placeHldr,"lw  $t0, %d($sp)",node->right->symbol->offset*WORDSIZE);
            break;
        case IDENTIFIER:
            readIdentifier(node->right);
            writeInst(fp,"","lw  $t0, ($t2)", "#load word from $t2 into $t0");
            break;
        case CALL:
            readCall(node->right);
            writeInst(fp, "", "lw $t0, ($v0)", "#load value from return");
            break;
    }

    sprintf(placeHldr, "beq $t0 $0 %s", L4);
    writeInst(fp, "", placeHldr, "#while false, jump out");
    
    //This is where we can handle loop unrolling if possible
    /*
        conditions:
            number
            expr with constant and identifier
            expr with two constants

        handling: 
            expressions:
                check left and right for a constant
                if found identify operator
                right now handle ==, <=, and <
                to be safe we will always only unroll the constant value -1
    */
    switch(node->right->type){
        case EXPR:
            if (node->right->right->type == NUMBER && node->right->right->value > 0){
                for (int x = 0; x <= node->right->right->value - 1; x++){
                    readAST(node->s1);
                    writeInst(fp, "", "addi $t3, $t3, 1", "#increment counter by 1");
                }
                break;
            }
            if (node->right->left->type == NUMBER && node->right->left->value > 0){
                for (int x = 0; x <= node->right->left->value - 1; x++){
                    readAST(node->s1);
                    writeInst(fp, "", "addi $t3, $t3, 1", "#increment counter by 1");
                }
                break;
            }
            else {
                readAST(node->s1);
                writeInst(fp, "", "addi $t3, $t3, 1", "#increment counter by 1");
            }
            break;
        default:
            readAST(node->s1);
            writeInst(fp, "", "addi $t3, $t3, 1", "#increment counter by 1");
            break;
    }
    
    sprintf(placeHldr,"j   %s", L3);
    writeInst(fp,"",placeHldr,"#while true, jump to beginning");

    sprintf(placeHldr,"%s:  ",L4);
    writeInst(fp,placeHldr,"  ","#target to stop executing loop");
} //end while node

void readWrite(ASTNode *node){
    switch(node->right->type){
        case NUMBER:
            sprintf(placeHldr, "li  $a0, %d", node->right->value);
            writeInst(fp, "", placeHldr, "#load immediate value into $v0");
            writeInst(fp, "", "li  $v0, 1", "#load immediate 1 into $v0 to indicate integer");
            break;
        case CHARACTER:
            /*sprintf(placeHldr, "li  $a0, %d", node->right->str);
            writeInst(fp, "", placeHldr, "#load immediate value into $v0");
            writeInst(fp, "", "li  $v0, 11", "#load immediate 11 into $v0 to indicate character");*/
            writeInst(fp, "", ".data", "");
            sprintf(placeHldr, "%s: .asciiz \"%s\"", node->right->name, node->right->str);
            writeInst(fp, placeHldr, "", "");
            writeInst(fp, "", ".text", "");
            sprintf(placeHldr, "la $a0, %s", node->right->name);
            writeInst(fp, "", placeHldr, "");
            writeInst(fp, "", "li $v0, 4", "#load this bih up");
            break;
        case FLOATNUMBER:
            sprintf(placeHldr, "li.s  $f12, %f", node->right->fvalue);
            writeInst(fp, "", placeHldr, "#load address of the float");
            writeInst(fp, "", "li  $v0, 2", "#load immediate 2 into $v0 to indicate float");
            break;
        case EXPR:
            readExpr(node->right);
            sprintf(placeHldr, "lw  $a0, %d($sp)",node->right->symbol->offset*WORDSIZE);
            writeInst(fp, "",placeHldr," #fetch expr value");
            writeInst(fp,"","li  $v0, 1"," #put 1 in v0 to print an integer");
            break;
        case IDENTIFIER:
            /*
                We will need to adjust this for incorperation of floats
                li $v0, 1
                1 = int type
                2 = float type
            */
            readIdentifier(node->right);
            switch(node->right->isType) {
                case INTDECL:
                    sprintf(placeHldr, "lw  $a0, %d($t2)", 0);
                    writeInst(fp, "", placeHldr, "#load word from $t2 int0 $a0");
                    sprintf(placeHldr, "li  $v0, %d", readIdType(node->right));
                    writeInst(fp, "", placeHldr, "#load immediate 1 to print Int");
                    break;
                case FLOATDECL:
                    sprintf(placeHldr, "li.s  $v0, %d", readIdType(node->right));
                    writeInst(fp, "", placeHldr, "#load immediate 1 to print Int");
                    break;
                case CHARDECL:
                /*
                    lw $t1, 60($sp)
                    li $t2, 4
                    mult $t1, $t2
                    mflo $t1
                    la $t0, xz
                    add $t2, $t1, $t0
                */
                    if (node->right->symbol->isAFunc == 1){
                        writeInst(fp, "", "li $t2, 4", "#load wordsize into t2 for multiplying");
                        writeInst(fp, "", "mult $t1, $t2", "#multiply the values to get the correct offset");
                        writeInst(fp, "", "mflo $t1", "#move low to t1");
                        sprintf(placeHldr, "la $t0, %s", node->right->name);
                        writeInst(fp, "", placeHldr, "#load address of variable into t0");
                        writeInst(fp, "", "add $t2, $t1, $t0", "#add offset and address to get numb location");
                    }
                    sprintf(placeHldr, "lw  $a0, %d($t2)", node->right->right->value*WORDSIZE);
                    writeInst(fp, "", placeHldr, "#load word from $t2 int0 $a0");
                    sprintf(placeHldr, "li  $v0, %d", 11);
                    writeInst(fp, "", placeHldr, "#load immediate 1 to print Int");
                    break;
            }
            break;
        case CALL:
            readCall(node->right);
            writeInst(fp, "", "lw $a0 0($t2)", "#move return addy to a0");
            writeInst(fp, "", "li $v0, 1", "#load immediate into 1");
            break;
    }
    writeInst(fp, "", "syscall", "");
} //end write node

void readAssign(ASTNode *node){
    if (node->right->symbol->isUsed){
        //x = expr
        //right = x ; s1 = expr
        readAST(node->s1);
        //At this point we need to store the vairable into a register
        //to do this we can pic any register. I pick $t6 
        //we are then loading the variable which will be stored in the stack pointer
        //at the offset * 4
        sprintf(placeHldr, "sw  $t6, %d($sp)", node->symbol->offset*WORDSIZE);
        writeInst(fp, "", placeHldr, "#get value from the stack pointer");

        readIdentifier(node->right);
        switch (node->right->isType){
            case INTDECL:
                sprintf(placeHldr, "lw  $t6, %d($sp)", node->symbol->offset*WORDSIZE);
                writeInst(fp, "", placeHldr, "#get value from the stack pointer");
                writeInst(fp, "", "sw   $t6, ($t2)", "#store word into $t6 from $t2");
        }
    }
} //end assignment node

void readExprStmt(ASTNode *node){
    switch(node->right->type){
        case NUMBER:
            sprintf(placeHldr, "li   $t6, %d", node->right->value);
            writeInst(fp, "", placeHldr, "#load immediate value into register $t6");
            break;
        case FLOATNUMBER:
            /*
                lwc1  $f2, x 		#load ID from .data into register $t2
                li.s  $f3, 12.0
                add.s $f12, $f2, $f3
            */
            sprintf(placeHldr, "li.s  $f3, %f", node->right->fvalue);
            writeInst(fp, "", placeHldr, "#load value into $f12 register");
            writeInst(fp, "", "add.s   $f12, $f2, $f3", "#add number to and original to the $f12 register");
            printf("Do some floating point mips shit later\n");
            break;
        case CHARACTER:
            /*
                create label for inital empty variable
                convert string into character array
                load label address into register
                for length of array
                    insert character at index
                store and done
            */
            sprintf(placeHldr, "la $t0, %s", node->name);
            writeInst(fp, "", placeHldr, "#load variable address into t0");
            char charArr[100] = "";
            strcpy(charArr, node->right->str);
            for (int x = 0; x <= strlen(charArr); x++){
                sprintf(placeHldr, "li $t1, %d", charArr[x]);
                writeInst(fp, "", placeHldr, "#load char into $t1");
                sprintf(placeHldr, "sw $t1, %d($t0)", x*WORDSIZE);
                writeInst(fp, "", placeHldr, "#store char into the variable array");
            }
            break;
        case IDENTIFIER:
            readIdentifier(node->right);
            writeInst(fp,"","lw  $t6, ($t2)", "#Load value from stack in t6 for exprstmt");
            break;
        case CALL:
            readCall(node->right);
            writeInst(fp,"","addu $t6, $v0, 0","#put the return in t6 to use later");
            break;
        case EXPR:
            readAST(node->right);
            sprintf(placeHldr, "lw  $t6, %d($sp)", node->right->symbol->offset*WORDSIZE);
            writeInst(fp, "", placeHldr, "#load offset from stack pointer to $t6");
            break;
    }
} //end expression stmt

void readCall(ASTNode *node){
    if (node->right != NULL){
        int offset;
        offset = node->symbol->mySize*WORDSIZE;
        readArgs(node->right, 1, offset);
    }

    sprintf(placeHldr, "jal %s", node->name);
    writeInst(fp, "", placeHldr, "#jump to the function");
    writeInst(fp, "", "nop", "#to return to the spot we left");
} //end call to func node

void readArgs(ASTNode *node, int numOfArgs, int offset){
    switch (node->right->type)
    {
        case NUMBER:
            sprintf(placeHldr, "li $t0, %d", node->right->value);
            writeInst(fp, "", placeHldr, "#load value from arg into $t0");

            sprintf(placeHldr, "subu $t6, $sp, %d", offset);
            writeInst(fp, "", placeHldr, "#point sp to t0");
            writeInst(fp, "", "sw $sp, ($t6)", "#store old stack pointer");
            writeInst(fp,"","addu $sp, $t6, 0","#move the sp now");
            
            sprintf(placeHldr, "sw $t0, %d($sp)", (numOfArgs+1)*WORDSIZE);
            writeInst(fp, "", placeHldr, "#store argument value into sp");
            writeInst(fp, "", "lw $sp, ($sp)", "#put back stack pointer");
            break;
        case CALL:
            sprintf(placeHldr, "subu $t6, $sp, %d", offset);
            writeInst(fp, "", placeHldr, "#move stack pointer down");
            writeInst(fp, "", "sw $sp, ($t6)", "#store the old stack pointer");
            writeInst(fp, "", "addu $sp, $t6, 0", "#move stack pointer up");

            readCall(node->right);

            sprintf(placeHldr, "sw $t0, %d($sp)", (numOfArgs+1)*WORDSIZE);
            writeInst(fp, "", placeHldr, "#store argument value into sp");
            writeInst(fp, "", "lw $sp, ($sp)", "#put back stack pointer");
            break;
        case IDENTIFIER:
            readIdentifier(node->right);
            writeInst(fp, "", "lw $t0, ($t2)", "#load word into t0");

            sprintf(placeHldr, "subu $t6, $sp, %d", offset);
            writeInst(fp, "", placeHldr, "#move stack pointer down");
            writeInst(fp, "", "sw $sp, ($t6)", "#store the old stack pointer");
            writeInst(fp, "", "addu $sp, $t6, 0", "#move stack pointer up");

            sprintf(placeHldr, "sw $t0, %d($sp)", (numOfArgs+1)*WORDSIZE);
            writeInst(fp, "", placeHldr, "#store argument value into sp");
            writeInst(fp, "", "lw $sp, ($sp)", "#put back stack pointer");
            break;
        case EXPR:
            readExpr(node->right);
            sprintf(placeHldr, "lw $t0, %d($sp)", node->right->symbol->offset*WORDSIZE);
            writeInst(fp, "", placeHldr, "#load word into t0 from stack pointer");

            sprintf(placeHldr, "subu $t6, $sp, %d", offset);
            writeInst(fp, "", placeHldr, "#move stack pointer down");
            writeInst(fp, "", "sw $sp, ($t6)", "#store the old stack pointer");
            writeInst(fp, "", "addu $sp, $t6, 0", "#move stack pointer up");

            sprintf(placeHldr, "sw $t0, %d($sp)", (numOfArgs+1)*WORDSIZE);
            writeInst(fp, "", placeHldr, "#store argument value into sp");
            writeInst(fp, "", "lw $sp, ($sp)", "#put back stack pointer");
            break;
        default:
            printf("Error: Unkown type in argument node\n");
            exit(1);
    }

    if (node->left != NULL){
        readArgs(node->left, numOfArgs + 1, offset);
    }
} //end arguments node

void readIdentifier(ASTNode *node){
    //check for variables in the global scope first
    if (getLineno(node->symbol) == 0){
        if (node->right == NULL){
            switch(node->isType){
                case INTDECL:
                    sprintf(placeHldr, "la   $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $t2");
                    break;
                case FLOATDECL:
                    sprintf(placeHldr, "lwc1   $f2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $f2");
                    break;
                case CHARDECL:
                    printf("Char Ident Global\n");
                    break;
            }
        }
        else {
            //switch is if the variable is an array
            switch(node->right->type){
                case NUMBER:
                    sprintf(placeHldr, "la   $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $t2");
                    writeInst(fp,"","sll $t1, $t3, 2","#add t2 to t3 and store in t3 this is the offset");
                    writeInst(fp, "", "addu $t2, $t2, $t1", "#add t2 and t1 for the offset value incremented by 4");
                    break;
                case FLOATNUMBER:
                    printf("FLOAT Array\n");
                    break;
                case CHARACTER:
                    printf("CHAR Array\n");
                    break;
                case EXPR:
                    sprintf(placeHldr, "la   $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $t2");
                    sprintf(placeHldr, "lw  $t3, %d($sp)", node->right->symbol->offset*WORDSIZE);
                    writeInst(fp, "", placeHldr, "#load offset of array");
                    sprintf(placeHldr, "sll $t3, $t3, %d", WORDSIZE/2);
                    writeInst(fp, "", placeHldr, "#multiply t3 by wordsize");
                    writeInst(fp, "", "add $t2, $t2, $t3", "#add array offset to $t2");
                    break;
                case IDENTIFIER:
                    readIdentifier(node->right);
                    writeInst(fp, "", "lw $t3, ($t2)", "#move value from t2 to t3");
                    sprintf(placeHldr, "sll $t3, $t3, %d", WORDSIZE/2);
                    writeInst(fp, "", placeHldr, "#multiply t3 by wordsize");
                    sprintf(placeHldr, "la   $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $t2");
                    writeInst(fp, "", "add $t2, $t2, $t3", "#add array offset to $t2");
                    break;
                case CALL:
                    readCall(node->right);
                    sprintf(placeHldr, "la   $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $t2");
                    writeInst(fp, "", "addu $t3, $v0, 0", "#move return into t3");
                    sprintf(placeHldr, "sll $t3, $t3, %d", WORDSIZE/2);
                    writeInst(fp, "", placeHldr, "#multiply t3 by wordsize");
                    sprintf(placeHldr, "la   $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID from .data into register $t2");
                    writeInst(fp, "", "add $t2, $t2, $t3", "#add array offset to $t2");
                    break;
            }
        }
    }
    //if not check local variables
    else {
        if (node->right == NULL){
            switch (node->isType){
                case INTDECL:
                    //wrong offset being calculated right now
                    sprintf(placeHldr,"li  $t2, %d",node->symbol->offset*WORDSIZE);
                    writeInst(fp, "",placeHldr,"# Load ID offset into $t2");
                    writeInst(fp, "","add $t2, $t2, $sp","# Create exact mem location for ID");
                    break;
                case CHARDECL:
                    sprintf(placeHldr, "la $t2, %s", node->name);
                    writeInst(fp, "", placeHldr, "#load ID offset into t2");
                    break;
            }
            
        }
        else {
            switch(node->right->type){
                case NUMBER:
                    switch(node->isType){
                        default:
                            sprintf(placeHldr, "li   $t2, %d", node->symbol->offset*WORDSIZE);
                            writeInst(fp, "", placeHldr, "#load offset into t2");
                            sprintf(placeHldr, "li $t3, %d", node->right->value*WORDSIZE);
                            writeInst(fp, "", placeHldr, "#load value offset into t3");
                            writeInst(fp, "", "add $t2, $t2, $t3", "#add t2 and t3 offset together");
                            writeInst(fp, "", "add $t2, $t2, $sp", "#add stack pointer to t2 to get final location");
                        case CHARDECL:
                            sprintf(placeHldr, "lw   $t1, %d($t2)", node->symbol->offset*WORDSIZE);
                            writeInst(fp, "", placeHldr, "#load offset into t1");
                            break;
                    }
                    break;
                case EXPR:
                    readExpr(node->right);
                    sprintf(placeHldr, "li   $t2, %d", node->symbol->offset*WORDSIZE);
                    writeInst(fp, "", placeHldr, "#load offset into t2");
                    sprintf(placeHldr, "lw $t3, %d($sp)", node->right->symbol->offset*WORDSIZE);
                    writeInst(fp, "", placeHldr, "#load offset from stack pointer");
                    sprintf(placeHldr, "sll $t3, $t3, %d", WORDSIZE/2);
                    writeInst(fp, "", placeHldr, "#multiply t3 by wordsize");
                    writeInst(fp, "", "add $t2, $t2, $t3", "#add t2 and t3 offset together");
                    writeInst(fp, "", "add $t2, $t2, $sp", "#add stack pointer to t2 to get final location");
                    break;
                case IDENTIFIER:
                    readIdentifier(node->right);
                    sprintf(placeHldr, "lw $t3, %d($sp)", node->right->symbol->offset*WORDSIZE);	                    writeInst(fp, "", "lw $t3, ($t2)", "#load offset from stack pointer");
                    writeInst(fp, "", placeHldr, "#load offset from stack pointer");
                    sprintf(placeHldr, "sll $t3, $t3, %d", WORDSIZE/2);
                    writeInst(fp, "", placeHldr, "#multiply t3 by wordsize");
                    sprintf(placeHldr, "li   $t2, %d", node->symbol->offset*WORDSIZE);
                    writeInst(fp, "", placeHldr, "#load offset into t2");
                    writeInst(fp, "", "add $t2, $t2, $t3", "#add t2 and t3 offset together");
                    writeInst(fp, "", "add $t2, $t2, $sp", "#add stack pointer to t2 to get final location");
                    break;
                case CALL:
                    readCall(node->right);
                    writeInst(fp, "", "addu $t3, $v0, 0", "#add return addy to t3");
                    sprintf(placeHldr, "sll $t3, $t3, %d", WORDSIZE/2);
                    writeInst(fp, "", placeHldr, "#multiply t3 by wordsize");
                    sprintf(placeHldr, "li   $t2, %d", node->symbol->offset*WORDSIZE);
                    writeInst(fp, "", placeHldr, "#load offset into t2");
                    writeInst(fp, "", "add $t2, $t2, $t3", "#add t2 and t3 offset together");
                    writeInst(fp, "", "add $t2, $t2, $sp", "#add stack pointer to t2 to get final location");
                    break;
                case CHARACTER:
                    printf("FOund ID in scope");
                    printf("CHAR Array\n");
                    break;
            }
        }
    }
} //end identifier node

void initiate(){
    writeInst(fp, ".data", "", "");
    writeInst(fp, "", "nl: .asciiz \"\\n\"", "");
    writeInst(fp, ".text", "", "");
}

void readAST(ASTNode *node){
    if (node == NULL) return;
    else {
        switch (node->type) {
            case VARDECL:
                switch(node->isType){
                    case INTDECL:
                        if (node->symbol->lines->lineno == 0){
                            readVariable(node);
                        }
                        break;
                    case CHARDECL:
                        readVariable(node);
                        break;
                }
                    
                break;
            case FUNCDECL:
                readFunction(node);
                break;
            case EXPRSTMT:
                readExprStmt(node);
                break;
            case EXPR:
                readExpr(node);
                break;
            case IDENTIFIER:
                readIdentifier(node);
                break;
            case BLOCK:
                readAST(node->right);
                break;
            case DECISIONSTMT:
                readDecision(node);
                break;
            case RETURNSTMT:
                readReturn(node);
                break;
            case ITTERSTMT:
                readItter(node);
                break;
            case WRITESTMT:
                readWrite(node);
                break;
            case READSTMT:
                readIdentifier(node->right);
                writeInst(fp, "", "li $v0, 5", "#5 means read integer");
                writeInst(fp, "", "syscall", "#syscall to read");
                writeInst(fp, "", "sw $v0, 0($t2)", "#store number into the t2 stack");
                break;
            case ASSIGNSTMT:
                readAssign(node);
                break;
            case CALL:
                readCall(node);
                break;
            case WRITELN:
                writeInst(fp, "", "lw $a0, nl", "#load newline into a0");
                writeInst(fp, "", "li, $v0, 11", "#string type");
                writeInst(fp, "", "syscall", "");
                break;
            default:
                printf("Error Unknown node type in AST\n");
                exit(1);
        }
        if(node->type != EXPR){
            readAST(node->left);
        }
    }

} //end function will analyze the entire AST and write the nessicary assembly
