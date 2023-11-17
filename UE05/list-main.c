#include <stdio.h>
#include <assert.h>
#include "./list.h"

void print(int payload) {
    printf("%d ", payload);
}

int main(void) {
    list_type l = create_empty_list();
    prepend(&l, 1);
    prepend(&l, 2);
    prepend(&l, 3);

    apply(l, print); printf("\n");
    apply(NULL, print); printf("\n");

    clear(&l);
    assert (l == create_empty_list()); // l == NULL
}

