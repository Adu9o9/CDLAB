#include <stdio.h>

int states, inputs;
int trans[20][20]; // trans[state][input] = next_state
int is_final[20];
int marked[20][20] = {0}; // The Myhill-Nerode Table

int main() {
    int i, j, k, changed;
    
    printf("Compiler Lab - DFA Minimization\n");
    printf("Enter number of states (0 to n-1) and inputs: ");
    scanf("%d %d", &states, &inputs);
    
    printf("Enter transitions (State Input Next_State):\n");
    for (i = 0; i < states * inputs; i++) {
        int s, in, ns;
        scanf("%d %d %d", &s, &in, &ns);
        trans[s][in] = ns;
    }
    
    printf("Enter number of final states: ");
    int num_finals;
    scanf("%d", &num_finals);
    printf("Enter final states: ");
    for (i = 0; i < num_finals; i++) {
        int fs;
        scanf("%d", &fs);
        is_final[fs] = 1;
    }

    // Step 1: Mark pairs where one is Final and the other is Non-Final (0-distinguishable)
    for (i = 0; i < states; i++) {
        for (j = i + 1; j < states; j++) {
            if (is_final[i] != is_final[j]) {
                marked[i][j] = 1;
                marked[j][i] = 1; // Symmetric
            }
        }
    }

    // Step 2: Mark pairs if their transitions lead to a marked pair
    do {
        changed = 0;
        for (i = 0; i < states; i++) {
            for (j = i + 1; j < states; j++) {
                if (marked[i][j] == 0) { // If currently unmarked
                    for (k = 0; k < inputs; k++) {
                        int dest1 = trans[i][k];
                        int dest2 = trans[j][k];
                        
                        // If the destinations are already marked as different
                        if (marked[dest1][dest2] == 1) {
                            marked[i][j] = 1;
                            marked[j][i] = 1;
                            changed = 1; // Keep looping until no changes occur
                            break;
                        }
                    }
                }
            }
        }
    } while (changed);

    // Step 3: Print equivalent unmarked pairs
    printf("\n--- Equivalent (Merged) States ---\n");
    int found_equivalent = 0;
    for (i = 0; i < states; i++) {
        for (j = i + 1; j < states; j++) {
            if (marked[i][j] == 0) {
                printf("State q%d and State q%d are equivalent.\n", i, j);
                found_equivalent = 1;
            }
        }
    }
    if (!found_equivalent) printf("No states can be minimized. DFA is already optimal.\n");

    return 0;
}
