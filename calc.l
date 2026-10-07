%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
// extern int yylval; (Automatically included by y.tab.h in modern YACC)
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUM; }
[\t ]       { ; } /* Ignore spaces */
\n          { return NL; }
.           { return yytext[0]; } /* Pass operators (+, -, *, /, (, )) to YACC */
%%

int yywrap() { return 1; }
