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

int * random_vector_unique_elems(int n) {
    int* v = new(n);

    for (int i = 0; i < n; i++) {
        v[i] = i;
    }

    shuffle(v, 0, n);

    return v;
}


void shuffle(int *v, int ini, int fim) {

    int i, j;

    for(i = fim-1; i > ini; i--){
        j = (rand() % (i + 1));
        j = j <= ini? ini+1 : j;
        swap(v, i, j);
    }
}

void swap(int* v, int i, int j) {
    int temp = v[i]; 
    v[i] = v[j];
    v[j] = temp;
}

