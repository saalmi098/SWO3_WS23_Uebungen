#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Aufgabe 1:

// a)
// malloc:  Übergabe der Größe des benötigten Speicherbereiches, jedoch keine Typsicherheit (man gibt nur Größe an, nicht was man darin speichert)
//          Returned einen void-Pointer, muss dann gecasted werden
//          returned NULL falls kein Speicher verfügbar -> NULL-Prüfungen notwendig
// new:     Man gibt an, welches Objekt man instanzieren möchte. new called selbst auch malloc, aber ruft dann noch den Konstruktor des Objekts auf
//          gibt bereits den richtigen Typ zurück, keine Casts notwendig
//          wirft eine Exception, falls nicht genug Speicher frei -> Exception-Handling notwendig
// free     Übergabe des Pointers, den man freigeben will
// delete   Ruft ebenfalls free auf, aber ruft davor den Destruktor auf

// b)
// Beide werden verwendet, um mit dynamischen Datenstrukturen zu arbeiten bzw. Call-By-Ref zu ermöglichen
// Referenzdatentyp ist ein Alias auf eine vorhandene Variable 
// Pointer Vorteile:    Pointer-Arithmetik, Zuweisung ändern möglich, Pointer-to-Pointer, keine Intialisierung notwendig (NULL möglich)
// Ref. Vorteile:       Keine Dereferenzierung notwendig, einfacher zu verwenden

// Aufgabe 2
// Felder   Vorteile: Zugriff auf jedes Element in O(1) möglich, kein dynamische Datenstruktur benötigt
//          Nachteile: Fixe Größe, Resizen umständlich, Einfügen sowie Löschen umständlich (nach vorne rücken)
// Listen   Vorteile: Beliebige Größe, einfaches Einfügen/Löschen von Elementen,
//          Nachteile: kein O(1) Zugriff auf Elemente, dynamische Datenstrukturen (Pointer) notwendig

typedef struct node *node_ptr;
typedef struct node {
    node_ptr next;
    int val;
} node;
typedef node_ptr list_ptr;

list_ptr list_of_array(int* arr, int size) {
    list_ptr l = NULL;
    node_ptr n = NULL;
    node_ptr pred = NULL;

    for(int i = 0; i < size; i++) {
        n = (node_ptr)malloc(sizeof(node));
        if (n != NULL) {
            n->next = NULL;
            n->val = arr[i];

            if (l == NULL) {
                l = n;
            }

            if (pred != NULL)
                pred->next = n;

            pred = n;
        }
    }

    return l;
}

int* array_of_list(list_ptr l) {
    assert (l != NULL);

    int size = 0;
    node_ptr n = l;
    while (n != NULL) {
        size++;
        n = n->next;
    }

    int* arr = (int*)malloc(sizeof(int) * size);
    n = l;
    for (int i = 0; i < size; i++) {
        arr[i] = n->val;
        n = n->next;
    }

    return arr;
}

void print(int* val) {
    printf("%d ", *val);
}

typedef void (*ofp)(int* val); /*operation function pointer*/

void for_each(list_ptr l, ofp fp) {
    node_ptr n = l;
    while (n != NULL) {
        fp(&n->val);
        n = n->next;
    }
    printf("\n");
}

void bsp2() {
    int arr[5] = {2, 5, 7, 3, 0};
    printf("%ld\n", sizeof(arr));
    list_ptr l = list_of_array(arr, 5);

    node_ptr n = l;
    while (n != NULL) {
        printf("%d ", n->val);
        n = n->next;
    }
    printf("\n");

    int* arr2 = array_of_list(l);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n=================\n");

    for_each(l, print);
}

int main() {
    bsp2();
    return 0;
}
