#include <stdio.h>

// nfa[from_state][input_symbol][to_state] = 1 (if transition exists)
int nfa[10][10][10] = {0};
int dfa[100][10] = {0}; // dfa[dfa_state_bitmask][input] = next_dfa_state_bitmask
int state_queue[100], front = 0, rear = 0;
int visited[100] = {0}; // Marks which bitmasks we have already processed

int main() {
    int states, inputs, transitions, i, j, k;
    
    printf("Compiler Lab - NFA to DFA (Subset Construction)\n");
    printf("Enter number of states and inputs: ");
    scanf("%d %d", &states, &inputs);
    
    printf("Enter number of transitions: ");
    scanf("%d", &transitions);
    printf("Enter transitions (From Input To) - Use Integers (0, 1, 2...):\n");
    for (i = 0; i < transitions; i++) {
        int f, in, t;
        scanf("%d %d %d", &f, &in, &t);
        nfa[f][in][t] = 1;
    }

    // Start state is always q0 (Bitmask = 1 << 0 = 1)
    state_queue[rear++] = 1;
    visited[1] = 1;

    printf("\n--- DFA Transitions ---\n");
    printf("State\tInput\tNext State\n");

    // Process the Queue
    while (front < rear) {
        int current_dfa_state = state_queue[front++];
        
        // For every input symbol
        for (j = 0; j < inputs; j++) {
            int next_dfa_state = 0;
            
            // Check every NFA state inside this DFA state
            for (k = 0; k < states; k++) {
                // If NFA state 'k' is present in current_dfa_state
                if (current_dfa_state & (1 << k)) {
                    // Check where 'k' goes on input 'j'
                    for (int l = 0; l < states; l++) {
                        if (nfa[k][j][l]) {
                            next_dfa_state |= (1 << l); // Add to next DFA state using OR
                        }
                    }
                }
            }
            
            // If we found a valid transition
            if (next_dfa_state > 0) {
                printf("{%d}\t%d\t{%d}\n", current_dfa_state, j, next_dfa_state);
                
                // If this is a newly discovered DFA state, add it to the queue
                if (!visited[next_dfa_state]) {
                    visited[next_dfa_state] = 1;
                    state_queue[rear++] = next_dfa_state;
                }
            }
        }
    }
    return 0;
}
