#ifndef QRCODE_CORRECAO_DE_ERROS_H_H
#define QRCODE_CORRECAO_DE_ERROS_H_H

#include <stdio.h>
#include "Object.h"

#define CAST (unsigned short)

void imprimeVetor(unsigned char v[], unsigned short N);


void CORREC_ETAPA8() {
    if (qrcode.error < 0)
        return;
    //converter a strbits em decimal
    unsigned short *dec = 0;
    int bytes = 0, i;
    qrcode.tamanhoDaStrbits = contaLetras(qrcode.strbits);
    while ((bytes) * 8 < qrcode.tamanhoDaStrbits) {
        dec = realloc(dec, (bytes + 1) * 8);
        dec[bytes] = binaryToDec(
                qrcode.strbits + (bytes * 8),
                qrcode.strbits + ((1 + bytes) * 8), qrcode.strbits + qrcode.tamanhoDaStrbits * 8);
        bytes++;
    }
    //pegando numero de palavras de corretor de erro
    switch (qrcode.versao) {
        case 1:
        COMPARE_MODO_CORRECAO(qrcode.numeroDePalavrasCodigoCorrecaoDeErro, qrcode.MODE_correcaoDeErro, 7, 10, 13, 17);
            break;
        case 2:
        COMPARE_MODO_CORRECAO(qrcode.numeroDePalavrasCodigoCorrecaoDeErro, qrcode.MODE_correcaoDeErro, 10, 16, 22, 28);
            break;
        case 3:
        COMPARE_MODO_CORRECAO(qrcode.numeroDePalavrasCodigoCorrecaoDeErro, qrcode.MODE_correcaoDeErro, 15, 26, 18, 22);
            break;
        default:
            break;
    }
    qrcode.msgNumbers = dec;
    qrcode.tamanhoDa_msgNumbers = bytes;
    LOG("CORRECAO_ETAPA8\n   bytes: %d\n   ", bytes);
    logFile = fopen("debug.txt", "a");
    printa8Bits(logFile, qrcode.strbits);
    fprintf(logFile, "\n   ");
    for (i = 0; i < bytes; ++i) {
        fprintf(logFile, "%d ", dec[i]);
    }

    fclose(logFile);
}

void CORREC_CORRIGIR() {
    unsigned char *codigo = CodigosCorretores(qrcode.msgNumbers, CAST qrcode.tamanhoDa_msgNumbers, CAST qrcode.numeroDePalavrasCodigoCorrecaoDeErro);
    LOG("\ncodigos corretores : ", codigo);
    imprimeVetor(codigo, CAST qrcode.numeroDePalavrasCodigoCorrecaoDeErro);
    free(codigo);
}

// Programa que mostra exemplo de como utilizar a biblioteca QRCode.h para determinar os Error Correction Codewords




void imprimeVetor(unsigned char v[], unsigned short N) {
    unsigned short i;
    logFile = fopen("debug.txt", "a");
    for (i = 0; i < N; i++) {
        fprintf(logFile, "%d ", v[i]);
    }
    fprintf(logFile, "\n");
    fclose(logFile);
}
#undef CAST
#endif //QRCODE_CORRECAO_DE_ERROS_H_H
