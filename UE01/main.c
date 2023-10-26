#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double const PI = 3.1415927;

int main (int argc, char * argv []) {

    printf("Hello World!\n");
    printf("value of PI: %f\n", PI);

    for (int i = 0; i < argc; ++i) {
        printf("%d-tes Argument: '%s'\n", i, argv[i]);

        int const value = atoi(argv[i]);
        int const root = (int)sqrt(value);
        printf("%d-tes Argument: '%d'\n", i, value);
        printf("%d-tes Argument: '%d', Wurzel: %d\n", i, value, root);
    }

    return EXIT_SUCCESS;
}