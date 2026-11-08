%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char target[5]; // Global array to store the 4-character substring

// Helper function to convert a string to lowercase
void to_lowercase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
%}

%%
.*\n    { 
            char temp[1000];
            strcpy(temp, yytext);
            to_lowercase(temp); // Make input lowercase for case-insensitive matching
            
            // strstr() checks if the 'target' substring exists inside 'temp'
            if (strstr(temp, target) != NULL) {
                printf("Result: Rejected (Contains '%s')\n", target);
            } else {
                printf("Result: Accepted -> %s", yytext);
            }
        }
%%

int main() {
    char name[50];
    
    printf("Enter your name: ");
    scanf("%s", name);
    
    // Extract the first 4 characters and force them to lowercase
    strncpy(target, name, 4);
    target[4] = '\0';
    to_lowercase(target);
    
    printf("Target substring to reject: '%s'\n", target);
    printf("Enter strings to test (Ctrl+D to stop):\n");
    
    // CRITICAL: scanf leaves a newline ('\n') in the input buffer. 
    // We must clear it, or yylex() will instantly read a blank line.
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    yylex();
    return 0;
}

int yywrap() { return 1; }
