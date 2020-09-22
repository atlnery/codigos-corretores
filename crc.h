#ifndef CRC_H
#define CRC_H

    #include <stdio.h>
    #include "aux.h"

    #define SIZEG 4

    int* codificar_CRC(int* original, int n);
    int verificar_erros_CRC(int* crc, int n);
    int* dividir_CRC(int* crc, int n);
    void subtrair_CRC(int* rest);
    int clean(int* rest);
    int verificar_resto_CRC(int* v);    
    
#endif