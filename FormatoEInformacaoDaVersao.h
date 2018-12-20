#ifndef QRCODE_FORMATOEINFORMACAODAVERSAO_H
#define QRCODE_FORMATOEINFORMACAODAVERSAO_H

#include "Object.h"

void TABELAMASK(int *str_result, int nivel_de_correcao, int vL, int vM, int vQ, int vH) {
    LOG("\nescolhendo o nivem para : %d %c\n   ", nivel_de_correcao, nivel_de_correcao);
    if (nivel_de_correcao == CORRECAO_MODO_L) {
        *str_result = vL;
    } else if (nivel_de_correcao == CORRECAO_MODO_M) {
        *str_result = vM;
    } else if (nivel_de_correcao == CORRECAO_MODO_Q) {
        *str_result = vQ;
    } else if (nivel_de_correcao == CORRECAO_MODO_H) {
        *str_result = vH;
    }
    LOG("\n  codigo = %d\n", *str_result);
}

void string_format(char str[16], unsigned int numero_mascara) {
    /* unsigned char *codStringFormat;
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
      */
    int codStringFormat = 0;
    int m = qrcode.tabela.nivelCorrecaoErro;
    int n = qrcode.tabela.maskara;
    switch (n) {
        case 0:TABELAMASK(&codStringFormat, m, 30660, 21522, 13663, 5769);
            break;
        case 1:TABELAMASK(&codStringFormat, m, 29427, 20773, 12392, 5054);
            break;
        case 2:TABELAMASK(&codStringFormat, m, 32170, 24188, 16177, 7399);
            break;
        case 3:TABELAMASK(&codStringFormat, m, 30877, 23371, 14854, 6608);
            break;
        case 4:TABELAMASK(&codStringFormat, m, 26159, 17913, 9396, 1890);
            break;
        case 5:TABELAMASK(&codStringFormat, m, 25368, 16590, 8579, 597);
            break;
        case 6:TABELAMASK(&codStringFormat, m, 27713, 20375, 11994, 3340);
            break;
        case 7:TABELAMASK(&codStringFormat, m, 26998, 19104, 11245, 2107);
            break;
        default:break;
    }
    converterParaBinario(str, codStringFormat, 15);
    
    LOG("\n  STR = %s\n", str);
    
}

void insere_string_format_ETAPA_1() {
    LOG("\ninserir str FORMAT\n      nivel de correcao = %c , versao %d\n         ", qrcode.tabela.nivelCorrecaoErro, qrcode.tabela.version);
    
    int i = 0, j = 8, k = 14;
    int ordem = qrcode.QRImagem.m;
    char str[25] = {0};
    string_format(str, qrcode.tabela.maskara);
    LOG("\nstrFormat : %s\n\n", str);
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
        j++;
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
