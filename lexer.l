%{
	#include <stdio.h>
	#include "parser.tab.h"
%}

%option noyywrap

DIGIT [0-9]
CHAR [a-zA-Z]

%%
[\t\n] {}
" " {}
"%".* {}
"+" {return PLUS;}
"-" {return MINUS;}
"/" {return DIVIDE;}
"*" {return TIMES;}
"<" {return LESS;}
">" {return GREATER;}
"<=" {return LESSEQ;}
">=" {return GREATEREQ;}
"==" {return EQUALS;}
"!=" {return NEQUALS;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
";" {return SEMICOLON;}
":=" {return ASSIGN;}
"(" {return OPAREN;}
")" {return CPAREN;}
"begin" {return BEG;}
"end" {return END;}
"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"while" {return WHILE;}
"do" {return DO;}
"print" {return PRINT;}
"input" {return INPUT;}
(_|{CHAR})(_|{DIGIT}|{CHAR})* {yylval.var = yytext; return IDENTIFIER;}
({DIGIT})*"."?{DIGIT}*  {yylval.value = atof(yytext); return VALUE;}

%%
