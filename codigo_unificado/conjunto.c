#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZEG 4
#define N 500

//VARIÁVEIS GLOBAIS
//CRC: polinômio gerador x³ + 1
int G[SIZEG] = {1, 0, 0, 1};

//PROTÓTIPOS AUXILIARES
void print(int* v, int n);
int* copy(char * m);
int* new(int n);
int* random_vector_unique_elems(int n);
void shuffle(int *v, int ini, int fim);
void swap(int* v, int i, int j);

//PROTÓTIPOS CRC
int* codificar_CRC(int* original, int n);
int verifica_bits(int* crc, int tamCRC);
static void dividir_CRC(int* crc, int tamCRC);
static void subtrair_CRC(int* crc, int inicio);
int verificar_erros_CRC(int* crc, int tamCRC);

//PROTÓTIPOS SPC
int* codificar_SPC(int* original, int n); 
int verificar_erros_SPC(int* spc, int n);
int verificar_bits_SPC(int* v, int n);

//PROTÓTIPOS ENVIO DA MENSAGEM
int ruido(int* m, int tam, int n);
void erro(int r);
void comunicacao(char* mensagem, int n);


//funções auxiliares
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

//CRC
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


//SPC
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

//FUNÇÃO PRINCIPAL
int main(int argc, char** argv) {

    char mensagem[N]; int n;

    printf("\nDigite a mensagem a ser enviada:\t ");
    scanf("%[^\n]", mensagem);
    printf("Quantidade de bits a serem alterados:\t");
    scanf("%d", &n);
   
    comunicacao(mensagem, n);

    return 0;
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
