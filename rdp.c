#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char input[100];
int i = 0;
bool error = false;

void E(); void Eprime(); void T(); void Tprime(); void F();

void match(char expected) {
    if (input[i] == expected) i++;
    else error = true;
}

void F() {
    if (input[i] == 'i') { // 'i' represents a boolean identifier like true/false
        i++;
    } else if (input[i] == '!') {
        i++;
        F();
    } else if (input[i] == '(') {
        i++;
        E();
        match(')');
    } else {
        error = true;
    }
}

void Tprime() {
    if (input[i] == '&') {
        i++;
        F();
        Tprime();
    }
}

void T() {
    F();
    Tprime();
}

void Eprime() {
    if (input[i] == '|') {
        i++;
        T();
        Eprime();
    }
}

void E() {
    T();
    Eprime();
}

int main() {
    printf("Enter boolean expression (use i, &, |, !, (), end with $): ");
    scanf("%s", input);
    
    E(); // Start parsing
    
    if (input[i] == '$' && !error) {
        printf("Result: String Accepted.\n");
    } else {
        printf("Result: Syntax Error!\n");
    }
    return 0;
}
$E \rightarrow T E'$ (OR level)
$E' \rightarrow \vert{} T E' \mid \epsilon$
$T \rightarrow F T'$ (AND level)
$T' \rightarrow \& F T' \mid \epsilon$
$F \rightarrow ! F \mid ( E ) \mid i$
