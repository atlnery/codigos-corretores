#include "spc.h"

int* codificar_SPC(int* original, int n) {
    int* spc = new(n + 1);
    
    memcpy(spc, original, n * sizeof(int));

    //printf("SPC: Paridade par\n");

    int bits1 = verificar_bits_SPC(original, n);
    
    spc[n] = (bits1 % 2) ? 1 : 0;
    return spc;
}

int verificar_bits_SPC(int* v, int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        if (v[i]) { sum++; }
    }
    
    return sum;
}


int verificar_erros_SPC(int* spc, int n) {
    int bits1 = 0;
    
    for (int i = 0; i < (n-1); i++) {
        if (spc[i]) bits1++;
    }
    
    if ((bits1 % 2) == spc[n-1]) { return 0; }
   
   return 1;
}
