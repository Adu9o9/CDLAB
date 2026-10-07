%{
#include "y.tab.h"
%}

%%
"for"                   { return FOR; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[0-9]+                  { return NUM; }

"<="                    { return LE; }
">="                    { return GE; }
"=="                    { return EQ; }
"!="                    { return NE; }
"||"                    { return OR; }
"&&"                    { return AND; }

[\t \n]                 { /* Ignore whitespace and newlines */ }
.                       { return yytext[0]; } /* Pass (, ), {, }, ;, =, +, etc. directly */
%%

int yywrap() { return 1; }
