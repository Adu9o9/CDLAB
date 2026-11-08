#include <stdio.h>

int n; // Total number of states
int epsilon_graph[20][20]; // 2D Adjacency Matrix for epsilon transitions
int visited[20];

// Recursive DFS to find all reachable states via epsilon
void find_closure(int state) {
    visited[state] = 1;
    printf("q%d ", state); // Print the state as part of the closure
    
    // Check all possible next states
    for (int i = 0; i < n; i++) {
        // If there is an epsilon path to state 'i' and it hasn't been visited yet
        if (epsilon_graph[state][i] == 1 && !visited[i]) {
            find_closure(i); 
        }
    }
}

int main() {
    int edges, u, v;
    
    printf("Enter number of states: ");
    scanf("%d", &n);
    
    // Initialize matrix with 0
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            epsilon_graph[i][j] = 0;
            
    printf("Enter number of epsilon transitions: ");
    scanf("%d", &edges);
    
    char symbol; // Add a variable to hold 'e', 'a', 'b', etc.
    
    printf("Enter transitions (Format: start_state symbol end_state, use 'e' for epsilon):\n");
    for (int i = 0; i < edges; i++) {
        // The space before %c is CRITICAL to ignore trailing newlines/spaces!
        scanf("%d %c %d", &u, &symbol, &v);
        
        // Only map it to the graph if it is an epsilon transition
        if (symbol == 'e') {
            epsilon_graph[u][v] = 1;
        }
    }
    
    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < n; i++) {
        // Reset the visited array for each new state evaluation
        for(int j = 0; j < n; j++) visited[j] = 0;
        
        printf("Epsilon closure of q%d: { ", i);
        find_closure(i);
        printf("}\n");
    }
    
    return 0;
}
