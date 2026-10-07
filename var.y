%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *s);
%}

%token LETTER DIGIT NL

%%
// The Start Rule
stmt: var NL { printf("Result: Valid Identifier!\n"); exit(0); } ;

// A variable MUST start with a LETTER
var: LETTER rest ;

// The rest can be letters, digits, or empty (epsilon)
rest: LETTER rest 
    | DIGIT rest 
    | /* epsilon */ 
    ;
%%

void yyerror(char *s) {
    printf("Result: Invalid Identifier!\n");
    exit(1);
}

int main() {
    printf("Compiler Lab - Valid Variable Checker\n");
    printf("Enter variable name: ");
    yyparse();
    return 0;
}
lex var.l

yacc -d var.y (The -d generates y.tab.h)

gcc lex.yy.c y.tab.c -w (The -w suppresses annoying warnings)

./a.out
