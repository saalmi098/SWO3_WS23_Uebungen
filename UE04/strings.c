#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void print_string(char const str []) {
    int i = 0;
    while (str[i] != '\0')
    {
        printf("%c", str[i++]);
    }
}

int string_length(char const str[]) {
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    
    return i;
}

void test_1() {
    // char s1[6] = { 'H', 'a', 'n', 's', 'i', '\0'};
    // char s1[5] = { 'H', 'a', 'n', 's', 'i'}; // string terminator "\0" missing
    // char s2[6] = "Hansi"; // array of const char; 6 bytes (last one for "\0" string terminator) 
    // char s2[10] = "Susi";
    char s1 [20] = "Karli12345";
    char s2 [20] = "Susi12345";

    print_string(s1);
    print_string("\n"); // '\n' would not work here (char != array of char)
    print_string(s2);
    print_string("\n");

    printf("size: %d\n", string_length("Hansi"));
    printf("sizeof(s1): %ld\n", sizeof(s1));
}

void test_2() {
    char s1[10] = "FH ";
    char s2[20] = "Hagenberg";
    char s3[100] = "Softwarepark";

    printf("strcmp: %d\n", strcmp("Susi", "Hansi"));
    printf("strcmp: %d\n", strcmp("FH", s1)); // returns -32 because of "FH " (space at end = ASCII-Dec 32)

    if (!strcmp("FH ", s1)) { // strcomp == 0 ... equal
        printf("strings are equal\n");
    }

    print_string(s3); printf(" (length: %d)", string_length(s3)); print_string("\n");
    strcpy(s3, s2); // copies the 10 bytes from "Hagenberg\0" to s3
    print_string(s3); printf(" (length: %d)", string_length(s3)); print_string("\n");
}

void test_3() {
    char s1[10] = "FH ";
    char s2[20] = "Hagenberg";
    char s3[100] = " Softwarepark";
    char s4[500] = {'\0'};

    print_string(s4); print_string("\n");
    strcat(s4, s1);
    strcat(s4, s2);
    strcat(s4, s3);
    print_string(s4); print_string("\n");
}

// dynamic programming
int change_dp(
    int const M,        // M(oney) ... zu wechselnder Betrag, 
    int const c[],      // c(oins) ... Array der Coins (Stückelung)
    int const d) {      // Anzahl der Münzen in der Stückelung 

    int dpt[100] = {0}; // dynamic programming table

    assert(M >= 0);
    assert(M < 100);

    for (int m = 1; m <= M; m++) {
        dpt[m] = M;

        for (int k = 0; k < d; k++) {
            if (m >= c[k]) {
                if (dpt[m - c[k]] + 1 < dpt[m]) {
                    dpt[m] = dpt[m-c[k]] + 1;
                }
            }
        }
    }
    
    return dpt[M];
}

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

void test_4() {
    int c[] = {7, 3, 1};
    for (int M = 0; M <= 14; M++) {
        printf("%2d %d\n", M, change_dp(M, c, ARRAY_SIZE(c)));
    }
}

#define MAX_ROWS 5
#define MAX_COLS 10

// multi-dimensional array
void test_5() {
    // int matrix [MAX_ROWS][MAX_COLS] = {{0}};
    int matrix [MAX_ROWS][MAX_COLS] = {
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                                        {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
                                        {0},
                                        {0},
                                        {0}
                                      };

    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            printf("%2d ", matrix[r][c]);
        }

        printf("\n");
    }
}

int main() {
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    test_5();

    return EXIT_SUCCESS;
}
