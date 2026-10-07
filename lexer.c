#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Array of standard C keywords
char keywords[10][10] = {"int", "float", "if", "else", "while", "return", "void", "char", "for", "do"};

// Function to check if a string is a keyword
int isKeyword(char buffer[]) {
    for (int i = 0; i < 10; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char ch, buffer[15];
    int j = 0;
    
    printf("Compiler Lab - Manual Lexical Analyzer\n");
    printf("Enter code (end with $):\n");

    while ((ch = getchar()) != '$') {
        // 1. Ignore redundant spaces, tabs, and newlines
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            continue;
        }
        
        // 2. Identify Operators
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '>' || ch == '<') {
            printf("Operator: %c\n", ch);
        }
        // 3. Identify Separators/Punctuation
        else if (ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            printf("Separator: %c\n", ch);
        }
        // 4. Identify Identifiers and Keywords
        else if (isalpha(ch)) {
            buffer[j++] = ch;
            // Keep reading as long as it's alphanumeric
            while (isalnum(ch = getchar())) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0'; // Null-terminate the string
            j = 0; // Reset buffer index
            
            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
            
            // Put the last read character back into the input stream
            ungetc(ch, stdin);
        }
        // 5. Identify Constants (Numbers)
        else if (isdigit(ch)) {
            buffer[j++] = ch;
            while (isdigit(ch = getchar())) {
                buffer[j++] = ch;
            }
            buffer[j] = '\0';
            j = 0;
            printf("Constant: %s\n", buffer);
            
            ungetc(ch, stdin); // Put the non-digit char back
        }
    }
    return 0;
}
