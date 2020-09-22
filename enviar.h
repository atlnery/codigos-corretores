#ifndef ENVIAR_H
#define ENVIAR_H

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>

    #include "crc.h"
    #include "spc.h"
    #include "aux.h"

    #define N 500

    int ruido(int* m, int tam, int n);
    void erro(int r);
    void comunicacao(char* mensagem, int n);

#endif