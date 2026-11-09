#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[100];
int temp_var_count = 1;

// Helper to replace the evaluated part with a temp variable and shift the string
void reduce_string(int left_pos, int right_pos, char temp_char) {
    expr[left_pos] = temp_char;
    int shift = right_pos - left_pos;
    for (int i = left_pos + 1; i <= strlen(expr); i++) {
        expr[i] = expr[i + shift];
    }
}

void generate_tac(char op1, char op2) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == op1 || expr[i] == op2) {
            // Print the TAC instruction
            printf("t%d = %c %c %c\n", temp_var_count, expr[i - 1], expr[i], expr[i + 1]);
            
            // Convert temp_var_count integer to a character representation (e.g., '1' for t1)
            // Note: This lab logic maps t1->'1', t2->'2' inside the string for simplicity.
            char temp_char = temp_var_count + '0'; 
            
            reduce_string(i - 1, i + 1, temp_char);
            temp_var_count++;
            i = -1; // Reset loop to rescan the modified string from the beginning
        }
    }
}

int main() {
    printf("Enter an expression (e.g., W=A*B+C): ");
    scanf("%s", expr);
    
    printf("\n--- Three Address Code ---\n");
    // Pass 1: High precedence
    generate_tac('*', '/');
    // Pass 2: Low precedence
    generate_tac('+', '-');
    
    // Final assignment (e.g., W = 2, where '2' implies t2)
    printf("%c = t%c\n", expr[0], expr[2]);
    
    return 0;
}
