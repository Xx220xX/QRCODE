#ifndef CODIFIC_H_H
#define CODIFIC_H_H

#include <stdlib.h>
#include <stdio.h>
#include "Object.h"

#define ESCOLHER_VERSAO(v1, v2, v3)\
       if (qrcode.tamanhoDa_mensagemAserCriptografada <= v1) {\
        qrcode.tabela.version = 1;\
     }else if (qrcode.tamanhoDa_mensagemAserCriptografada <= v2) {\
            qrcode.tabela.version = 2;\
     }else if (qrcode.tamanhoDa_mensagemAserCriptografada <= v3) {\
            qrcode.tabela.version = 3;\
     }else \
        qrcode.error = EXCEPTION_LENGTH_UNSUPPORTED


void modoNumerico();

/*
 * Etapa de codificao:
 ~concluido~*   ETAPA 2:
 *                  ***obs: o usuario escolhe a correcao de erro
 *                  conte o n?mero de tamanhoDa_mensagemAserCriptografada a serem codificados
 *                  determinar modo a ser crptografado
 *                  determine qual ? a menor vers?o que pode conter esse n?mero de tamanhoDa_mensagemAserCriptografada para o modo de codifica??o e o n?vel de corre??o
 *
 ~concluido~ *  ETAPA 3:
 *                  converter para string de 4 bytes o indicador de modo
 *                  0001 para MODO_NUMERICO
 *                  0010 para MODO_ALPHANUMERICO
 *                  0100 para MODO_BYTE
  ~concluido~*  ETAPA 4:
 *                  contar os tamanhoDa_mensagemAserCriptografada da frase a ser criptografada
 *                  antes de converter defina a quantidade de bits que seu binario tera
 *                  10 bits para MODO_NUMERICO
 *                  9 bits para MODO_ALPHANUMERICO
 *                  8 bits para MODO_BYTE
 *                  converter o numero de tamanhoDa_mensagemAserCriptografada para binario
 *                  unir a seq de 4 bits da etapa anterior com a sequencia de bits atual(numero de letras em binario)
 *              ETAPA 5:
 *
 *
 *
 *
 */
void CODF_ETAPA1() {
    int i = 0;
    for (; qrcode.mensagemAserCriptografada[i]; i++) {
        if (qrcode.mensagemAserCriptografada[i] >= '0' && qrcode.mensagemAserCriptografada[i] <= '9' &&
            qrcode.MODE_TYPE != MODO_ALPHANUMERICO) {
            qrcode.MODE_TYPE = MODO_NUMERICO;
        } else if ((qrcode.mensagemAserCriptografada[i] >= 'A' && qrcode.mensagemAserCriptografada[i] <= 'Z') ||
                   qrcode.mensagemAserCriptografada[i] == '$' || qrcode.mensagemAserCriptografada[i] == '%' ||
                   qrcode.mensagemAserCriptografada[i] == '*' || qrcode.mensagemAserCriptografada[i] == '+' ||
                   qrcode.mensagemAserCriptografada[i] == '-' || qrcode.mensagemAserCriptografada[i] == '.' ||
                   qrcode.mensagemAserCriptografada[i] == '/' || qrcode.mensagemAserCriptografada[i] == ':' ||
                   qrcode.mensagemAserCriptografada[i] == ' ' ||
                   (qrcode.mensagemAserCriptografada[i] >= '0' && qrcode.mensagemAserCriptografada[i] <= '9')) {
            qrcode.MODE_TYPE = MODO_ALPHANUMERICO;
        } else {
            qrcode.MODE_TYPE = MODO_BYTE;
            break;
        }

    }


    LOG("CODIFICACAO ETAPA1\n   Mensagem: %s\n   modo: %s %d\n\n", qrcode.mensagemAserCriptografada,
        qrcode.MODE_TYPE == MODO_NUMERICO ? "MODO_NUMERICO" : qrcode.MODE_TYPE ==
                                                              MODO_ALPHANUMERICO ? "MODO_ALPHANUMERICO" : "MODO_BYTE",
        qrcode.MODE_TYPE);
}

