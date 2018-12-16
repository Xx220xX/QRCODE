#ifndef QRCODE_CORRECAO_DE_ERROS_H_H
#define QRCODE_CORRECAO_DE_ERROS_H_H

#include <stdio.h>
#include "Object.h"

void shortValueOf(char *str_init, char *str_intervalo_fim, char *str_final_maximo, unsigned short *n) {
    if (str_init < str_final_maximo && str_init < str_intervalo_fim) {
        if (*str_init >= '0' && *str_init <= '9')
            *n = *n * 10 + ((*str_init - '0'));
        shortValueOf((str_init + 1), str_intervalo_fim, str_final_maximo, n);
    }
}

void CORREC_ETAPA8() {
    if (qrcode.error < 0)
        return;
    //converter a strbits em decimal
    unsigned short *dec = 0;
    int bytes = 0, i;
    qrcode.tamanhoDaStrbits /= 8;
    printf("ola\n");
    while (bytes < qrcode.tamanhoDaStrbits) {
        dec = realloc(dec, bytes + 1);
        shortValueOf(
                qrcode.strbits + (bytes * 8),
                qrcode.strbits + ((1 + bytes) * 8), qrcode.strbits + qrcode.tamanhoDaStrbits * 8 + 1, dec + bytes);
        bytes++;
    }
    for (i = 0; i < bytes; ++i) {
        printf("%d ", dec[i]);
    }
    free(dec);
}

#endif //QRCODE_CORRECAO_DE_ERROS_H_H
