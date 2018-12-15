#ifndef CODIFIC_H_H
#define CODIFIC_H_H

#include <stdlib.h>
#include <stdio.h>
#include "Object.h"

#define ESCOLHER_NIVEL(x, y, v1, v2, v3, v4){\
    x = (y==CORRECAO_MODO_L)*v1+(y==CORRECAO_MODO_M)*v2+(y==CORRECAO_MODO_Q)*v3+(y==CORRECAO_MODO_H)*v4; \
}

void modoNumerico();

/*
 * Etapa de codificao:
 ~concluido~*   ETAPA 2:
 *                  ***obs: o usuario escolhe a correcao de erro
 *                  conte o n�mero de caracteres a serem codificados
 *                  determinar modo a ser crptografado
 *                  determine qual � a menor vers�o que pode conter esse n�mero de caracteres para o modo de codifica��o e o n�vel de corre��o
 *
 ~concluido~ *  ETAPA 3:
 *                  converter para string de 4 bytes o indicador de modo
 *                  0001 para MODO_NUMERICO
 *                  0010 para MODO_ALPHANUMERICO
 *                  0100 para MODO_BYTE
  ~concluido~*  ETAPA 4:
 *                  contar os caracteres da frase a ser criptografada
 *                  antes de converter defina a quantidade de bits que seu binario tera
 *                  10 bits para MODO_NUMERICO
 *                  9 bits para MODO_ALPHANUMERICO
 *                  8 bits para MODO_BYTE
 *                  converter o numero de caracteres para binario
 *                  unir a seq de 4 bits da etapa anterior com a sequencia de bits atual(numero de letras em binario)
 *              ETAPA 5:
 *
 *
 *
 *
 */
void CODF_ETAPA1() {
    int i = 0, flag = 0;
    qrcode.MODE = 0;
    for (; qrcode.mensagemAserCriptografada[i]; i++) {
        printf("%c  ", qrcode.mensagemAserCriptografada[i]);
        if (qrcode.mensagemAserCriptografada[i] >= '0' && qrcode.mensagemAserCriptografada[i] <= '9' &&
            qrcode.MODE != MODO_ALPHANUMERICO) {
            qrcode.MODE = MODO_NUMERICO;
            printf(" if \n");
        } else if ((qrcode.mensagemAserCriptografada[i] >= 'A' && qrcode.mensagemAserCriptografada[i] <= 'Z') ||
                   qrcode.mensagemAserCriptografada[i] == '$' || qrcode.mensagemAserCriptografada[i] == '%' ||
                   qrcode.mensagemAserCriptografada[i] == '*' || qrcode.mensagemAserCriptografada[i] == '+' ||
                   qrcode.mensagemAserCriptografada[i] == '-' || qrcode.mensagemAserCriptografada[i] == '.' ||
                   qrcode.mensagemAserCriptografada[i] == '/' || qrcode.mensagemAserCriptografada[i] == ':' ||
                   qrcode.mensagemAserCriptografada[i] == ' ' ||
                   (qrcode.mensagemAserCriptografada[i] >= '0' && qrcode.mensagemAserCriptografada[i] <= '9')) {
            qrcode.MODE = MODO_ALPHANUMERICO;
            printf("else if \n");
        } else {
            qrcode.MODE = MODO_BYTE;
            printf(" else  \n");
            break;
        }

    }

    FILE *log;
    log = fopen("debug.txt", "a");
    if (!log) {
        log = fopen("debug.txt", "w");
    }
    fprintf(log, "CODIFICACAO ETAPA1\nMensagem: %s\nmodo: %s %d\n\n", qrcode.mensagemAserCriptografada,
            qrcode.MODE == MODO_NUMERICO ? "MODO_NUMERICO" : qrcode.MODE ==
                                                             MODO_ALPHANUMERICO ? "MODO_ALPHANUMERICO" : "MODO_BYTE", qrcode.MODE);
    fclose(log);
}

