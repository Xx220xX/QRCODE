#ifndef QRCODE_FORMATOEINFORMACAODAVERSAO_H
#define QRCODE_FORMATOEINFORMACAODAVERSAO_H

#include "Object.h"


void string_format(char str[15], unsigned int numero_mascara) {
    unsigned char *codStringFormat;
    int modo_erro, i, j;
    modo_erro = (qrcode.tabela.nivelCorrecaoErro == CORRECAO_MODO_L) * 1 + (qrcode.tabela.nivelCorrecaoErro == CORRECAO_MODO_Q) * 3 + (qrcode.tabela.nivelCorrecaoErro == CORRECAO_MODO_H) * 2;
    converterParaBinario(str, modo_erro, 2);
    converterParaBinario(str + 2, numero_mascara, 3);
    codStringFormat = CodigosCorretoresStringFormat(str);
    for (i = 5, j = 0; j < 15; i++, j++) {
        str[i] = codStringFormat[j];
    }
    //printf("Codigos Corretores da String Format: %s\n",codStringFormat);
    //printf("final : %s ", str);
    free(codStringFormat);
}

void insere_string_format_ETAPA_1() {
    int i = 0, j = 8, k = 14;
    int ordem = qrcode.QRImagem.m;
    char str[15];
    string_format(str, qrcode.tabela.maskara);
    //lateral da querda superior
    while (i <= 8) {
        qrcode.QRImagem.mat[i * ordem + j] = str[k];
        if (i == 5) {
            i = i + 2;
            k--;
        } else {
            i++;
            k--;
        }
    }
    //baixo da esquerda superior
    i = 8;
    j = 0;
    k = 0;
    while (j <= 8) {
        qrcode.QRImagem.mat[i * ordem + j] = str[k];
        if (j == 5) {
            j = j + 2;
            k++;
        } else {
            j++;
            k++;
        }
    }
    //baixo da direita superior
    j = ordem - 8;
    k = 7;
    while (j < ordem) {
        qrcode.QRImagem.mat[i * ordem + j] = str[k];
        k++;
    }
    //lateral esquerda inferior
    i = ordem - 1;
    j = 8;
    k = 0;
    while (i >= ordem - 7) {
        qrcode.QRImagem.mat[i * ordem + j] = str[k];
        i--;
        k++;
    }
}

#endif //QRCODE_FORMATOEINFORMACAODAVERSAO_H
