
sloth: lex.yy.c parser.tab.c parsetree.o
	gcc parsetree.o lex.yy.c parser.tab.c -o sloth

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.h: parser.tab.c
parser.tab.c: parser.y
	bison -d parser.y

parsetree.o: parsetree.c parsetree.h
	gcc -c parsetree.c

clean:
	rm -f calc lex.yy.c parser.tab.h parser.tab.c *.o