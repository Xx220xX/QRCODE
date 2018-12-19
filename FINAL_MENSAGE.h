//
// Created by MORADIA082663 on 19/12/2018.
//

#ifndef QRCODE_FINAL_MENSAGE_H
#define QRCODE_FINAL_MENSAGE_H

#include "Object.h"

void FINAL_ETAPA1() {
    ERROR();
    int i, j;
    //unir na strbits msg + corretor
    j = 0;
    LOG("\n_________________________________________________________________________________________\n");
    LOG("ESTRUTURA DA MENSAGEM{\n  ETAPA 1:\n    STR Value FINAL:\n      ");
    logFile = fopen("debug.txt", "a");
    for (i = 0; i < qrcode.tamanhoDa_msgNumbers; i++) {
        qrcode.strbits = realloc(qrcode.strbits, (i * 8 + 9));
        fprintf(logFile, "%d ", (unsigned char) qrcode.msgNumbers[j]);
        converterParaBinario(qrcode.strbits + (i * 8), qrcode.msgNumbers[j++], 8);
    }
    j = 0;
    for (i = 0; i < qrcode.tamanhoDosCodigosCorretores; i++) {
        qrcode.strbits = realloc(qrcode.strbits, (i * 8 + 9));
        fprintf(logFile, "%d ", (unsigned char) qrcode.codigosCorretores[j]);
        converterParaBinario(qrcode.strbits + (i * 8), qrcode.codigosCorretores[j++], 8);
    }
    qrcode.strbits = realloc(qrcode.strbits, (i * 8 + 1 + qrcode.tabela.bitsdeRemanescenteRequeridos));
    converterParaBinario((qrcode.strbits + (i * 8)), 0, qrcode.tabela.bitsdeRemanescenteRequeridos);
    fprintf(logFile, "\n    STR bits FINAL+bits remanecentes:\n      ");
    qrcode.tamanhoDaStrbits = i * 8 + qrcode.tabela.bitsdeRemanescenteRequeridos;
    printa8Bits(logFile, qrcode.strbits, qrcode.tamanhoDaStrbits);
    fclose(logFile);
}

#endif //QRCODE_FINAL_MENSAGE_H
