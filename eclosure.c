#include <stdio.h>
#include <string.h>

int num_states, num_transitions;
char transitions[20][3][10]; // [transition_index][0:from, 1:input, 2:to]
int visited[20];

// Recursive function to find e-closure
void find_closure(int state_index, char states[][10]) {
    // Mark current state as visited and print it
    visited[state_index] = 1;
    printf("%s ", states[state_index]);
    
    // Check all transitions
    for (int i = 0; i < num_transitions; i++) {
        // If the transition is FROM our current state AND the input is 'e' (epsilon)
        if (strcmp(transitions[i][0], states[state_index]) == 0 && strcmp(transitions[i][1], "e") == 0) {
            
            // Find the index of the TARGET state
            int target_index = -1;
            for (int j = 0; j < num_states; j++) {
                if (strcmp(states[j], transitions[i][2]) == 0) {
                    target_index = j;
                    break;
                }
            }
            
            // If it hasn't been visited in this closure run, recurse into it
            if (target_index != -1 && visited[target_index] == 0) {
                find_closure(target_index, states);
            }
        }
    }
}

int main() {
    char states[20][10];
    
    printf("Enter number of states: ");
    scanf("%d", &num_states);
    
    printf("Enter the states (e.g., q0 q1 q2): \n");
    for (int i = 0; i < num_states; i++) {
        scanf("%s", states[i]);
    }
    
    printf("Enter number of transitions: ");
    scanf("%d", &num_transitions);
    
    printf("Enter transitions format: (From_State Input To_State). Use 'e' for epsilon.\n");
    for (int i = 0; i < num_transitions; i++) {
        scanf("%s %s %s", transitions[i][0], transitions[i][1], transitions[i][2]);
    }
    
    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < num_states; i++) {
        // Reset visited array for each state's closure calculation
        for (int v = 0; v < num_states; v++) visited[v] = 0;
        
        printf("e-closure(%s) = { ", states[i]);
        find_closure(i, states); // Starts the recursive DFS
        printf("}\n");
    }
    
    return 0;
}
