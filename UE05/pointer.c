#include <stdlib.h>
#include <stdio.h>

void print (int const * const p) {
    // int * const p ... p ist ein konstanter (=readonly) Zeiger auf einen int
    //  aber das worauf der Zeiger zeigt, ist nicht konstant!
    //  -> p kann man nicht verändern, aber das worauf der Zeiger zeigt (int) schon

    // int const * p ... p selbst ist nicht konstant (kann man auf eine andere Int-Var zeigen lassen)
    // aber das, worauf p zeigt (int) ist nicht änderbar

    // int const * const p ... sowohl Pointer selbst als auch das, worauf p zeigt (int) ist konstant

    if (p != NULL)
        printf("%p: %d\n", p, *p); // %p gibt die Adresse aus, die im Pointer gespeichert ist
}

void test_1 (void) {
    int   i = 42;
    int * p = NULL; // Pointer erstellen ohne NULL-Zuweisung wäre ein dangling pointer

    p = &i;
    print(p);
    print(&i);
    print(NULL);
}

void fun (int i) {
    printf("fun(%d)\n", i);
}

void some_other_fun (int i) {
    printf("some_other_fun(%d)\n", i);
}

// Return-Type und Parameter-Liste muss den Funktionen entsprechen (fun, some_other_fun)
// Typedef macht unary_function_type zu einem Datentyp, der genau für Funktionen mit
// der Signatur "void xxx(int)""
typedef void unary_function_type(int);
// typedef unary_function_type * unary_function_type_pointer_type;

void test_2(void) {
    unary_function_type * fp = NULL;
    
    fp = fun;
    (*fp) (3);

    fp = some_other_fun;
    (*fp) (4);
}

int * foo (void) {
    // Problem: i ist lokale Variable und deren Adresse wird returned
    // beim Verlassen der Funktion gibt es i aber nicht mehr -> es wird eine Adresse
    // auf eine nicht mehr vorhandene Variable zurückgegeben
    // -> dangling pointer!!
    // -> ist aber NICHT der Nullpointer!!
    int i = 42;
    return &i;
}

int * bar (void) {
    // static ... i lebt "ewig" -> static verlängert lifetime von i
    // i ist weiterhin eine lokale Variable (!!), stirbt aber nicht, wenn bar() verlassen wird
    static int i = 42;
    return &i;
}

void test_3(void) {
    // *foo() = 42;
    *bar() = 42;
}

int main (void) {
    // test_1();
    // test_2();
    test_3();
    return EXIT_SUCCESS;
}