#include <stdio.h>
#include <assert.h>
#include "./list.h"

void print(int payload) {
    printf("%d ", payload);
}

int main(void) {
    list_type l = create_empty_list();

    printf("prepending elements...\n");
    prepend(&l, 1);
    prepend(&l, 2);
    prepend(&l, 3);
    prepend(&l, 6);
    prepend(&l, 13);

    apply(l, print); printf("\n");
    apply(NULL, print); printf("\n");

    printf("reversing list...");
    reverse(&l); printf("\n");
    apply(l, print); printf("\n");

    clear(&l);
    assert (l == create_empty_list()); // l == NULL
}

