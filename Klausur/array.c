#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define CAPACITY 20

void print_array(int arr[CAPACITY], int elementCount) {
    assert (elementCount < CAPACITY);
    for (int i = 0; i < elementCount; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_array_pointer(int const * arr, int elementCount) {
    assert (elementCount < CAPACITY);
    for (int i = 0; i < elementCount; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (int i = 0; i < elementCount; ++i) {
        printf("%d ", *(arr++));
    }
    printf("\n");
}

void modify_array(int arr[CAPACITY], int elementCount) {
    assert (elementCount < CAPACITY);
    arr[2] = -3;
    arr[3] = -4;
    printf("\n");
}

int main() {
    int arr[CAPACITY] = {1, 2, 3, 4, 6, 9};
    int elementCount = 6;
    print_array(arr, elementCount);
    print_array_pointer(arr, elementCount);
    printf("\n===================\n");
    modify_array(arr, elementCount);
    print_array_pointer(arr, elementCount);
    return EXIT_SUCCESS;
}