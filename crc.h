#ifndef CRC_H
#define CRC_H

    #include <stdio.h>
    #include "aux.h"

    #define SIZEG 4

    int* codificar_CRC(int* original, int n);
    int verifica_bits(int* crc, int tamCRC);
    static void dividir_CRC(int* crc, int tamCRC);
    static void subtrair_CRC(int* crc, int inicio);
    int verificar_erros_CRC(int* crc, int tamCRC);
    
#endif