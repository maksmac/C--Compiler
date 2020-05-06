CC = clang

CFLAGS = -Wall -pedantic -DYYDEBUG

flexBison: lex.yy.c parser.tab.c parser.tab.h
	$(CC) $(CFLAGS) -o test parser.tab.c lex.yy.c
	./test

symtab: lex.yy.c SymbolTable/symbolTable.h SymbolTable/symbolTable.c
	$(CC) $(CFLAGS) -o test SymbolTable/symbolTable.c lex.yy.c
	./test

test: test.c SymbolTable/symbolTable.h SymbolTable/symbolTable.c
	$(CC) $(CFLAGS) -o test SymbolTable/symbolTable.c test.c
	./test

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean:
	rm -f *.o
	rm -f *~
	rm -f *.exe
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h
	rm -f test