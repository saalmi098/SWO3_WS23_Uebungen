#include <stdlib.h>
#include <assert.h>
#include "./list.h"

node_type * create_node (int const payload, node_type * const p_next) {
    node_type * p_new = malloc(sizeof(node_type)); // impliziter Cast
    assert (p_new != NULL);

    p_new->payload = payload;
    p_new->p_next = p_next;

    return p_new;
}

node_type * create_empty_list(void) {
    return NULL;
}

void prepend (node_type * * pp_head, int const payload) {
    assert(pp_head != NULL); // pp_head darf nicht NULL sein (weil der unten sofort dereferenziert wird)

    // node_type * p_new = create_node(payload, NULL);
    // p_new->p_next = *pp_head;
    // *pp_head = p_new;

    // pointer auf pointer pp_head wird benötigt, da ein "normaler" Pointer mit Call-By-Value übergeben
    // wird und wir mit "node_type * p_head" beim Ändern des Pointers den Pointer nur in der Funktion
    // ändern würden, aber nicht beim Aufrufer
    // -> Pointer of Pointer = "Call by Reference"
    // -> weil prepend die Liste verändert

    *pp_head = create_node(payload, *pp_head);
}

void apply (node_type * p_head, unary_function_type * pf) {
    while (p_head != NULL) {
        pf(p_head->payload);
        p_head = p_head->p_next; // hier kann p_head zum Iterieren verwendet werden wegen CBV
    }
}

void clear (node_type * * pp_head) {
    assert(pp_head != NULL);

    while (*pp_head != NULL) {
        node_type * p_free = *pp_head;
        *pp_head = (*pp_head)->p_next;
        free(p_free);
        p_free = NULL; // dangling pointer eliminieren
    }
}

void reverse (node_type * * pp_head) {
    assert(pp_head != NULL);

    node_type * n = *pp_head;
    node_type * pred = NULL;
    node_type * succ = NULL;
    while (n != NULL) {
        succ = n->p_next;

        n->p_next = pred; // reverse linking

        pred = n;
        n = succ;
    }

    *pp_head = pred;
}