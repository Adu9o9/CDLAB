#include <stdio.h>

int states, inputs;
// 3D Matrix: nfa[from_state][input_symbol][to_state] = 1 if transition exists
int nfa[10][10][10] = {0}; 
int e_close[10][10] = {0};
int new_nfa[10][10][10] = {0};

int main() {
    int i, j, k, l, m, num_transitions;
    int from, to, symbol, epsilon_index;

    printf("Compiler Lab - Convert NFA with Epsilon to NFA without Epsilon\n");
    printf("Enter number of states (e.g., 3 for q0,q1,q2): ");
    scanf("%d", &states);
    
    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &inputs);
    epsilon_index = inputs; // Epsilon is always the last symbol index

    printf("Enter number of transitions: ");
    scanf("%d", &num_transitions);

    printf("Enter transitions (From Input To) - Use integer IDs (e.g., 0 0 1).\n");
    printf("Note: For Input, 0 to %d are standard symbols, %d is epsilon.\n", inputs-1, epsilon_index);
    for (i = 0; i < num_transitions; i++) {
        scanf("%d %d %d", &from, &symbol, &to);
        nfa[from][symbol][to] = 1;
    }

    // 1. Initialize Epsilon-Closure matrix (Every state can reach itself)
    for (i = 0; i < states; i++) {
        e_close[i][i] = 1; 
        for (j = 0; j < states; j++) {
            if (nfa[i][epsilon_index][j] == 1) {
                e_close[i][j] = 1;
            }
        }
    }

    // 2. Warshall's Algorithm to find Transitive Epsilon Closures
    for (k = 0; k < states; k++) {
        for (i = 0; i < states; i++) {
            for (j = 0; j < states; j++) {
                if (e_close[i][k] && e_close[k][j]) {
                    e_close[i][j] = 1;
                }
            }
        }
    }

    // 3. Compute New NFA Transitions without Epsilon
    // Formula: T'(q, a) = e-closure( move( e-closure(q), a ) )
    for (i = 0; i < states; i++) { // For every starting state
        for (j = 0; j < inputs; j++) { // For every input symbol (non-epsilon)
            
            for (k = 0; k < states; k++) { // States in e-closure of 'i'
                if (e_close[i][k] == 1) {
                    
                    for (l = 0; l < states; l++) { // States reached by reading input 'j'
                        if (nfa[k][j][l] == 1) {
                            
                            for (m = 0; m < states; m++) { // States in e-closure of 'l'
                                if (e_close[l][m] == 1) {
                                    new_nfa[i][j][m] = 1; // Add to new NFA!
                                }
                            }
                        }
                    }
                }
            }
            
        }
    }

    // 4. Print the resulting NFA transition table
    printf("\n--- New NFA Transitions (Without Epsilon) ---\n");
    for (i = 0; i < states; i++) {
        for (j = 0; j < inputs; j++) {
            printf("q%d on input %d -> { ", i, j);
            int has_transition = 0;
            for (k = 0; k < states; k++) {
                if (new_nfa[i][j][k] == 1) {
                    printf("q%d ", k);
                    has_transition = 1;
                }
            }
            if (!has_transition) printf("NULL ");
            printf("}\n");
        }
    }

    return 0;
}
