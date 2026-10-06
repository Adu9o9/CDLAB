#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0;
char prod[10][10], res[10];

// Helper function to add a character to the result array without duplicates
void add_to_res(char c) {
    for (int i = 0; i < m; i++) {
        if (res[i] == c) return; // Already exists
    }
    res[m++] = c;
}

// Function to calculate FIRST
void FIRST(char c) {
    // If it's a terminal, FIRST is the terminal itself
    if (!isupper(c)) { 
        add_to_res(c); 
        return; 
    }
    
    // If it's a Non-Terminal, look through productions
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (prod[i][2] == '#') {
                add_to_res('#'); // Epsilon
            } else if (!isupper(prod[i][2])) {
                add_to_res(prod[i][2]); // Terminal
            } else {
                FIRST(prod[i][2]); // Recursive call for Non-Terminal
            }
        }
    }
}

// Function to calculate FOLLOW
void FOLLOW(char c) {
    // Rule 1: Start symbol gets '$'
    if (prod[0][0] == c) {
        add_to_res('$');
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                // Rule 2: If there is a symbol after 'c'
                if (prod[i][j+1] != '\0') {
                    FIRST(prod[i][j+1]);
                }
                // Rule 3: If 'c' is at the end, or the symbol after 'c' has Epsilon
                if (prod[i][j+1] == '\0' && c != prod[i][0]) {
                    FOLLOW(prod[i][0]);
                }
            }
        }
    }
}

int main() {
    char choice;
    char c;
    
    printf("Compiler Lab - FIRST and FOLLOW\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    
    printf("Enter productions (Format: S=AB, use # for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }
    
    do {
        m = 0; // Reset result index
        memset(res, '\0', sizeof(res));
        
        printf("\nEnter Non-Terminal to find FIRST & FOLLOW: ");
        scanf(" %c", &c);
        
        // Find and print FIRST
        FIRST(c);
        printf("FIRST(%c) = { ", c);
        for (int i = 0; i < m; i++) printf("%c ", res[i]);
        printf("}\n");
        
        // Reset and find FOLLOW
        m = 0;
        memset(res, '\0', sizeof(res));
        FOLLOW(c);
        printf("FOLLOW(%c) = { ", c);
        // We must remove '#' from FOLLOW if it leaked from FIRST
        for (int i = 0; i < m; i++) {
            if (res[i] != '#') printf("%c ", res[i]);
        }
        printf("}\n");
        
        printf("Continue? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');
    
    return 0;
}
S=AB

A=a

B=b
