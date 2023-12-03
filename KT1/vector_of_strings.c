#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct vector_of_strings {
    char ** elements;
    int size;
} vector_of_strings;

vector_of_strings * make_new(int size) {
    assert(size > 0);
    vector_of_strings * v = malloc(sizeof(vector_of_strings));
    assert(v != NULL);

    v->size = size;
    v->elements = malloc(sizeof(char *) * size);
    assert(v->elements != NULL);

    for (int i = 0; i < size; i++) {
        v->elements[i] = NULL;
    }

    return v;
}

void set (vector_of_strings * p_vector, int index, char const * p_string) {
    assert(p_vector != NULL);
    assert(index >= 0);

    if (p_vector->elements[index] != NULL) {
        free(p_vector->elements[index]);
        p_vector->elements[index] = NULL;
    }

    p_vector->elements[index] = p_string;
}

void print_vector(vector_of_strings * p_vector) {
    assert(p_vector != NULL);
    
    for (int i = 0; i < p_vector->size; i++) {
        if (i > 0)
            printf(", ");

        printf("%s", p_vector->elements[i]);
    }
    printf("\n");
}

void dispose_vector(vector_of_strings ** p_vector) {
    assert(p_vector != NULL && (*p_vector) != NULL);

    // freeing of every single string not needed... and does not work?
    
    // for (int i = 0; i < (*p_vector)->size; i++) {
    //     if ((*p_vector)->elements[i] != NULL) {
    //         free((*p_vector)->elements[i]);
    //         (*p_vector)->elements[i] = NULL;
    //     }
    // }

    free((*p_vector)->elements);
    (*p_vector)->elements = NULL;

    free(*p_vector);
    (*p_vector) = NULL;
}

int main() {
    vector_of_strings * v = make_new(5);
    print_vector(v);

    printf("\nFilling vector...\n");
    set(v, 1, "Hugo");
    set(v, 2, "Susi");
    set(v, 4, "AB");
    print_vector(v);

    dispose_vector(&v);
    v = NULL;
}