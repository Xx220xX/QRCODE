#ifndef OBJECT_H_H
#define OBJECT_H_H

#include<stdlib.h>
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

#define LOG(format, ...)\
    logFile = fopen("debug.txt", "a");\
    if (!logFile) \
     logFile = fopen("debug.txt", "w");\
    fprintf(logFile, format,## __VA_ARGS__);\
    fclose(logFile)

#define COMPARE_MODO_CORRECAO(result, MODO_ATUAL, v1, v2, v3, v4)\
    result = 0;\
    result = ((MODO_ATUAL==CORRECAO_MODO_L)*v1 + (MODO_ATUAL==CORRECAO_MODO_M)*v2 + (MODO_ATUAL==CORRECAO_MODO_Q)*v3 + (MODO_ATUAL == CORRECAO_MODO_H)*v4)


typedef struct {
    int qtBitsMode;
    int caracteres;
    char *mensagemAserCriptografada;
    char MODE_TYPE;//numerico alphanumerico ou byte
    char MODE_correcaoDeErro;
    char MODE_CORRECAO_AUTOMATICO;
    unsigned int numeroDoUltimoArquivo;
    char versao;
    char strBinMode4Bits[4], indicadorDecontagemDeCaracteres[10];
    char error;
    char *strbits;
    int tamanhoDaStrbits;
    int numeroDePalavrasChave_cd6;
    int numeroDePalavrasCodigoCorrecaoDeErro;
    unsigned  short *msgNumbers;
    int tamanhoDa_msgNumbers;
    int numeroDeBlocos;
} QRCODE;

QRCODE qrcode = {0};
FILE *logFile;

void freeqr() {
    free(qrcode.strbits);
}

void integerValueOf(char *str_init, char *str_intervalo_fim, char *str_final_maximo, int *n) {
    if (str_init < str_final_maximo && str_init < str_intervalo_fim) {
        if (*str_init >= '0' && *str_init <= '9')
            *n = *n * 10 + ((*str_init - '0'));
        integerValueOf((str_init + 1), str_intervalo_fim, str_final_maximo, n);
    }
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
void converterParaBinario(char *buff, int decimal, int bits) {
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

void printa8Bits(FILE *f, char *str) {
    int i, j, k = 0;
    for (i = 0; str[k]; ++i) {
        for (j = 0; str[k] && j < 8; j++) {
            fprintf(f, "%c", str[k++]);
        }
        fprintf(f, " ");
    }
}

#endif
