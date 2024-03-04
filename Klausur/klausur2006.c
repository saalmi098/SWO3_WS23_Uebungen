#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef enum bool {false, true} bool;

int* fdi = NULL;
int* ds = NULL;

void InitGraph (int nrOfNodes, int nrOfVertices) {
    fdi = (int*)malloc(nrOfNodes * sizeof(int));
    if (fdi != NULL) {
        for (int i = 0; i < nrOfNodes; i++) {
            fdi[i] = 0;
        }
    }

    ds = (int*)malloc((nrOfNodes + nrOfVertices) * sizeof(int));
    if (ds != NULL) {
        for (int i = 0; i < nrOfNodes + nrOfVertices; i++) {
            ds[i] = -1;
        }
    }
}

bool HasVertico (int src, int dest) {
    if (fdi == NULL || ds == NULL)
        return false;

    // int element_count_fdi = sizeof(fdi) / sizeof(int);
    // int element_count_ds = sizeof(ds) / sizeof(int);
    // assert(src >= 0 && src < element_count_fdi);
    // assert(dest >= 0 && dest < element_count_fdi);

    int curr_index_ds = fdi[src];
    int curr_val = ds[curr_index_ds];

    while (curr_val != -1 && curr_val != dest) {
        curr_val = ds[++curr_index_ds];
    }

    return curr_val == dest;
}

void FreeGraph(void) {
    if (fdi != NULL) {
        free(fdi);
        fdi = NULL;
    }

    if (ds != NULL) {
        free(ds);
        ds = NULL;
    }
}

int main() {
    
    InitGraph(4, 6);
    
    fdi[0] = 0; fdi[1] = 3; fdi[2] = 6; fdi[3] = 7; 
    ds[0] = 1; ds[1] = 2; ds[2] = -1; ds[3] = 2; ds[4] = 3; ds[5] = -1; ds[6] = -1; ds[7] = 0; ds[8] = 2; ds[9] = -1; 

    printf("%d\n", HasVertico(0, 1));
    printf("%d\n", HasVertico(0, 2));
    printf("%d\n", HasVertico(1, 2));
    printf("%d\n", HasVertico(1, 3));
    printf("%d\n", HasVertico(3, 2));
    printf("%d\n", HasVertico(3, 0));

    // not existing:
    printf("%d\n", HasVertico(0, 0));
    printf("%d\n", HasVertico(2, 3));
    printf("%d\n", HasVertico(0, 3));

    FreeGraph();

    return 0;
}