#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    char str1[255];

    printf("Enter name: ");
    scanf("%s", str1);

    printf("\nEntered Name: %s (length: %ld)\n", str1, strlen(str1));

    return EXIT_SUCCESS;
}