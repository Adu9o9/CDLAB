#include <stdio.h>
#include <string.h>

int i = 0, j = 0, c = 0;
char a[20], stk[20], act[10];

// Function to check and perform reductions
void check() {
    strcpy(act, "REDUCE");
    
    // Check for 'i' -> E
    for (int z = 0; z < c; z++) {
        if (stk[z] == 'i') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("$%s\t%s$\t%s\n", stk, a, act);
        }
    }
    
    // Check for E+E -> E
    for (int z = 0; z < c - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("$%s\t%s$\t%s\n", stk, a, act);
            i = i - 2; // Adjust stack pointer
        }
    }
    
    // Check for E*E -> E
    for (int z = 0; z < c - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("$%s\t%s$\t%s\n", stk, a, act);
            i = i - 2; // Adjust stack pointer
        }
    }
}

int main() {
    printf("Enter input string (e.g., i+i*i): ");
    scanf("%s", a);
    c = strlen(a);
    
    printf("STACK\tINPUT\tACTION\n");
    
    for (int k = 0; j < c; k++, i++, j++) {
        // Shift action
        strcpy(act, "SHIFT");
        stk[i] = a[j];
        stk[i + 1] = '\0';
        a[j] = ' '; // Clear from input buffer
        
        printf("$%s\t%s$\t%s\n", stk, a, act);
        
        // After every shift, check if a reduction is possible
        check();
    }
    
    if (stk[0] == 'E' && stk[1] == '\0') {
        printf("\nResult: String Accepted\n");
    } else {
        printf("\nResult: String Rejected\n");
    }
    
    return 0;
}
