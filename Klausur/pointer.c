#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define CAPACITY 5

typedef enum bool {false, true} bool;

typedef struct person {
    char* first_name;
    char* last_name;
    int age;
} person;

typedef bool fp_type(person*, int);

void print_person(person const * const p) {
    assert(p != NULL);
    printf("%s %s (%d)\n", p->first_name, p->last_name, (*p).age);
}

person* create_person(char* first_name, char* last_name, int age) {
    person* p = (person*)malloc(sizeof(person));
    assert(p != NULL);

    p->first_name = first_name;
    p->last_name = last_name;

    // p->first_name = "xx";

    // p->first_name = malloc((strlen(first_name) + 1) * sizeof(char));
    // assert(p->first_name != NULL);
    // strcpy(p->first_name, first_name);

    p->age = age;
    return p;
}

bool is_older_than(person* p, int age_limit) {
    assert(p != NULL);
    return p->age > age_limit ? true : false;
}

bool is_younger_than(person* p, int age_limit) {
    assert(p != NULL);
    return !is_older_than(p, age_limit) && p->age != age_limit;
}

void test_persons() {
    // char* first_name = "Max";
    // person* p1 = create_person(first_name, "Mustermann", 30);
    // printf(">>%s\n", first_name);
    person* p1 = create_person("Max", "Mustermann", 30);
    person* p2 = create_person("Susi", "Sorglos", 20);

    // print_person(p1);
    // print_person(p2);

    person** persons = (person**)malloc(sizeof(person) * CAPACITY);
    persons[0] = p1;
    persons[1] = p2;

    for (size_t i = 0; i < 2; i++)
    {
        person* p = persons[i];
        print_person(p);

        int age_limit = 25;
        fp_type* fp = is_older_than;
        if ((*fp)(p, age_limit)) {
            printf("  is older than %d\n", age_limit);
        } else {
            printf("  is NOT older than %d\n", age_limit);
        }

        fp = is_younger_than;
        if ((*fp)(p, age_limit)) {
            printf("  is younger than %d\n", age_limit);
        } else {
            printf("  is NOT younger than %d\n", age_limit);
        }
        


        // free(p->first_name);
        free(p);
        p = NULL;
    }

    free(persons);
    


    /*// free(p1->first_name);
    free(p1);
    // free(p2->first_name);
    free(p2);
    p1 = NULL;
    p2 = NULL;*/
}

int main() {
    test_persons();
    return 0;
}