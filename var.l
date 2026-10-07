%{
#include "y.tab.h" // Links Lex to YACC's token definitions
%}

%%
[a-zA-Z]    { return LETTER; }
[0-9]       { return DIGIT; }
\n          { return NL; }
.           { return yytext[0]; } /* Pass any invalid char (like @ or !) directly to Yacc */
%%

int yywrap() { return 1; }
