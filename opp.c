#include <stdio.h>
#include <string.h>

char stack[50];
char input[50];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

// Convert character to matrix index: i=0, +=1, *=2, $=3
int get_index(char c) {
    switch(c) {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '$': return 3;
    }
    return -1;
}

int main() {
    // Precedence Table: '<' (Shift), '>' (Reduce), 'A' (Accept), 'e' (Error)
    char table[4][4] = {
      /*       i    +    *    $  */
      /* i */ {'e', '>', '>', '>'},
      /* + */ {'<', '>', '<', '>'},
      /* * */ {'<', '>', '>', '>'},
      /* $ */ {'<', '<', '<', 'A'}
    };

    int i = 0, j;
    char action;

    printf("Compiler Lab - Operator Precedence Parser\n");
    printf("Enter input string (end with $, e.g., i+i*i$): ");
    scanf("%s", input);

    push('$');

    printf("\nStack\t\tInput\t\tAction\n");
    printf("--------------------------------------\n");

    while (1) {
        for (j = 0; j <= top; j++) printf("%c", stack[j]);
        printf("\t\t");
        
        for (j = i; input[j] != '\0'; j++) printf("%c", input[j]);
        printf("\t\t");

        // Find the top-most terminal in the stack (Ignore Non-Terminal 'E')
        int top_term_index = top;
        if (stack[top_term_index] == 'E') {
            top_term_index--; 
        }

        int row = get_index(stack[top_term_index]);
        int col = get_index(input[i]);

        if (row == -1 || col == -1) {
            printf("Error\n");
            break;
        }

        action = table[row][col];

        if (action == '<') {
            printf("Shift %c\n", input[i]);
            push(input[i]);
            i++;
        } 
        else if (action == '>') {
            printf("Reduce\n");
            if (stack[top] == 'i') {
                pop();
                push('E');
            } else {
                pop(); // Pop 'E'
                pop(); // Pop '+' or '*'
                pop(); // Pop 'E'
                push('E');
            }
        } 
        else if (action == 'A') {
            printf("Accept\n");
            break;
        } 
        else {
            printf("Error\n");
            break;
        }
    }
    return 0;
}
Input: i+i$
