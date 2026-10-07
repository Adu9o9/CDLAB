%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *s);
%}

%token NUMBER ID NL
%left '+' '-'
%left '*' '/'

%%
// Start Rule
stmt: E NL { printf("Result: Valid Arithmetic Expression!\n"); exit(0); } ;

// Expression Rules
E: E '+' E
 | E '-' E
 | E '*' E
 | E '/' E
 | '(' E ')'
 | NUMBER
 | ID
 ;
%%

void yyerror(char *s) {
    printf("Result: Invalid Arithmetic Expression!\n");
    exit(1);
}

int main() {
    printf("Enter expression (e.g., a + 5 * (b - 2)):\n");
    yyparse();
    return 0;
}
