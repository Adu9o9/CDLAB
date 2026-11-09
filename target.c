#include <stdio.h>
#include <string.h>

int main() {
    char tac[20];
    char result, arg1, op, arg2;
    int n;

    printf("Enter number of TAC instructions: ");
    scanf("%d", &n);

    printf("Enter the TAC instructions (Format: X=A+B):\n");
    
    printf("\n--- 8086 Assembly Target Code ---\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", tac);
        
        result = tac[0];
        arg1   = tac[2];
        op     = tac[3];
        arg2   = tac[4];

        // 1. Move first argument into Register R0
        printf("MOV R0, %c\n", arg1);
        
        // 2. Perform the operation with the second argument
        if (op == '+') {
            printf("ADD R0, %c\n", arg2);
        } else if (op == '-') {
            printf("SUB R0, %c\n", arg2);
        } else if (op == '*') {
            printf("MUL R0, %c\n", arg2);
        } else if (op == '/') {
            printf("DIV R0, %c\n", arg2);
        }
        
        // 3. Move the result from Register R0 back to the memory variable
        printf("MOV %c, R0\n\n", result);
    }

    return 0;
}
