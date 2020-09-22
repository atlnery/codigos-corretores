#include "aux.h"

void print(int* v, int n) {

    for (int i = 0; i < n; i++) {
        printf ("%d", v[i]);
    }
    printf("\n");
}

int* copy(char * m) {
    int size = strlen(m); 
    int* v = new(size);

    for (int i = 0; i < size; i++) {
        v[i] = (int) m[i] % 2;       
    }    

    return v;
}

int* new(int n) {
    if (n < 0) {return NULL;}

    int* new = malloc(n * sizeof(int));
    return new;
}

