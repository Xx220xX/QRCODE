#ifndef CODIFIC_H_H
#define CODIFIC_H_H

#include <stdlib.h>
#include <stdio.h>
#include "Object.h"




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
                                                              MODO_ALPHANUMERICO ? "MODO_ALPHANUMERICO" : "MODO_BYTE", qrcode.MODE_TYPE);
}

void CODF_ETAPA2() {
    //conte o n�mero de caracteres a serem codificados
    //determinar modo a ser crptografado
    //determine qual � a menor vers�o que pode conter esse n�mero de caracteres para o modo de codifica��o e o n�vel de corre��o
    for (qrcode.caracteres = 0; qrcode.mensagemAserCriptografada[qrcode.caracteres]; qrcode.caracteres++) {}
    qrcode.error = 0;
    switch (qrcode.MODE_TYPE) {
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
        LOG("CODIFICACAO ETAPA2\n   Modo erro: %c\n   Version %d\n\n", qrcode.MODE_correcaoDeErro, qrcode.versao);

    }
    if (qrcode.error < 0) {
        LOG("~ERROR  %d:CODIFICACAO ETAPA2\n ", qrcode.error);
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

    converterParaBinario(qrcode.strBinMode4Bits, qrcode.MODE_TYPE, 4);
    LOG("CODIFICACAO ETAPA3 \n   indicador de modo: %s\n\n", qrcode.strBinMode4Bits);

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
    qrcode.qtBitsMode = (qrcode.MODE_TYPE == MODO_NUMERICO) * 10 + (qrcode.MODE_TYPE == MODO_ALPHANUMERICO) * 9 +
                        (qrcode.MODE_TYPE == MODO_BYTE) * 8;
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
    LOG("CODIFICACAO ETAPA4 \n   quantidade de bits :%d   %s\n   strings concatendas: %s\n\n", qrcode.qtBitsMode, qrcode.indicadorDecontagemDeCaracteres, qrcode.strbits);
}

int alphaValue(int x1,int x2){

}
void modoAlphanumerico(){
    int coluna = 2;
    //HELO
    int i, valor;
    for(i=0; i < qrcode.caracteres/coluna; i++){
        valor = alphaValue(qrcode.mensagemAserCriptografada[i*coluna],qrcode.mensagemAserCriptografada[i*coluna+1]);
    }
}
void CODF_ETAPA5() {
// Encode Using the Selected Mode
    if (qrcode.error < 0) {
        LOG("~ERROR  %d:CODIFICACAO ETAPA5\n ", qrcode.error);
        return;
    }
    LOG("CODIFICACAO ETAPA5\n");
    switch (qrcode.MODE_TYPE) {
        case MODO_NUMERICO:
            modoNumerico();
            break;
        case MODO_ALPHANUMERICO:
            modoAlphanumerico();
        default:
            break;
    }
    LOG("\n");
}
void CODF_ETAPA6() {
    if (qrcode.error < 0)
        return;
    int add = 1;
    LOG("ETAPA 6\n");
    //determinar numero de bits necessarios
    switch (qrcode.versao) {
        case 1:
        COMPARE_MODO_CORRECAO(qrcode.numeroDePalavrasChave_cd6, qrcode.MODE_correcaoDeErro, 19, 16, 13, 9);
            break;
        case 2:
        COMPARE_MODO_CORRECAO(qrcode.numeroDePalavrasChave_cd6, qrcode.MODE_correcaoDeErro, 34, 28, 22, 16);
            break;
        case 3:
        COMPARE_MODO_CORRECAO(qrcode.numeroDePalavrasChave_cd6, qrcode.MODE_correcaoDeErro, 55, 44, 34, 26);
            break;
        default:
            qrcode.error = EXCEPTION_BUG_IN_CHOSEN_VERSION;
    }
    LOG("   N de palavras chaves: %d\n", qrcode.numeroDePalavrasChave_cd6);
//deixar multiplo de 8
    while ((qrcode.tamanhoDaStrbits = contaLetras(qrcode.strbits)) % 8 != 0) {
        qrcode.strbits = realloc(qrcode.strbits, 2 + qrcode.tamanhoDaStrbits);//1230*
        qrcode.strbits[qrcode.tamanhoDaStrbits] = '0';
        qrcode.strbits[qrcode.tamanhoDaStrbits + 1] = 0;
    }
    LOG("   strbits : %s\n   tamanho : %d\n", qrcode.strbits, qrcode.tamanhoDaStrbits);
    //multiplica o numero de palavras chave por  8
    qrcode.numeroDePalavrasChave_cd6 *= 8;
    while ((qrcode.tamanhoDaStrbits = contaLetras(qrcode.strbits)) < qrcode.numeroDePalavrasChave_cd6) {
        qrcode.strbits = realloc(qrcode.strbits, 9 + qrcode.tamanhoDaStrbits);
        if (add) {
            converterParaBinario(qrcode.strbits + qrcode.tamanhoDaStrbits, 236, 8);
            add = 0;
        } else {
            converterParaBinario(qrcode.strbits + qrcode.tamanhoDaStrbits, 17, 8);
            add = 1;
        }
    }
    LOG("   adicionando 236 17 , strbits : %s\n\n", qrcode.strbits, qrcode.tamanhoDaStrbits);

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
    logFile = fopen("debug.txt", "a");
    if (!logFile) {
        logFile = fopen("debug.txt", "w");
    }

    for (i = 0; i < qrcode.caracteres; i += coluna) {
        integerValueOf(
                qrcode.mensagemAserCriptografada + i,
                qrcode.mensagemAserCriptografada + (i / coluna) * coluna + coluna,
                qrcode.mensagemAserCriptografada + qrcode.caracteres, &a);
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

 