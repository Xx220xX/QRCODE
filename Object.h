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
} Table;
typedef struct {
    Table tabela;
    int qtBitsMode;
    
    int tamanhoDa_mensagemAserCriptografada;
    char *mensagemAserCriptografada;
    
    char MODE_TYPE;//numerico alphanumerico ou byte
    char MODE_CORRECAO_AUTOMATICO;
    
    unsigned int numeroDoUltimoArquivo;
    char strBinMode4Bits[4], indicadorDecontagemDeCaracteres[10];
    char error;
    
    char *strbits;
    int tamanhoDaStrbits;
    
    unsigned short *msgNumbers;
    int tamanhoDa_msgNumbers;
    char *codigosCorretores;
    int tamanhoDosCodigosCorretores;
} QRCODE;
QRCODE qrcode = {0};
FILE *logFile;

void freeqr() {
    if (qrcode.strbits) {
        free(qrcode.strbits);
    }
    if (qrcode.msgNumbers) {
        free(qrcode.msgNumbers);
    }
    if (qrcode.codigosCorretores) {
        free(qrcode.codigosCorretores);
    }
}

void integerValueOf(char *str_init, char *str_intervalo_fim, char *str_final_maximo, int *n) {
    if (str_init < str_final_maximo && str_init < str_intervalo_fim) {
        if (*str_init >= '0' && *str_init <= '9')
            *n = *n * 10 + ((*str_init - '0'));
        integerValueOf((str_init + 1), str_intervalo_fim, str_final_maximo, n);
    }
}

int alphaValue(int x1, int x2) {
    int valor;
    if (x1 >= '0' && x1 <= '9')
        x1 = x1 - '0';
    else if (x1 >= 'A' && x1 <= 'Z')
        x1 = x1 - 'A' + 10;
    else
        x1 = ((x1 == ' ') * 36 + (x1 == '$') * 37 + (x1 == '%') * 38 + (x1 == '*') * 39 + (x1 == '+') * 40 + (x1 == '-') * 41 + (x1 == '.') * 42 + (x1 == '/') * 43 + (x1 == ':') * 44);
    if (x2 >= '0' && x2 <= '9')
        x2 = x2 - '0';
    else if (x2 >= 'A' && x2 <= 'Z')
        x2 = x2 - 'A' + 10;
    else
        x2 = ((x2 == ' ') * 36 + (x2 == '$') * 37 + (x2 == '%') * 38 + (x2 == '*') * 39 + (x2 == '+') * 40 + (x2 == '-') * 41 + (x2 == '.') * 42 + (x2 == '/') * 43 + (x2 == ':') * 44);
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


#endif