void CODF_ETAPA2() {
    //conte o n?mero de tamanhoDa_mensagemAserCriptografada a serem codificados
    //determinar modo a ser crptografado
    //determine qual ? a menor vers?o que pode conter esse n?mero de tamanhoDa_mensagemAserCriptografada para o modo de codifica??o e o n?vel de corre??o
    for (qrcode.tamanhoDa_mensagemAserCriptografada = 0; qrcode.mensagemAserCriptografada[qrcode.tamanhoDa_mensagemAserCriptografada]; qrcode.tamanhoDa_mensagemAserCriptografada++) {}
    qrcode.error = 0;
    switch (qrcode.MODE_TYPE) {
        case MODO_NUMERICO:
            switch (qrcode.tabela.nivelCorrecaoErro) {
                case CORRECAO_MODO_L:
                    ESCOLHER_VERSAO(41, 77, 127);
                    break;
                case CORRECAO_MODO_M:
                    ESCOLHER_VERSAO(34, 63, 101);
                    break;
                case CORRECAO_MODO_Q:
                    ESCOLHER_VERSAO(27, 48, 77);
                    break;
                case CORRECAO_MODO_H:
                    ESCOLHER_VERSAO(17, 34, 58);
                    break;
                default:
                    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                    break;
            }
            break;
        case MODO_ALPHANUMERICO:
            switch (qrcode.tabela.nivelCorrecaoErro) {
                case CORRECAO_MODO_L:
                    ESCOLHER_VERSAO(25, 47, 77);
                    break;
                case CORRECAO_MODO_M:
                    ESCOLHER_VERSAO(20, 38, 61);
                    break;
                case CORRECAO_MODO_Q:
                    ESCOLHER_VERSAO(16, 29, 47);
                    break;
                case CORRECAO_MODO_H:
                    ESCOLHER_VERSAO(10, 20, 35);
                    break;
                default:
                    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                    break;
            }
            break;

        case MODO_BYTE:
            switch (qrcode.tabela.nivelCorrecaoErro) {
                case CORRECAO_MODO_L:
                    ESCOLHER_VERSAO(17, 32, 53);
                    break;
                case CORRECAO_MODO_M:
                    ESCOLHER_VERSAO(14, 26, 42);
                    break;
                case CORRECAO_MODO_Q:
                    ESCOLHER_VERSAO(11, 20, 32);
                    break;
                case CORRECAO_MODO_H:
                    ESCOLHER_VERSAO(7, 14, 24);
                    break;
                default:
                    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                    break;
            }
        default:
            break;
    }
    if (qrcode.error == EXCEPTION_LENGTH_UNSUPPORTED && qrcode.MODE_CORRECAO_AUTOMATICO == 1) {
        switch (qrcode.tabela.nivelCorrecaoErro) {
            case CORRECAO_MODO_H:
                qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_Q;
                CODF_ETAPA2();
                break;
            case CORRECAO_MODO_Q:
                qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_M;
                CODF_ETAPA2();
                break;
            case CORRECAO_MODO_M:
                qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_L;
                CODF_ETAPA2();
                break;
            default:
                break;

        }

    } else {
        LOG("CODIFICACAO ETAPA2\n   Modo erro: %c\n   Version %d\n\n", qrcode.tabela.nivelCorrecaoErro,
            qrcode.tabela.version);

    }
    if (qrcode.error < 0) {
        LOG("~ERROR  %d:CODIFICACAO ETAPA2, TAMANHO %d, NIVEL TENTADO : %c\n ", qrcode.error, qrcode.tamanhoDa_mensagemAserCriptografada, qrcode.tabela.nivelCorrecaoErro);
    }

}
// o usuario escolhe a correcao de erro


void CODF_ETAPA3() {
    ERROR();
    // converter para string de 4 bytes o indicador de modo
    // 0001 para MODO_NUMERICO
    // 0010 para MODO_ALPHANUMERICO
    // 0100 para MODO_BYTE

    converterParaBinario(qrcode.strBinMode4Bits, qrcode.MODE_TYPE, 4);
    LOG("CODIFICACAO ETAPA3 \n   indicador de modo: %s\n\n", qrcode.strBinMode4Bits);

}

void CODF_ETAPA4() {
    ERROR();
    //contar os tamanhoDa_mensagemAserCriptografada da frase a ser criptografada
    // antes de converter defina a quantidade de bits que seu binario tera
    // 10 bits para MODO_NUMERICO
    // 9 bits para MODO_ALPHANUMERICO
    // 8 bits para MODO_BYTE
    //converter o numero de tamanhoDa_mensagemAserCriptografada para binario
    int i, j;
    qrcode.qtBitsMode = (qrcode.MODE_TYPE == MODO_NUMERICO) * 10 + (qrcode.MODE_TYPE == MODO_ALPHANUMERICO) * 9 +
                        (qrcode.MODE_TYPE == MODO_BYTE) * 8;
    converterParaBinario(qrcode.indicadorDecontagemDeCaracteres, qrcode.tamanhoDa_mensagemAserCriptografada,
                         qrcode.qtBitsMode);
    // unir a seq de 4 bits da etapa anterior com a sequencia de bits atual(numero de letras em binario)
    qrcode.strbits = (char *) calloc(qrcode.qtBitsMode + 4 + 1, sizeof(char));
    for (i = 0; i < 4; i++) {
        qrcode.strbits[i] = qrcode.strBinMode4Bits[i];
    }
    for (i = 4, j = 0; j < qrcode.qtBitsMode; i++, j++) {
        qrcode.strbits[i] = qrcode.indicadorDecontagemDeCaracteres[j];
    }
    qrcode.strbits[i] = 0;
    LOG("CODIFICACAO ETAPA4 \n   quantidade de bits :%d   %s\n   strings concatendas: %s\n\n", qrcode.qtBitsMode,
        qrcode.indicadorDecontagemDeCaracteres, qrcode.strbits);
}


