#include <stdio.h>

#include "crc.h"

//CRC: polinômio gerador x³ + 1
int G[SIZEG] = {1, 0, 0, 1};

int* codificar_CRC(int* original, int n) {
    if (n < SIZEG) { return NULL; }
  
    int grauDivisor = SIZEG - 1;

    int* copia = calloc(grauDivisor + n, sizeof(int));
    memcpy(copia, original, n * sizeof(int));
    int tamCRC = n + grauDivisor;

    dividir_CRC(copia, tamCRC);

    memcpy(copia, original, n * sizeof(int));

    return copia;
}

static void dividir_CRC(int* crc, int tamCRC) {

    int grauDivisor = SIZEG - 1;
    int inicio = 0;
    int fim = grauDivisor;
    int limite = tamCRC - 1;

    while (fim < limite) {
        inicio = verifica_bits(crc, tamCRC);
        fim = inicio + grauDivisor;
        if (fim > limite) {
            break;
        }
        subtrair_CRC(crc, inicio);
    }
}


static void subtrair_CRC(int* crc, int inicio) {
    for (int i = 0; i < SIZEG; i++) {
        crc[inicio++] ^= G[i];
    }
}

int verifica_bits(int* crc, int tamCRC) {
    if (!crc || tamCRC < 1) return -1;

    int i = 0;
    while (!crc[i]) {
        if (i >= tamCRC) {
            break;
        }
        i++;
    }

    return i;
}

int verificar_erros_CRC(int* crc, int tamCRC) {
    
    dividir_CRC(crc, tamCRC);

    int resto = tamCRC - SIZEG+1;
    
    for (; resto < tamCRC; resto++) {
        if (crc[resto])
            return 1;
    }

    return 0;
    
}

