#include <stdio.h>
#include <string.h>

void print_char_array(char arr[]) {
    printf("%s\n", arr);
    printf("%c\n", arr[0]);
}

void print_char_pointer(char *ptr) {
    printf("%s\n", ptr);
    printf("%c\n", ptr[0]);

    while (*ptr != '\0') {
        printf("%c ", *(ptr++));
    }
    printf("\n");
}

int main() {
    char str[] = "Hello World!";
    print_char_array(str);

    char *pointer = "Hello World!";
    print_char_pointer(pointer);
    
    return 0;
}