#include "enviar.h"

void main(int argc, char** argv) {

    char mensagem[N]; int n;

    printf("\nDigite a mensagem a ser enviada:\t ");
    scanf("%[^\n]", mensagem);
    printf("Quantidade de bits a serem alterados:\t");
    scanf("%d", &n);
   
    comunicacao(mensagem, n);
}

void comunicacao(char* mensagem, int n) { 
    int* original = copy(mensagem);
    int tam_original = strlen(mensagem);
    
    //codificar    
    int* crc = codificar_CRC(original, tam_original);
    int* spc = codificar_SPC(original, tam_original);
    
    //atualizar tamanho da mensagem (n + k)
    int tam_spc = tam_original + 1;
    int tam_crc = tam_original-1 + SIZEG;

    //mensagens enviadas
    printf("\nMensagem codificada");
    printf("\nSPC:\t"); print(spc, tam_spc);
    printf("CRC:\t"); print(crc, tam_crc);

    //causar ruídos
    ruido(spc, tam_spc, n);
    ruido(crc, tam_crc, n);
   
    printf("\nMensagem com ruído\n");
    // //mensagens recebida
    printf("SPC:\t"); print(spc, tam_spc);
    printf("CRC:\t"); print(crc, tam_crc);

    //detectar erros
    clock_t inicio, fim;
    double tempo1, tempo2;

    inicio = clock();
    int spc_deteccao = verificar_erros_SPC(spc, tam_spc);
    tempo1 = (double) (clock() - inicio) / (CLOCKS_PER_SEC / 1000) ;

    inicio = clock();
    int crc_deteccao = verificar_erros_CRC(crc, tam_crc);
    tempo2 = (double) (clock() - inicio) / (CLOCKS_PER_SEC / 1000) ;

    //verificar se código detectou erro 
    printf("\nSPC: \t");
    erro(spc_deteccao);   
    printf("tempo de execução: %.3f s\n\n", tempo1);
 
    printf("CRC: \t");
    erro(crc_deteccao);
    printf("tempo de execução: %.3f s\n", tempo2);
    
    free(crc);
    free(spc);
    free(original);
}


int ruido(int* m, int tam, int n) {
    if (n > tam) { return 0;}

    int* v = random_vector_unique_elems(tam);

    for (int i = 0; i < n; i++) {
        int r_pos = v[i];
        m[r_pos] = !m[r_pos];
    }
    
    free(v);
    return 1;
}

void erro(int r) {
    if (r) { printf("Erro detectado!\n"); }

    else { printf("Não houve detecção de erro!\n"); }
}


