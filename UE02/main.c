#include <stdio.h>
#include <assert.h>

#define MAL_2(x) (2*(x))

void print_int (int const x); // function prototype (function declaration)

#define CAPACITY 10

void print_int_vector(int w [CAPACITY], int const s) { // function definition (and implicit declaration)
    // printf("sizeof(w): %ld\n", sizeof(w)); // = 8 Bytes (size of int* pointer) -> use s parameter
    
    assert(s <= CAPACITY); // "Programm Invariante" - assert checks

    printf("{ ");
    for (int i = 0; i < s; i++) {
        printf("%d ", w[i]);
    }
    printf("}\n");
}

int main() {
    print_int(42);

    int v [CAPACITY] = {1, 2, 3, 4, 5}; // C-array; ab dem 6. Element sind alle 0

    printf("sizeof(v): %ld\n", sizeof(v)); // = 40 Bytes (10x4 Bytes)
    print_int_vector(v, CAPACITY);
}

void print_int (int const x) { // function definition
    printf("value: %d\n", x);
}