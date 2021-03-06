#ifndef OBJECT_H_H
#define OBJECT_H_H

#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include "QRCode.h"

#define MODO_NUMERICO 1
#define MODO_ALPHANUMERICO 2
#define MODO_BYTE 4

#define CORRECAO_MODO_L 'L'
#define CORRECAO_MODO_M 'M'
#define CORRECAO_MODO_Q 'Q'
#define CORRECAO_MODO_H 'H'

#define    EXCEPTION_LENGTH_UNSUPPORTED  (char)-1
#define    EXCEPTION_BUG_IN_CHOSEN_VERSION  (char)-2
#define    ArrayIndexOutOfBoundsException  (char)-3
#define    NULLPoiterException (char)-4
#define ERROR()\
     if(qrcode.error<0)\
        return

#define LOG(format, ...)\
    logFile = fopen("debug.txt", "a");\
    if (!logFile) \
     logFile = fopen("debug.txt", "w");\
    fprintf(logFile, format,## __VA_ARGS__);\
    fclose(logFile)

#define COMPARE_MODO_CORRECAO(result, MODO_ATUAL, v1, v2, v3, v4)\
    result = 0;\
    result = ((MODO_ATUAL==CORRECAO_MODO_L)*v1 + (MODO_ATUAL==CORRECAO_MODO_M)*v2 + (MODO_ATUAL==CORRECAO_MODO_Q)*v3 + (MODO_ATUAL == CORRECAO_MODO_H)*v4)

void gerarQR(char *vet);

typedef struct {
    unsigned int numeroDoUltimoArquivo;
    int temmsg;
    char MODE_CORRECAO_AUTOMATICO;
    char ultimaMsg[300];
} Configuracoes;
typedef struct {
    int version;
    int nivelCorrecaoErro;
    int numeroTotaldePalavrasChavedeDados;
    int bytesCorretoresPorBloco;
    int qtBlocosGrupo_1;
    int qtDePalavrasCodigo_Grupo_1;
    int qtBlocosGrupo_2;
    int qtDePalavrasCodigo_Grupo_2;

    int bitsdeRemanescenteRequeridos;
    int maskara;
} Table;
typedef struct {
    int *mat;
    int m, n;

} Matriz;
typedef struct {
    Table tabela;
    int qtBitsMode;

    int tamanhoDa_mensagemAserCriptografada;
    char *mensagemAserCriptografada;

    char MODE_TYPE;//numerico alphanumerico ou byte



    char strBinMode4Bits[4], indicadorDecontagemDeCaracteres[10];
    char error;

    char *strbits;
    int tamanhoDaStrbits;

    unsigned short *msgNumbers;
    int tamanhoDa_msgNumbers;
    char *codigosCorretores;
    int tamanhoDosCodigosCorretores;
    Matriz QRImagem;
    Configuracoes config;
} QRCODE;
QRCODE qrcode = {0};
FILE *logFile;

void freeqr() {

    if (qrcode.strbits) {
        free(qrcode.strbits);
        qrcode.strbits = 0;
    }
    if (qrcode.msgNumbers) {
        free(qrcode.msgNumbers);
        qrcode.msgNumbers = 0;
    }
    if (qrcode.codigosCorretores) {
        free(qrcode.codigosCorretores);
        qrcode.codigosCorretores = 0;
    }
    if (qrcode.QRImagem.mat) {
        free(qrcode.QRImagem.mat);
        qrcode.QRImagem.mat;
    }
}

void integerValueOf(char *str_init, char *str_intervalo_fim, char *str_final_maximo, int *n) {
    if (str_init < str_final_maximo && str_init < str_intervalo_fim) {
        if (*str_init >= '0' && *str_init <= '9')
            *n = *n * 10 + ((*str_init - '0'));
        integerValueOf((str_init + 1), str_intervalo_fim, str_final_maximo, n);
    }
}

void printaERRO() {
    if (qrcode.error < 0) {
        if (qrcode.error == EXCEPTION_LENGTH_UNSUPPORTED) {
            LOG("\n\nERROR: %s", "EXCEPTION_LENGTH_UNSUPPORTED");
        } else if (qrcode.error == EXCEPTION_BUG_IN_CHOSEN_VERSION) {
            LOG("\n\nERROR: %s", "EXCEPTION_BUG_IN_CHOSEN_VERSION");
        } else if (qrcode.error == ArrayIndexOutOfBoundsException) {
            LOG("\n\nERROR: %s", "ArrayIndexOutOfBoundsException");
        } else if (qrcode.error == ArrayIndexOutOfBoundsException) {
            LOG("\n\nERROR: %s", "ArrayIndexOutOfBoundsException");
        } else if (qrcode.error == NULLPoiterException) {
            LOG("\n\nERROR: %s", "NULLPoiterException");
        }
    }
}

int alphaValue(int x1, int x2) {
    int valor;
    if (x1 >= '0' && x1 <= '9')
        x1 = x1 - '0';
    else if (x1 >= 'A' && x1 <= 'Z')
        x1 = x1 - 'A' + 10;
    else
        x1 = ((x1 == ' ') * 36 + (x1 == '$') * 37 + (x1 == '%') * 38 + (x1 == '*') * 39 + (x1 == '+') * 40 +
              (x1 == '-') * 41 + (x1 == '.') * 42 + (x1 == '/') * 43 + (x1 == ':') * 44);
    if (x2 >= '0' && x2 <= '9')
        x2 = x2 - '0';
    else if (x2 >= 'A' && x2 <= 'Z')
        x2 = x2 - 'A' + 10;
    else
        x2 = ((x2 == ' ') * 36 + (x2 == '$') * 37 + (x2 == '%') * 38 + (x2 == '*') * 39 + (x2 == '+') * 40 +
              (x2 == '-') * 41 + (x2 == '.') * 42 + (x2 == '/') * 43 + (x2 == ':') * 44);
    valor = ((x1 * 45) + x2);
    return valor;
}

unsigned short binaryToDec(char *str_init, char *str_fim, char *str_max) {
    int i = 7;
    unsigned short soma = 0;
    int j = 0;
    for (; i >= 0; i--) {
        soma += (str_init[i] - 48) * pow(2, j++);
    }
    return soma;
}

void converterParaBinario(char *buff, unsigned int decimal, int bits) {
    buff[bits] = '\0';
    bits--;
    while (bits >= 0) {
        buff[bits] = (decimal % 2) + '0';
        bits--;
        decimal = decimal / 2;
    }
}

int contaLetras(char *str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

void printa8Bits(FILE *f, char *str, int tam) {
    int i, j, k = 0;
    for (i = 0; str[k] && k < tam; ++i) {
        for (j = 0; str[k] && j < 8 && k < tam; j++) {
            fprintf(f, "%c", str[k++]);
        }
        fprintf(f, " ");
    }
}

Matriz multiplicaMatriz(Matriz cop, int scale) {
    Matriz r = {0};
    r.m = cop.m * scale;
    r.n = cop.n * scale;
    r.mat = calloc(r.n * r.m, sizeof(int));
    printf("%p    %d\n", r.mat, sizeof(r.mat) / sizeof(int));
    int i, j;
    int a, b;
    int l = 0, k = 0;
    for (i = 0; i < cop.m; i++) {
        for (j = 0; j < cop.n; j++) {
            for (a = l; a < l + scale; a++) {
                for (b = k; b < k + scale; b++) {
                    r.mat[a * r.n + b] = cop.mat[i * cop.n + j];
                }
            }
            k += scale;
        }
        l += scale;
        k = 0;
    }
    return r;
}

void printaQRIMG(Matriz m, int numero, int inverter, int log) {
    ERROR();
    int i, j;
//    rh
    int scale = 640 / m.m;
    if (scale < 1) scale = 1;
    Matriz matriz = multiplicaMatriz(m, scale);
    char nome[30] = "";
    snprintf(nome, 29, "qrcode_(%d).pbm", numero);
    if (log)
        logFile = fopen("debug.txt", "a");
    FILE *img = fopen(nome, "w");
    fprintf(img, "P1\n");
    fprintf(img, "%d %d \n", matriz.m + 8 * scale, matriz.n + 8 * scale);
    LOG("\nrescalondo imagem");
    for (i = -4 * scale; i < matriz.m + (4 * scale); ++i) {
        for (j = -4 * scale; j < matriz.n + (4 * scale); ++j) {
            if (i >= 0 && i < matriz.m && j >= 0 && j < matriz.n) {
                if (inverter) {
                    if (log)
                        fprintf(logFile, "%c ", !(matriz.mat[i * matriz.n + j] % 2) ? '1' : '0');
                    fprintf(img, "%c ", !(matriz.mat[i * matriz.n + j] % 2) ? '1' : '0');
                } else {
                    if (log)
                        fprintf(logFile, "%c ", (matriz.mat[i * matriz.n + j] % 2) ? '1' : '0');
                    fprintf(img, "%c ", (matriz.mat[i * matriz.n + j] % 2) ? '1' : '0');
                }
            } else {
                if (log)
                    fprintf(logFile, "%c ", inverter ? '1' : '0');
                fprintf(img, "%c ", inverter ? '1' : '0');
            }
        }
    }
    LOG("Imagem rescalonada com sucesso!\n");


    if (matriz.mat)
        free(matriz.mat);
    if (log)
    fprintf(logFile, "\n");
    if (log)
    fclose(logFile);
    fclose(img);
#if win32
    snprintf(nome, 29, "start qrcode_(%d).pbm", numero);
    system(nome);
#endif
}

#endif
