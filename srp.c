#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int st_ptr = 0, len;

// The REDUCE function
void check() {
    int i;
    
    // Check for Handle: i  --> Reduce to E
    for (i = 0; i < st_ptr; i++) {
        if (stack[i] == 'i') {
            stack[i] = 'E';
            printf("\n$%s\t\t%s$\t\tReduce E->i", stack, input);
        }
    }
    
    // Check for Handle: E+E --> Reduce to E
    for (i = 0; i < st_ptr - 2; i++) {
        if (stack[i] == 'E' && stack[i+1] == '+' && stack[i+2] == 'E') {
            stack[i] = 'E';
            stack[i+1] = '\0';
            stack[i+2] = '\0';
            st_ptr = st_ptr - 2; // Pull stack pointer back by 2
            printf("\n$%s\t\t%s$\t\tReduce E->E+E", stack, input);
        }
    }
    
    // Check for Handle: E*E --> Reduce to E
    for (i = 0; i < st_ptr - 2; i++) {
        if (stack[i] == 'E' && stack[i+1] == '*' && stack[i+2] == 'E') {
            stack[i] = 'E';
            stack[i+1] = '\0';
            stack[i+2] = '\0';
            st_ptr = st_ptr - 2; // Pull stack pointer back by 2
            printf("\n$%s\t\t%s$\t\tReduce E->E*E", stack, input);
        }
    }
}

int main() {
    printf("Compiler Lab - Shift Reduce Parser\n");
    printf("Enter the input string (e.g., i+i*i): ");
    scanf("%s", input);
    len = strlen(input);

    printf("\nStack\t\tInput\t\tAction");
    printf("\n--------------------------------------------");

    // The SHIFT loop
    for (int j = 0; j < len; j++) {
        // 1. Shift first char of input onto stack
        stack[st_ptr] = input[0];
        stack[st_ptr + 1] = '\0';
        st_ptr++;
        
        // 2. Remove that char from input buffer (shift the array left)
        memmove(input, input + 1, strlen(input));

        printf("\n$%s\t\t%s$\t\tShift", stack, input);

        // 3. Try to Reduce
        check();
    }

    // ACCEPT phase
    if (st_ptr == 1 && stack[0] == 'E') {
        printf("\n\nResult: String Accepted!\n");
    } else {
        printf("\n\nResult: Syntax Error!\n");
    }

    return 0;
}
i+i
