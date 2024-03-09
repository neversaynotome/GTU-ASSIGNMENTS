%{
	#include <stdio.h>
    #include <ctype.h>
    #include "gpp_interpreter.h"
    void yyerror(char *);
    extern YYSTYPE yylval; 
	int FLAG = 1;
%}

%%

and						{return KW_AND;}
or						{return KW_OR;}
not						{return KW_NOT;}
equal					{return KW_EQUAL;}
nil						{return KW_NIL;}
list					{return KW_LIST;}
set						{return KW_SET;}
defvar					{return KW_DEFVAR;}
deffun					{return KW_DEFFUN;}
while					{return KW_WHILE;}
if						{return KW_IF;}
exit					{return KW_EXIT;}
load					{return KW_LOAD;}
disp					{return KW_DISP;}
true					{return KW_TRUE;}
false					{return KW_FALSE;}

[a-zA-Z_][a-zA-Z0-9_]*	{return IDENTIFIER;}
["]["]					{return OP_CC;}
([0]|[1-9])*[f][1-9]* 	{return VALUEF;}
[;;].*					{return COMMENT;}
[+]						{return OP_PLUS;}
[-]						{return OP_MINUS;}
[/]						{return OP_DIV;}
[*]						{return OP_MULT;}
[**]					{return OP_DBLMULT;}
[,]						{return OP_COMMA;}
[(]						{return OP_OP;}
[)]						{return OP_CP;}
["]								{
		if (FLAG){
			printf("OP_OC\n");
			FLAG = 0;
		}
		else {
			printf("OP_CC\n");
			FLAG = 1;
		}
			
}

[[:space:]]+

[a-zA-Z]*[,+-/*]	 	  	  {printf("LEXICAL ERROR: string can not be operand %s.\n", yytext);}
[,][A-zA-Z0-9+-/*,]*	 	  {printf("LEXICAL ERROR: invalid usage of OP_COMMA %s.\n", yytext);}
[+][A-zA-Z0-9,-/*+]*	 	  {printf("LEXICAL ERROR: operand not found %s.\n", yytext);}
[-][A-zA-Z0-9+,/*-]*	 	  {printf("LEXICAL ERROR: operand not found %s.\n", yytext);}
[/][A-zA-Z0-9+-,*/]*	 	  {printf("LEXICAL ERROR: operand not found %s.\n", yytext);}
[*][A-zA-Z0-9+-,/*]*	 	  {printf("LEXICAL ERROR: operand not found %s.\n", yytext);}
[0][0-9]*				 	  {printf("LEXICAL ERROR: leading zeros %s.\n", yytext);}
[0-9][a-zA-Z0-9_]*			  {printf("LEXICAL ERROR: invalid Identifier %s.\n", yytext);}
.		 				 	  {printf("LEXICAL ERROR: dot is for %s.\n", yytext);}

%%

int yywrap(){}