void CODF_ETAPA2() {
    //conte o n�mero de caracteres a serem codificados
    //determinar modo a ser crptografado
    //determine qual � a menor vers�o que pode conter esse n�mero de caracteres para o modo de codifica��o e o n�vel de corre��o
    for (qrcode.caracteres = 0; qrcode.mensagemAserCriptografada[qrcode.caracteres]; qrcode.caracteres++) {}
    qrcode.error = 0;
    switch (qrcode.MODE) {
        case MODO_NUMERICO:
            switch (qrcode.MODE_correcaoDeErro) {
                case CORRECAO_MODO_L:
                    if (qrcode.caracteres < 41) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 77) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 127) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_M:
                    if (qrcode.caracteres < 34) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 63) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 101) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_Q:
                    if (qrcode.caracteres < 27) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 48) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 77) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_H:
                    if (qrcode.caracteres < 17) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 34) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 58) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
            }
            break;
        case MODO_ALPHANUMERICO:
            switch (qrcode.MODE_correcaoDeErro) {
                case CORRECAO_MODO_L:
                    if (qrcode.caracteres < 25) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 47) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 77) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_M:
                    if (qrcode.caracteres < 20) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 38) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 61) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_Q:
                    if (qrcode.caracteres < 16) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 29) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 47) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_H:
                    if (qrcode.caracteres < 10) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 20) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 35) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
            }
            break;

        case MODO_BYTE:
            switch (qrcode.MODE_correcaoDeErro) {
                case CORRECAO_MODO_L:
                    if (qrcode.caracteres < 17) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 32) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 53) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_M:
                    if (qrcode.caracteres < 14) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 26) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 42) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_Q:
                    if (qrcode.caracteres < 11) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 20) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 32) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;
                case CORRECAO_MODO_H:
                    if (qrcode.caracteres < 7) {
                        qrcode.versao = 1;
                    } else if (qrcode.caracteres < 53) {
                        qrcode.versao = 2;
                    } else if (qrcode.caracteres < 24) {
                        qrcode.versao = 3;
                    } else {
                        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED;
                    }
                    break;

            }
    }
    if (qrcode.error == EXCEPTION_LENGTH_UNSUPPORTED && qrcode.MODE_CORRECAO_AUTOMATICO == 1) {

        switch (qrcode.MODE_correcaoDeErro) {
            case CORRECAO_MODO_H:
                qrcode.MODE_correcaoDeErro = CORRECAO_MODO_Q;
                CODF_ETAPA2();
                break;
            case CORRECAO_MODO_Q:
                qrcode.MODE_correcaoDeErro = CORRECAO_MODO_M;
                CODF_ETAPA2();
                break;
            case CORRECAO_MODO_M:
                qrcode.MODE_correcaoDeErro = CORRECAO_MODO_L;
                CODF_ETAPA2();
                break;

        }

    } else {
        FILE *log;
        log = fopen("debug.txt", "a");
        if (!log) {
            log = fopen("debug.txt", "w");
        }
        fprintf(log, "CODIFICACAO ETAPA2\nmodo: %d\nversao: %d\n Modo erro: %c\n\n", qrcode.MODE, qrcode.versao, qrcode.MODE_correcaoDeErro);
        fclose(log);
    }
    if (qrcode.error < 0) {
        FILE *log;
        log = fopen("debug.txt", "a");
        if (!log) {
            log = fopen("debug.txt", "w");
        }
        fprintf(log, "~ERROR  %d:CODIFICACAO ETAPA2\n ", qrcode.error);
        fclose(log);
    }

}
// o usuario escolhe a correcao de erro


void CODF_ETAPA3() {
    if (qrcode.error < 0)
        return;
    // converter para string de 4 bytes o indicador de modo
    // 0001 para MODO_NUMERICO
    // 0010 para MODO_ALPHANUMERICO
    // 0100 para MODO_BYTE

    converterParaBinario(qrcode.strBinMode4Bits, qrcode.MODE, 4);
    FILE *log;
    log = fopen("debug.txt", "a");
    if (!log) {
        log = fopen("debug.txt", "w");
    }
    fprintf(log, "CODIFICACAO ETAPA3 \nindicador de modo: %s\n", qrcode.strBinMode4Bits);
    fclose(log);
}

