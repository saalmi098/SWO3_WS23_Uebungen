#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

char* interleave(const char *a, const char *b) {
    assert(a != NULL && b != NULL);
    size_t length_a = strlen(a);
    size_t length_b = strlen(b);
    assert (length_a == length_b);

    char* result = malloc(length_a + length_b + 1);
    assert(result != NULL);
    
    int char_cnt = 0;
    for (int i = 0; i < (int)length_a; i++) {
        result[char_cnt] = a[i];
        char_cnt++;
        result[char_cnt] = b[i];
        char_cnt++;
    }
    result[length_a + length_b] = '\0';
    return result;
}

int main() {
    char * res1 = interleave("abcd", "1234");  // -> "a1b2c3d4"
    char * res2 = interleave("abc",  ",,,");   // -> "a,b,c,"
    char * res3 = interleave("d lie uesh",  "ukenrhrnon");   // -> ???
    printf("%s\n", res1);
    printf("%s\n", res2);
    printf("%s\n", res3);
    
    free(res1);
    free(res2);
    free(res3);
    res1 = NULL;
    res2 = NULL;
    res3 = NULL;
    
    return EXIT_SUCCESS;
}