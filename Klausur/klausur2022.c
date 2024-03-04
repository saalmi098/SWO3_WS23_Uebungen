#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// Bsp. 1 

// a)
// Probleme:
// - Buffer-Overflow falls Ziel-String nicht groß genug
// - s1/s2 könnten ungültige Pointer sein (z.B. NULL oder dangling pointer)
//
// Lösungen
// - Größe mit strlen() überprüfen (z.B. a >= strlen(s1) + 1)
// - NULL-Pointer Checks

// b)
// - Makros werden von Präprozessor durch anderen Text ersetzt (vor dem Kompilieren)
//   keine type-safety (simple Textersetzung), keine Semantikprüfung
// - Bei Templates generiert der Compiler (beim Kompilieren) alle benötigten Datentypen (int, string, ...) als eigene Funktionen
//   Bieten type-safety (Parameter müssen richtigen Typ aufweisen)

typedef struct node *node_ptr;
typedef struct node {
    int val;
    node_ptr left, right;
} node;
typedef node_ptr tree_ptr;

int nr_of_nodes(tree_ptr t) {
    if (t == NULL)
        return 0;
    
    return 1 + nr_of_nodes(t->left) + nr_of_nodes(t->right);
}

void array_of_rec(tree_ptr t, int* arr, int* i) {
    if (t == NULL)
        return;

    array_of_rec(t->left, arr, i);
    arr[*i] = t->val;
    (*i)++;
    array_of_rec(t->right, arr, i);
}

int* array_of(tree_ptr t) {
    
    int arr_size = nr_of_nodes(t);
    int* arr = (int*)malloc(sizeof(int) * arr_size);

    int i = 0;
    array_of_rec(t, arr, &i);
    
    return arr;
}

void bsp1() {
    tree_ptr t = (tree_ptr)malloc(sizeof(node));
    tree_ptr l = (tree_ptr)malloc(sizeof(node));
    tree_ptr r = (tree_ptr)malloc(sizeof(node));
    if (t != NULL && l != NULL && r != NULL) {
        t->left = l; t->right = r; t->val = 3;
        l->left = NULL; l->right = NULL; l->val = 1;
        r->left = NULL; r->right = NULL; r->val = 5;

        const int nr_nodes = nr_of_nodes(t);
        printf("nr of nodes: %d\n", nr_nodes);
       
        int* arr = array_of(t);
        for(int i = 0; i < nr_nodes; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        free(arr);
        arr = NULL;
    }

    free(t); free(l); free(r);
    t = NULL; l = NULL; r = NULL;

    // d) Aufrufer der Schnittstelle hat keine Möglichkeit, die Länge des Arrays
    // zu bestimmen, ohne selbst 'nr_of_nodes()' aufzurufen.
    // -> CBR-Parameter für Größe des Arrays ergänzen (Var. "i")

}

int main(void) {
    bsp1();
    return 0;
}