void CODF_ETAPA4() {
    // if (qrcode.error < 0)
    //   return;
    //contar os caracteres da frase a ser criptografada
    // antes de converter defina a quantidade de bits que seu binario tera
    // 10 bits para MODO_NUMERICO
    // 9 bits para MODO_ALPHANUMERICO
    // 8 bits para MODO_BYTE
    //converter o numero de caracteres para binario
    int i, j;

    qrcode.qtBitsMode = (qrcode.MODE == MODO_NUMERICO) * 10 + (qrcode.MODE == MODO_ALPHANUMERICO) * 9 +
                        (qrcode.MODE == MODO_BYTE) * 8;
    converterParaBinario(qrcode.indicadorDecontagemDeCaracteres, qrcode.caracteres, qrcode.qtBitsMode);
    // unir a seq de 4 bits da etapa anterior com a sequencia de bits atual(numero de letras em binario)
    qrcode.strbits = (char *) calloc(qrcode.qtBitsMode + 4 + 1, sizeof(char));
    for (i = 0; i < 4; i++) {
        qrcode.strbits[i] = qrcode.strBinMode4Bits[i];
    }
    for (i = 4, j = 0; j < qrcode.qtBitsMode; i++, j++) {
        qrcode.strbits[i] = qrcode.indicadorDecontagemDeCaracteres[j];
    }
    qrcode.strbits[i] = 0;
    FILE *log;
    log = fopen("debug.txt", "a");
    if (!log) {
        log = fopen("debug.txt", "w");
    }
    fprintf(log, "CODIFICACAO ETAPA4 \nquantidade de bits :%d    %s\nstrings concatendas: %s\n\n", qrcode.qtBitsMode, qrcode.indicadorDecontagemDeCaracteres, qrcode.strbits);
    fclose(log);
}

void CODF_ETAPA5() {
// Encode Using the Selected Mode
    FILE *log;
    log = fopen("debug.txt", "a");
    if (!log) {
        log = fopen("debug.txt", "w");
    }
    if (qrcode.error < 0) {
        fprintf(log, "~ERROR  %d:CODIFICACAO ETAPA5\n ", qrcode.error);
        fclose(log);
        return;
    }
    fprintf(log, "CODIFICACAO ETAPA5\n");
    fclose(log);
    switch (qrcode.MODE) {
        case MODO_NUMERICO:
            modoNumerico();
            break;
    }

}

void CODF_ETAPA6() {
    //determinar numero de bits necessarios

    switch (qrcode.versao) {
        case 1: ESCOLHER_NIVEL(qrcode.numeroDePalavrasChave_cd6, qrcode.MODE_CORRECAO_AUTOMATICO, 19, 16, 13, 9);
            break;
        case 2: ESCOLHER_NIVEL(qrcode.numeroDePalavrasChave_cd6, qrcode.MODE_CORRECAO_AUTOMATICO, 34, 28, 22, 16);
            break;
        case 2: ESCOLHER_NIVEL(qrcode.numeroDePalavrasChave_cd6, qrcode.MODE_CORRECAO_AUTOMATICO, 55, 44, 34, 26);
            break;

    }
}

void modoNumerico() {
    char *stfin;
    int coluna = 3;
    int i, j, a = 0, bits = 1, tamanhoDastfin = (qrcode.caracteres / 3) * 10;
    if ((j = qrcode.caracteres % 3) == 2) {
        tamanhoDastfin += 7;
    } else if (j == 1) {
        tamanhoDastfin += 4;
    }
    tamanhoDastfin++;
    stfin = (char *) calloc(tamanhoDastfin, sizeof(char));
    qrcode.caracteres = contaLetras(qrcode.mensagemAserCriptografada);

    FILE *log;
    log = fopen("debug.txt", "a");
    if (!log) {
        log = fopen("debug.txt", "w");
    }

    for (i = 0; i < qrcode.caracteres; i += coluna) {
        integerValueOf(
                qrcode.mensagemAserCriptografada + i,
                qrcode.mensagemAserCriptografada + (i / coluna) * coluna + coluna,
                qrcode.mensagemAserCriptografada + qrcode.caracteres, &a);
        fprintf(log, "    %d     ", a);
        if (a < 10) {

            converterParaBinario(stfin + bits - 1, a, 4);
            fprintf(log, "%s\n", stfin + bits - 1);
            bits += 4;
        } else if (a < 100) {
            converterParaBinario(stfin + bits - 1, a, 7);
            fprintf(log, "%s\n", stfin + bits - 1);
            bits += 7;
        } else {
            converterParaBinario(stfin + bits - 1, a, 10);
            fprintf(log, "%s\n", stfin + bits - 1);
            bits += 10;
        }
        stfin[bits] = 0;
        a = 0;
    }
    qrcode.strbits = (char *) realloc(qrcode.strbits, bits + 4 + qrcode.qtBitsMode);
    for (i = qrcode.qtBitsMode + 4, j = 0; stfin[j]; i++, j++) {
        qrcode.strbits[i] = stfin[j];
    }
    qrcode.strbits[i] = 0;

    fprintf(log, "numeros convertidos %s\n", stfin);
    fprintf(log, "str bits %s\n", qrcode.strbits);

    fclose(log);
    printf("fechou\n");
    free(stfin);
    printf("liberou\n");
}

#endif

 