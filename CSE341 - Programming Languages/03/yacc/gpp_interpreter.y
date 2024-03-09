%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include "gpp_interpreter.h"
    extern FILE *yyin;
    void yyerror(char *);
    int yylex(void);
    int result=1;
    void printArray(int* arr);
    int findAndSetID(char*,int);
    int findID(char*);
    void convert(char*, char*, int flag);
    void sum(char* ret, char* first, char* second);
    char* itoa(int num, char* buffer, int base);
    void init();
    typedef union value{
            int num; 
            int* list;
    }value;
    typedef struct Variable{
        char id[10]; // Variable Name
        char type; // Int = I || Char = C || List = L
        value val; 
        
    }Variable;
    typedef struct VariableArray{
        int size;
        Variable* vars;
    }VariableArray;
%}
%union {
    int val;
    char valf[100];
    char id[100];
}
%start START

%token KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL KW_LIST KW_SET KW_DEFFUN KW_DEFVAR
%token KW_FOR KW_IF KW_WHILE KW_EXIT KW_LOAD KW_DISP KW_TRUE KW_FALSE
%token OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_DBLMULT OP_OC OP_CC OP_COMMA
%token COMMENT
%token <valf> VALUEF
%token <id> IDENTIFIER

%type <valf> ExpI
%type <val> ExpB

%%

START: COMMENT {}
    | START COMMENT {}
    | OP_OP KW_EXIT OP_CP { exit(0);}
    | START OP_OP KW_EXIT OP_CP { exit(0);}
    | ExpI { printf("%s\n", $1); }
    | START ExpI { printf("%s\n", $2); }
    | ExpB { if($1 == 1){printf("true\n");} else{printf("false\n");} }
    | START ExpB { if($2 == 1){printf("true\n");} else{printf("false\n");} }
    ;

ExpI:
    OP_OP OP_PLUS ExpI ExpI OP_CP {sum($$, $3, $4);}
    |
    OP_OP OP_MINUS ExpI ExpI OP_CP {sum($$, $3, $4);}
    |
    OP_OP OP_MULT ExpI ExpI OP_CP {sum($$, $3, $4);}
    |
    OP_OP OP_DIV ExpI ExpI OP_CP {sum($$, $3, $4);}
    |
    //IDENTIFIER {strcpy($$, findID($1));}
    //|
    VALUEF {strcpy($$, $1);}
    |
    //OP_OP KW_SET IDENTIFIER ExpI OP_CP {strcpy($$, findAndSetID($3,$4));}
    //|
    OP_OP KW_IF ExpB ExpI OP_CP {
        if (1 == $3)
            strcpy($$, $4);
        else
            strcpy($$, "0f1");
    }
    |
    OP_OP KW_IF ExpB ExpI ExpI OP_CP {
        if (1 == $3)
            strcpy($$, $4);
        else
            strcpy($$, $5);
    }
    ;

ExpB:
    OP_OP KW_AND ExpB ExpB OP_CP {$$= $3 && $4;}
    |
    OP_OP KW_OR ExpB ExpB OP_CP {$$= $3 || $4;}
    |
    OP_OP KW_NOT ExpB OP_CP {$$= !$3;}
    |
    OP_OP KW_EQUAL ExpB ExpB OP_CP {$$= ($3==$4);}
    |
    OP_OP KW_EQUAL ExpI ExpI OP_CP {$$= ($3==$4);}
    |
    OP_OP KW_LESS ExpI ExpI OP_CP {$$= ($3<$4);}
    |
    KW_TRUE {$$=1;}
    |
    KW_FALSE {$$=0;}
    ;

%%

VariableArray variables;

void init(){
    variables.size=0;
    variables.vars=NULL;
}
int findAndSetID(char* id,int num){
    if(variables.size==0 || variables.vars==NULL){
        variables.vars=(Variable*) malloc(1);
        strcpy(variables.vars[0].id,id);
        variables.vars[0].type='I';
        variables.vars[0].val.num=num;
        variables.size=1;
        return num;
    }
    for(int i=0;i< variables.size;i++){
        if(strcmp(variables.vars[i].id,id)==0){
            variables.vars[i].type='I';
            variables.vars[i].val.num=num;
            return num;
        }
    }
    /*if not exist ,create*/
    variables.vars=(Variable*)realloc(variables.vars,sizeof(Variable)*(variables.size+1));
    strcpy(variables.vars[variables.size].id,id);
    variables.vars[variables.size].type='I';
    variables.vars[variables.size].val.num=num;
    variables.size++;
    
    return num;
}
int findID(char* id){
    for(int i=0;i< variables.size;i++){
        if(strcmp(variables.vars[i].id,id)==0)
            return  variables.vars[i].val.num;
    }
    printf("Does not exist %s\n",id);
    exit(-1);
}
void convert(char* value, char* ret, int slct){
    char first[100], second[100];
    int flag;
    for (int i = 0; i < 100; ++i){
        if (value[i] != 'f')
            first[i] = value[i];
        else if (value[i] == 'f'){
            first[i] = '\0';
            flag = i + 1;
            i = 100;
        }
    }
    for (int i = 0; i < 100; ++i){
        if (value[i + flag] != '\0')
            second[i] = value[i + flag];
        else {
            second[i] = value[i + flag];
            i = 100;
        }
    }
    if (slct == 0)
        strcpy(ret, first);
    else
        strcpy(ret, second);
}
void sum(char* ret, char* first, char* second){
    char f1[100], f2[100], s1[100], s2[100], r1[100], r2[100];

    convert(first, f1, 0);
    convert(first, f2, 1);
    convert(second, s1, 0);
    convert(second, s2, 1);

    itoa((atoi(f1) * atoi(s2) + atoi(f2) * atoi(s1)), r1, 10);
    itoa((atoi(f2) * atoi(s2)), r2, 10);
    strcat(r1, "f");
    strcat(r1, r2);

    strcpy(ret, r1);
}
char* itoa(int num, char* buffer, int base){  
    int current = 0;  
    if (num == 0) {  
        buffer[current++] = '0';  
        buffer[current] = '\0';  
        return buffer;  
    }  
    int num_digits = 0;  
    if (num < 0) {  
        if (base == 10) {  
            num_digits ++;  
            buffer[current] = '-';  
            current ++;  
            num *= -1;  
        }  
        else  
            return NULL;  
    }  
    num_digits += (int)floor(log(num) / log(base)) + 1;  
    while (current < num_digits){  
        int base_val = (int) pow(base, num_digits-1-current);  
        int num_val = num / base_val;  
        char value = num_val + '0';  
        buffer[current] = value;  
        current ++;  
        num -= base_val * num_val;  
    }  
    buffer[current] = '\0';  
    return buffer;  
}
int main(int argc, char **argv)
{
    init();
     while(1){
            yyparse();

     }

    return 0;
}
/*Prints List*/
void printArray(int* arr){
    printf("(");
    if(arr!=NULL){
        int size=arr[0];
        for(int i=1; i<=size;i++)
            printf("%d ",arr[i]);
    }
    printf(")\n");
}
/* Yacc Error Handler */
void yyerror(char * s){  
    printf ("%s\n", s);
    exit(0);
}