#ifndef QRCODE_CORRECAO_DE_ERROS_H_H
#define QRCODE_CORRECAO_DE_ERROS_H_H

#include <stdio.h>
#include "Object.h"


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

    LOG("CORRECAO_ETAPA8\n   bytes: %d\n   ", bytes);
    logFile = fopen("debug.txt", "a");
    printa8Bits(logFile, qrcode.strbits);
    fprintf(logFile, "\n   ");
    for (i = 0; i < bytes; ++i) {
        fprintf(logFile, "%d ", dec[i]);
    }

    fclose(logFile);
    free(dec);
}

// Programa que mostra exemplo de como utilizar a biblioteca QRCode.h para determinar os Error Correction Codewords



void imprimeVetor(unsigned char v[], unsigned short N);

int test() {
    unsigned short mens1[15] = {67, 85, 70, 134, 87, 38, 85, 194, 119, 50, 6, 18, 6, 103, 38};
    unsigned short mens2[15] = {246, 246, 66, 7, 118, 134, 242, 7, 38, 86, 22, 198, 199, 146, 6};
    unsigned short mens3[16] = {182, 230, 247, 119, 50, 7, 118, 134, 87, 38, 82, 6, 134, 151, 50, 7};
    unsigned char *cod1, *cod2, *cod3, *codStringFormat;

    printf("Codigos 1: ");
    cod1 = CodigosCorretores(mens1, 15, 18);
    imprimeVetor(cod1, 18);
    printf("\n\n");

    printf("Codigos 2: ");
    cod2 = CodigosCorretores(mens2, 15, 18);
    imprimeVetor(cod2, 18);
    printf("\n\n");

    printf("Codigos 3: ");
    cod3 = CodigosCorretores(mens3, 16, 18);
    imprimeVetor(cod3, 18);
    printf("\n\n");

    codStringFormat = CodigosCorretoresStringFormat("01100");
    printf("Codigos Corretores da String Format: %s\n", codStringFormat);

    // As 4 linhas seguintes libera a mem�ria alocada dinamicamente pela fun��o de c�lculos dos c�digos corretores
    free(cod1);
    free(cod2);
    free(cod3);
    free(codStringFormat);

    return 0;
}

void imprimeVetor(unsigned char v[], unsigned short N) {
    unsigned short i;

    for (i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
}


#endif //QRCODE_CORRECAO_DE_ERROS_H_H
