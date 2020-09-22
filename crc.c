#include "crc.h"

int G[SIZEG] = {1, 0, 0, 1};

int* codificar_CRC(int* original, int n) {
    if (n < SIZEG) { return NULL; }
    
    int bits = SIZEG - 1;

    int * crc = new(n + bits);
    memcpy(crc, original, n * sizeof(int));
    
    int* rest = dividir_CRC(crc, n);
    
    int pos = verificar_resto_CRC(rest);
    if (pos > 1) { pos = 1; }
    memcpy(&crc[n], &rest[pos], bits * sizeof(int));
    
    free(rest);
    return crc;
}

int verificar_erros_CRC(int* crc, int n) {
    int* rest = dividir_CRC(crc, n);
    int bits0 = 0;

    for(int i = 0; i < SIZEG; i++) {
        if(!rest[i]) { bits0++; }
    }

    if(bits0 == SIZEG) { return 0; }

    return 1;
}

int* dividir_CRC(int* crc, int n) {
    int* rest = new(SIZEG);
    memcpy(rest, crc, SIZEG * sizeof(int));

    int point = SIZEG; int x;
    
    while (point <= n) {
        subtrair_CRC(rest);
        if (point != n) {
            x = clean(rest);
            rest[x++] = crc[point++];  
            while (x < SIZEG) {
                rest[x++] = crc[point++];  
            }        
        }
        else { point++;}
    }

    return rest;
}

void subtrair_CRC(int* rest) {
    for (int i = 0; i < SIZEG; i++) {
        rest[i] = rest[i] ^ G[i];
    }
}

int clean(int* rest) {
    int i; 

    int j = verificar_resto_CRC(rest);

    if (j == 0) { return -1; }

    int *temp = new(SIZEG);
   
    for (i = 0; j < SIZEG; j++, i++) {
        temp[i] = rest[j];
    }    
    
    memcpy(rest, temp, SIZEG * sizeof(int));
    free(temp);
    return i;
}

int verificar_resto_CRC(int* v) {
    int j = 0;

    while (v[j] == 0) { j++; }

    return j;
}

