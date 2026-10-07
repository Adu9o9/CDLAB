%{
#include "y.tab.h"
%}

%%
[0-9]+                  { return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[\t ]                   { /* Ignore whitespace */ }
\n                      { return NL; }
.                       { return yytext[0]; } /* Pass +, -, *, /, (, ) */
%%

int yywrap() { return 1; }
