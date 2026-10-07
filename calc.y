%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *s);
%}

/* Define Tokens */
%token NUM NL

/* Define Operator Precedence and Associativity (Bottom is Highest Priority) */
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

/* Grammar Rules and Semantic Actions */
stmt: exp NL { printf("Result: %d\n", $1); exit(0); } ;

exp: exp '+' exp    { $$ = $1 + $3; }
   | exp '-' exp    { $$ = $1 - $3; }
   | exp '*' exp    { $$ = $1 * $3; }
   | exp '/' exp    { 
        if ($3 == 0) { 
            yyerror("Divide by Zero Error!"); 
        } else { 
            $$ = $1 / $3; 
        } 
     }
   | '(' exp ')'    { $$ = $2; }
   | NUM            { $$ = $1; }
   ;

%%

void yyerror(char *s) {
    printf("Error: %s\n", s);
    exit(1);
}

int main() {
    printf("Compiler Lab - YACC Calculator\n");
    printf("Enter arithmetic expression (e.g., 2+3*4): ");
    yyparse();
    return 0;
}
