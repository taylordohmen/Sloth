sloth: lex.yy.o parser.tab.o parsetree.o executor.o
	g++ executor.o parsetree.o lex.yy.o parser.tab.o -o sloth

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.o: parser.tab.c parsetree.o
	gcc -c parser.tab.c

parser.tab.h: parser.tab.c
parser.tab.c: parser.y
	bison -d parser.y

executor.o: executor.cpp parsetree.o
	g++ -c -std=c++11 executor.cpp

parsetree.o: parsetree.c parsetree.h
	gcc -c parsetree.c

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o sloth