void modoAlphanumerico() {
    int coluna = 2, i, valor, tamanhoDastfin, bits = 1, j;
    char *stfin;

    if (qrcode.tamanhoDa_mensagemAserCriptografada % 2) {
        tamanhoDastfin = ((qrcode.tamanhoDa_mensagemAserCriptografada - 1) / 2) * 11 + 6;
    } else
        tamanhoDastfin = ((qrcode.tamanhoDa_mensagemAserCriptografada) / 2) * 11;
    tamanhoDastfin++;

    stfin = (char *) calloc(tamanhoDastfin, sizeof(char));
    qrcode.tamanhoDa_mensagemAserCriptografada = contaLetras(qrcode.mensagemAserCriptografada);
    logFile = fopen("debug.txt", "a");
    if (!logFile) {
        logFile = fopen("debug.txt", "w");
    }

    for (i = 0; i < qrcode.tamanhoDa_mensagemAserCriptografada / coluna; i++) {
        valor = alphaValue(qrcode.mensagemAserCriptografada[i * coluna], qrcode.mensagemAserCriptografada[i * coluna +
                                                                                                          1]);
        converterParaBinario(stfin + bits - 1, valor, 11);
        fprintf(logFile, "%s\n", stfin + bits - 1);
        bits += 11;
    }
    if (qrcode.tamanhoDa_mensagemAserCriptografada % 2) {
        valor = alphaValue('0', qrcode.mensagemAserCriptografada[qrcode.tamanhoDa_mensagemAserCriptografada - 1]);
        converterParaBinario(stfin + bits - 1, valor, 6);
        fprintf(logFile, "%s\n", stfin + bits - 1);
        bits += 6;
    }

    qrcode.strbits = (char *) realloc(qrcode.strbits, bits + 4 + qrcode.qtBitsMode);
    for (i = qrcode.qtBitsMode + 4, j = 0; stfin[j]; i++, j++) {
        qrcode.strbits[i] = stfin[j];
    }
    qrcode.strbits[i] = 0;

    fprintf(logFile, "   numeros convertidos %s\n", stfin);
    fprintf(logFile, "   str bits %s\n", qrcode.strbits);
    fclose(logFile);
    free(stfin);
}


void modoByte() {
        int i,j =0;
        char *strfim=0;
        logFile = fopen("debug.txt","a");
        for(i=0;qrcode.mensagemAserCriptografada[i];i++){
            strfim =  realloc(strfim,i*8+9);
            converterParaBinario(strfim+i*8,qrcode.mensagemAserCriptografada[i],8);
            fprintf(logFile, "   [%c  %d ] %s\n", qrcode.mensagemAserCriptografada[i], qrcode.mensagemAserCriptografada[i],
                    strfim + i * 8);
        }
        strfim = realloc(strfim,i*8+1);
        strfim[i*8]=0;

    qrcode.strbits = (char *) realloc(qrcode.strbits, i*8 + 4 + qrcode.qtBitsMode);
    for (i = qrcode.qtBitsMode + 4, j = 0; strfim[j]; i++, j++) {
        qrcode.strbits[i] = strfim[j];
    }
    qrcode.strbits[i] = 0;

    fprintf(logFile, "   numeros convertidos %s\n", strfim);
    fprintf(logFile, "   str bits %s\n", qrcode.strbits);
    fclose(logFile);
        free(strfim);
}


void CODF_ETAPA5() {
// Encode Using the Selected Mode
    ERROR();
    LOG("CODIFICACAO ETAPA5\n");
    switch (qrcode.MODE_TYPE) {
        case MODO_NUMERICO:
            modoNumerico();
            break;
        case MODO_ALPHANUMERICO:
            modoAlphanumerico();
            break;
        case MODO_BYTE:
            modoByte();
            break;
        default:
            break;
    }
    LOG("fim da etapa 5\n");
}

