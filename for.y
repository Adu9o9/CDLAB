%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *s);
%}

%token FOR ID NUM LE GE EQ NE OR AND

/* Define Precedence (Lowest to Highest) */
%right '='
%left OR AND
%left '<' '>' LE GE EQ NE
%left '+' '-'
%left '*' '/'

%%
// Start Rule
Program: stmt { printf("\nResult: Valid FOR Loop Syntax!\n"); exit(0); } ;

// The core FOR loop structure
stmt: FOR '(' exp ';' exp ';' exp ')' body ;

// The Body can be {} block, a single statement with ;, or a nested FOR loop
body: '{' stmt_list '}' 
    | exp ';' 
    | stmt 
    ;

// Inside a {}, there can be multiple statements or none
stmt_list: stmt_list exp ';' 
         | stmt_list stmt
         | /* epsilon (empty block) */
         ;

// An Expression handles init, condition, increment, and assignments
exp: ID '=' exp
   | exp '+' exp
   | exp '-' exp
   | exp '*' exp
   | exp '/' exp
   | exp '<' exp
   | exp '>' exp
   | exp LE exp
   | exp GE exp
   | exp EQ exp
   | exp NE exp
   | exp OR exp
   | exp AND exp
   | ID '+' '+'    /* Handles i++ */
   | ID '-' '-'    /* Handles i-- */
   | ID
   | NUM
   | /* epsilon (allows empty expressions like for(;;) ) */
   ;

%%

void yyerror(char *s) {
    printf("\nResult: Invalid FOR Loop Syntax!\n");
    exit(1);
}

int main() {
    printf("Compiler Lab - FOR Loop Checker\n");
    printf("Enter a C FOR loop:\n");
    yyparse();
    return 0;
}
