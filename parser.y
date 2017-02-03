%{
	#include <stdio.h>
	#include "parsetree.h"
	int yywrap();
	void yyerror(const char* str);
	struct Node* result;
%}

%union {
	char* var;
	double value;
	struct Node* node;
}

%token <var> IDENTIFIER 
%token <value> VALUE 
%token NOT 
%token TIMES DIVIDE
%token PLUS MINUS 
%token LESS GREATER LESSEQ GREATEREQ EQUALS NEQUALS 
%token AND OR 
%token SEMICOLON 
%token ASSIGN 
%token OPAREN CPAREN 
%token BEG
%token END 
%token IF 
%precedence THEN 
%precedence ELSE 
%token WHILE
%token DO 
%token PRINT 
%token INPUT 
%token STATEMENT

%type <node> prog stmts stmt expr id orterm andterm compterm addterm factor notterm

%error-verbose

%%

prog: stmts { result = make_node(STATEMENT, 0, "");
			attach_node(result, $1);
			}

stmts: stmt stmts { $$ = make_node(STATEMENT, 0,"");
					attach_node($$, $1);
					attach_node($$, $2);
					}
	| stmt { $$ = make_node(STATEMENT, 0, ""); 
			attach_node($$, $1);
			}
	| BEG stmts END { $$ = make_node(STATEMENT, 0, "");
					attach_node($$, $2);
					}

stmt: id ASSIGN expr SEMICOLON { $$ = make_node(ASSIGN, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| PRINT expr SEMICOLON { $$ = make_node(PRINT, 0, "");
							attach_node($$, $2);
							}
	| WHILE expr DO stmts { $$ = make_node(WHILE, 0, "");
							attach_node($$, $2);
							attach_node($$, $4);
							}
	| IF expr THEN stmts { $$ = make_node(IF, 0, "");
							attach_node($$, $2);
							attach_node($$, $4);
							}
	| IF expr THEN stmts ELSE stmts { $$ = make_node(IF, 0, "");
									attach_node($$, $2);
									attach_node($$, $4);
									attach_node($$, $6);
									}

expr: expr OR orterm { $$ = make_node(OR, 0, "");
						attach_node($$, $1);
						attach_node($$, $3);
						}
	| orterm {}

orterm: orterm AND andterm { $$ = make_node(AND, 0, "");
							attach_node($$, $1);
							attach_node($$, $3);
							}
	| andterm {}

andterm: andterm LESS compterm { $$ = make_node(LESS, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| andterm LESSEQ compterm { $$ = make_node(LESSEQ, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| andterm EQUALS compterm { $$ = make_node(EQUALS, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| andterm NEQUALS compterm { $$ = make_node(NEQUALS, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| andterm GREATER compterm { $$ = make_node(GREATER, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| andterm GREATEREQ compterm { $$ = make_node(GREATEREQ, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
	| compterm {}

compterm: compterm PLUS addterm { $$ = make_node(PLUS, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
		| compterm MINUS addterm { $$ = make_node(MINUS, 0, "");
									attach_node($$, $1);
									attach_node($$, $3);
									}
		| addterm {}

addterm: addterm TIMES factor { $$ = make_node(TIMES, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
		| addterm DIVIDE factor { $$ = make_node(DIVIDE, 0, "");
								attach_node($$, $1);
								attach_node($$, $3);
								}
		| factor {}

factor: NOT notterm { $$ = make_node(NOT, 0, "");
					attach_node($$, $2);
					}
	| notterm {}

notterm: OPAREN expr CPAREN {}
	| VALUE { $$ = make_node(VALUE, $1, ""); }
	| IDENTIFIER { $$ = make_node(IDENTIFIER, 0, $1); }
	| INPUT { $$ = make_node(INPUT, 0, ""); }


id: IDENTIFIER { $$ = make_node(IDENTIFIER, 0, $1); }

%%

int yywrap() {
	return 1;
}

void yyerror(const char* str) {
	fprintf(stderr, "COMPILER ERROR: '%s'.\n", str);
}

int main(int argc, char **argv) {
	stdin = fopen(argv[1], "r");
	yyparse();
	print_tree(result, 0);
	return 0;
}
