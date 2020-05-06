%{
#include "parser.tab.h"
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> 	// for sleep()
//variables
int chars = 0;
int words = 0;
int lines = 0;
int nConst = 0;
int nSymbols = 0;
int errors = 0;
int spaces = 5;
%}
%start COMMENT2
%option noyywrap yylineno

digit [0-9]
character [a-zA-Z]
id [_a-zA-Z][a-zA-Z0-9_]*
newline \n
whitespace [ ]+
%%

<COMMENT2>[^*]+  ;
<COMMENT2>\*[^/] ;
<COMMENT2>\*\/	 BEGIN 0;		/* end comment */
"/*"		     BEGIN COMMENT2;

[ \t\n]                 ;

int                     {words++; chars += strlen(yytext); return(INT_P);}
char                    {words++; chars += strlen(yytext); return(CHAR_P);}
float					{words++; chars += strlen(yytext); return(FLOAT_P);}
print                   {words++; chars += strlen(yytext); printf("%s \t\t RESERVED WORD\n", yytext);}
if                      {words++; chars += strlen(yytext); return(IF_P);}
else                    {words++; chars += strlen(yytext); return(ELSE_P);}
return                  {words++; chars += strlen(yytext); return(RETURN_P);}
while                   {words++; chars += strlen(yytext); return(WHILE_P);}
write                   {words++; chars += strlen(yytext); return(WRITE_P);}
writeln                 {words++; chars += strlen(yytext); return(WRITELN_P);}
break                   {words++; chars += strlen(yytext); return(BREAK_P);}
read                    {words++; chars += strlen(yytext); return(READ_P);}

"+"                     {nSymbols++; return(ADD_P);}
"-"                     {nSymbols++; return(MINUS_P);}
"*"                     {nSymbols++; return(MULTIPLY_P);}
"/"                     {nSymbols++; return(DIVIDE_P);}
"=="                    {nSymbols++; return(EQUALTO_P);}
"!="                    {nSymbols++; return(NOTEQUALTO_P);}
"<"                     {nSymbols++; return(LESSTHAN_P);}
"<="                    {nSymbols++; return(LESSTHANOREQUAL_P);}
">"                     {nSymbols++; return(GREATERTHAN_P);}
">="                    {nSymbols++; return(GREATERTHANOREQUAL_P);}
"&&"                    {nSymbols++; return(AND_P);}
"||"                    {nSymbols++; return(OR_P);}
"="                     {nSymbols++; return(EQUAL_P);}
"("                     {nSymbols++; return(LP_P);}
")"                     {nSymbols++; return(RP_P);}
"{"                     {nSymbols++; return(LCB_P);}
"}"                     {nSymbols++; return(RCB_P);}
"["                     {nSymbols++; return(LB_P);}
"]"                     {nSymbols++; return(RB_P);}
"\""                    {nSymbols++; return(DIVIDE_P);}
","                     {nSymbols++; return(COMMA_P);}
";"                     {nSymbols++; return(SEMICOLON_P);}
"!"                     {nSymbols++; return(NOT_P);}

{digit}+{character}+    {errors++; printf("%s \t\t ERROR INVALID TOKEN\n", yytext);}
{id}+                   {words++; chars += strlen(yytext); yylval.string = strdup(yytext); return(ID_P);}
{digit}+                {nConst++; yylval.value = atoi((const char *)yytext); return(CONSTANT_INT_P);}
{digit}+\.{digit}+    	{nConst++; yylval.fvalue = atof((const char *)yytext); return(CONSTANT_FLOAT_P);}
\"(.*?)\"				{words++; chars += strlen(yytext); yylval.string = strdup(yytext); return(CONSTANT_CHAR_P);} //single quote character not working
\'(.*?)\'				{words++; chars += strlen(yytext); yylval.string = strdup(yytext); return(CONSTANT_CHAR_P);} //single quote character not working

{whitespace}*           {}
{newline}*              {}

.                       {errors++; fprintf (stderr, "ERROR IN Lexer: %s\nLine Number: %i\n", yytext, yylineno);}
%%
void print2DUtil(ASTNode *t, int space){
		// Base case  
		if (t == NULL)
			return;

		// Increase distance between levels  
		space += spaces;

		// Process right child first  
		print2DUtil(t->right, space);

		// Print current node's data after space  
		// count
		printf("\n");  
		for (int i = spaces; i < space; i++)
			printf(" ");
		switch (t->type) {
			case EXPR:
				printf("%s ",t->name);
				printOpType(t);
				break;
			case DECISIONSTMT:
				printf("%s",t->s2->name);
				print2DUtil(t->s2, space);
				break;
			case RETURNSTMT:
				printf("return");
				break;
			case ASSIGNSTMT:
				printf("%s",t->s1->name);
				print2DUtil(t->s1, space);
				break;
			case NUMBER:
				printf("%d",t->value);
				break;
			case FLOATNUMBER:
				printf("%f",t->fvalue);
				break;
			case CHARACTER:
				printf("%s",t->str);
				break;
			default:
				printf("%s",t->name, t->type);
				break;
		}
		// Process left child  
		print2DUtil(t->left, space);
}

int main(int argc, char *argv[]){
	double time_spent = 0.0;
	clock_t begin = clock();
	static int GTEMP = 0;
    FILE *fps;
    fps = fopen("program.gcupl", "r");
    yyin = fps;
    initSymTab();
    yyparse();
    /*printf("%d characters, %d words %d constants, %d symbols\n", chars, words, nConst, nSymbols);
	printf("Interpreting Tree to Intermediate Code\n");
    printTree(0, prog);*/
	fp = fopen("out.a", "w");
	/*printf("Drawing Tree\n");
	printf("\nWriting Mips\n");*/
	print2DUtil(prog, 1);
	initiate();
	readAST(prog);
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\nTime elpased is %f seconds\n", time_spent);
    return 0;
}