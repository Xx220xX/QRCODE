#ifndef OBJECT_H_H
#define OBJECT_H_H

#include<stdlib.h>

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


typedef struct {
    int qtBitsMode;
    int caracteres;
    char *mensagemAserCriptografada;
    char MODE_OF_TXT;
    char MODE_correcaoDeErro;
    char MODE_CORRECAO_AUTOMATICO;
    unsigned int numeroDoUltimoArquivo;
    char versao;
    char strBinMode4Bits[4], indicadorDecontagemDeCaracteres[10];
    char error;
    char *strbits;
    int tamanhoDaStrbits;
    int numeroDePalavrasChave_cd6;
} QRCODE;

QRCODE qrcode = {0};
FILE *logFile;

void freeqr() {
    free(qrcode.strbits);
}

void integerValueOf(char *str_init, char *str_fim, char *str_max, int *n) {
    if (str_init < str_max && str_init < str_fim) {
        if (*str_init >= '0' && *str_init <= '9')
            *n = *n * 10 + ((*str_init - '0'));
        integerValueOf((str_init + 1), str_fim, str_max, n);
    }
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
    if (str[0]) {
        return 1 + contaLetras(str + 1);
    }
    return 0;
}

#endif