void CODF_ETAPA6() {
    ERROR();
    int add = 1;
    LOG("ETAPA 6\n");
    //determinar numero de bits necessarios
    switch (qrcode.tabela.version) {
        case 1:
        COMPARE_MODO_CORRECAO(qrcode.tabela.numeroTotaldePalavrasChavedeDados, qrcode.tabela.nivelCorrecaoErro, 19, 16,
                              13, 9);
            break;
        case 2:
        COMPARE_MODO_CORRECAO(qrcode.tabela.numeroTotaldePalavrasChavedeDados, qrcode.tabela.nivelCorrecaoErro, 34, 28,
                              22, 16);
            break;
        case 3:
        COMPARE_MODO_CORRECAO(qrcode.tabela.numeroTotaldePalavrasChavedeDados, qrcode.tabela.nivelCorrecaoErro, 55, 44,
                              34, 26);
            break;
        default:
            qrcode.error = EXCEPTION_BUG_IN_CHOSEN_VERSION;
    }
    LOG("   N de palavras chaves: %d\n", qrcode.tabela.numeroTotaldePalavrasChavedeDados);
//deixar multiplo de 8
    while ((qrcode.tamanhoDaStrbits = contaLetras(qrcode.strbits)) % 8 != 0) {
        qrcode.strbits = realloc(qrcode.strbits, 2 + qrcode.tamanhoDaStrbits);//1230*
        qrcode.strbits[qrcode.tamanhoDaStrbits] = '0';
        qrcode.strbits[qrcode.tamanhoDaStrbits + 1] = 0;
    }
    LOG("   strbits : %s\n   tamanho : %d\n", qrcode.strbits, qrcode.tamanhoDaStrbits);
    //multiplica o numero de palavras chave por  8
    qrcode.tabela.numeroTotaldePalavrasChavedeDados *= 8;
    while ((qrcode.tamanhoDaStrbits = contaLetras(qrcode.strbits)) < qrcode.tabela.numeroTotaldePalavrasChavedeDados) {
        qrcode.strbits = realloc(qrcode.strbits, 9 + qrcode.tamanhoDaStrbits);
        if (add) {
            converterParaBinario(qrcode.strbits + qrcode.tamanhoDaStrbits, 236, 8);
            add = 0;
        } else {
            converterParaBinario(qrcode.strbits + qrcode.tamanhoDaStrbits, 17, 8);
            add = 1;
        }
    }
    LOG("   adicionando 236 17 , strbits : ");
    logFile = fopen("debug.txt", "a");
    printa8Bits(logFile, qrcode.strbits, qrcode.tamanhoDaStrbits);
    fprintf(logFile, "\n");
    fclose(logFile);

}

void modoNumerico() {
    char *stfin;
    int coluna = 3;
    int i, j, a = 0, bits = 1, tamanhoDastfin = (qrcode.tamanhoDa_mensagemAserCriptografada / 3) * 10;
    if ((j = qrcode.tamanhoDa_mensagemAserCriptografada % 3) == 2) {
        tamanhoDastfin += 7;
    } else if (j == 1) {
        tamanhoDastfin += 4;
    }
    tamanhoDastfin++;
    stfin = (char *) calloc(tamanhoDastfin, sizeof(char));
    qrcode.tamanhoDa_mensagemAserCriptografada = contaLetras(qrcode.mensagemAserCriptografada);
    logFile = fopen("debug.txt", "a");
    if (!logFile) {
        logFile = fopen("debug.txt", "w");
    }

    for (i = 0; i < qrcode.tamanhoDa_mensagemAserCriptografada; i += coluna) {
        integerValueOf(
                qrcode.mensagemAserCriptografada + i,
                qrcode.mensagemAserCriptografada + (i / coluna) * coluna + coluna,
                qrcode.mensagemAserCriptografada + qrcode.tamanhoDa_mensagemAserCriptografada, &a);
        fprintf(logFile, "   %d     ", a);
        if (a < 10) {
            converterParaBinario(stfin + bits - 1, a, 4);
            fprintf(logFile, "%s\n", stfin + bits - 1);
            bits += 4;
        } else if (a < 100) {
            converterParaBinario(stfin + bits - 1, a, 7);
            fprintf(logFile, "%s\n", stfin + bits - 1);
            bits += 7;
        } else {
            converterParaBinario(stfin + bits - 1, a, 10);
            fprintf(logFile, "%s\n", stfin + bits - 1);
            bits += 10;
        }

        a = 0;
    }
    qrcode.strbits = (char *) realloc(qrcode.strbits, bits + 4 + qrcode.qtBitsMode);
    for (i = qrcode.qtBitsMode + 4, j = 0; stfin[j]; i++, j++) {
        qrcode.strbits[i] = stfin[j];
    }
    qrcode.strbits[i] = 0;

    fprintf(logFile, "   numeros convertidos %s\n", stfin);
    fprintf(logFile, "   str bits %s\n", qrcode.strbits);
    fclose(logFile);
    free(stfin);

}

void CODF_ALL_STEPS() {
    LOG("########################## CODIFICACAO ##########################\n");
    CODF_ETAPA1();
    CODF_ETAPA2();
    CODF_ETAPA3();
    CODF_ETAPA4();
    CODF_ETAPA5();
    CODF_ETAPA6();
    LOG("__________________________________________________________________________________________________\n\n\n");
}

#endif

 
