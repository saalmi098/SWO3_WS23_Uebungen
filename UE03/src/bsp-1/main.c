#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// include mit spitzen Klammern -> Präprozessor durchsucht Systempfade (inkl. C-Sprache etc.)
// Spitze Klammer ... Systemdateien
// Anführungszeichen ... eigene Projektdateien

// #include "./geo/geo.h"
// #include "./weight/weight.h"

#define MAX_N 100

bool queen_fits(int col[], int i, int j) {
    for (int k = 1; k < i; k++) { // Loop über Zeilen
        if (col[k] == j                 // selbe Spalte
            || k + col[k] == i + j      // selbe Hauptdiagonale
            || k - col[k] == i - j) {   // selbe Nebendiagonale
            return false;
        }
    }

    return true;
}

void print_solution(int col[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("%d ", col[i]);
    }

    printf("\n");
}

// col ... Lösungsvektor, i ... Zeile, n ... Anzahl Queens
void place_queen(int col[], int i, int n) {
    for (int j = 1; j <= n; j++) {
        if (queen_fits(col, i, j)) {
            col[i] = j; // Dame platzieren

            if (i == n) {
                print_solution(col, n);
                exit(0);
            }
                
            place_queen(col, i + 1, n);

            col[i] = 0; // Teillösung wieder zurücknehmen
        }
    }
}

int main() {
    // printf("volume: %7.3f\n", volume(1, 2, 3));
    // printf("weight: %7.3f\n", weight(1, 2, 3, 4));
    
    int col [MAX_N] = {0};
    const int queen_count = 4;
    place_queen(col, 1, queen_count);
    
    return EXIT_SUCCESS;
}