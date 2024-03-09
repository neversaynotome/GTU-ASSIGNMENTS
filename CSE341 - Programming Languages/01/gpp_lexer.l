%{
	int FLAG = 1;
%}

%%

and						{printf("AND : KW_AND\n");}
or						{printf("or : KW_OR\n");}
not						{printf("not : KW_NOT\n");}
equal					{printf("equal : KW_EQUAL\n");}
less					{printf("less : KW_LESS\n");}
nil						{printf("nil : KW_NIL\n");}
list					{printf("list : KW_LIST\n");}
append					{printf("append : KW_APPEND\n");}
concat					{printf("concat : KW_CONCAT\n");}
set						{printf("set : KW_SET\n");}
deffun					{printf("deffun : KW_DEFFUN\n");}
for						{printf("for : KW_FOR\n");}
if						{printf("if : KW_IF\n");}
exit					{printf("exit : KW_EXIT\n");return 0;}
load					{printf("load : KW_LOAD\n");}
disp					{printf("disp : KW_DISP\n");}
true					{printf("true : KW_TRUE\n");}
false					{printf("false : KW_FALSE\n");}

[a-zA-Z_][a-zA-Z0-9_]*	{printf("%s : IDENTIFIER\n",yytext);}
["]["]					{printf("%s : OP CC\n",yytext);}
["](.*?)["]				{printf("%s : VALUESTR\n",yytext);}
[0-9]|[1-9][0-9]*		{printf("%s : VALUEI\n",yytext);}
([0]|[1-9])*[f][1-9]* 	{printf("%s : VALUEF\n",yytext);}
[;;].*					{printf("%s : COMMENT\n",yytext);}
[+]						{printf("+ : OP_PLUS\n");}
[-]						{printf("- : OP_MINUS\n");}
[/]						{printf("/ : OP_DIV\n");}
[*]						{printf("* : OP_MULT\n");}
[**]					{printf("** : OP_DBLMULT\n");}
[,]						{printf(", : OP_COMMA\n");}
[(]						{printf("( : OP_OP\n");}
[)]						{printf(") : OP_CP\n");}
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
int main(int argc, char **argv){

	if(argc > 1){ 
		yyin = fopen(argv[1], "r");
		yylex();
	}
	else{	
		yyin = stdin;
		printf("Ready for input\n");
	}

	yylex();
	return 0;
}