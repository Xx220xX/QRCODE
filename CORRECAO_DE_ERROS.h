#ifndef QRCODE_CORRECAO_DE_ERROS_H_H
#define QRCODE_CORRECAO_DE_ERROS_H_H

#include <stdio.h>
#include "Object.h"

void imprimeVetor(unsigned char v[], int N);


void CORREC_ETAPA1() {
    ERROR();
    //Quebrar palavras-código de dados em blocos, se necessário
    LOG("ETAPA 1: pegar dados da tabela:\n");
    COMPARE_MODO_CORRECAO(qrcode.tabela.qtBlocosGrupo_2, qrcode.tabela.nivelCorrecaoErro, 0, 0, 0, 0);
    COMPARE_MODO_CORRECAO(qrcode.tabela.qtDePalavrasCodigo_Grupo_2, qrcode.tabela.nivelCorrecaoErro, 0, 0, 0, 0);
    switch (qrcode.tabela.version) {
        case 1:COMPARE_MODO_CORRECAO(qrcode.tabela.qtBlocosGrupo_1, qrcode.tabela.nivelCorrecaoErro, 1, 1, 1, 1);
            COMPARE_MODO_CORRECAO(qrcode.tabela.qtDePalavrasCodigo_Grupo_1, qrcode.tabela.nivelCorrecaoErro, 19, 16, 13, 9);
            break;
        case 2:COMPARE_MODO_CORRECAO(qrcode.tabela.qtBlocosGrupo_1, qrcode.tabela.nivelCorrecaoErro, 1, 1, 1, 1);
            COMPARE_MODO_CORRECAO(qrcode.tabela.qtDePalavrasCodigo_Grupo_1, qrcode.tabela.nivelCorrecaoErro, 34, 28, 22, 16);
            break;
        case 3:COMPARE_MODO_CORRECAO(qrcode.tabela.qtBlocosGrupo_1, qrcode.tabela.nivelCorrecaoErro, 1, 1, 2, 2);
            COMPARE_MODO_CORRECAO(qrcode.tabela.qtDePalavrasCodigo_Grupo_1, qrcode.tabela.nivelCorrecaoErro, 55, 44, 17, 13);
            break;
        default:qrcode.error = EXCEPTION_BUG_IN_CHOSEN_VERSION;
            break;
    }
    LOG("    BLOCLOS -> Gp1: %d , Gp2: %d\n    Palavras em cada bloco ->Gp1 :%d ,Gp2 :%d\n\n", qrcode.tabela.qtBlocosGrupo_1, qrcode.tabela.qtBlocosGrupo_2, qrcode.tabela.qtDePalavrasCodigo_Grupo_1, qrcode.tabela.qtDePalavrasCodigo_Grupo_2);
}

void CORREC_ETAPA8() {
    ERROR();
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
    switch (qrcode.tabela.version) {
        case 1:COMPARE_MODO_CORRECAO(qrcode.tabela.bytesCorretoresPorBloco, qrcode.tabela.nivelCorrecaoErro, 7, 10, 13, 17);
            break;
        case 2:COMPARE_MODO_CORRECAO(qrcode.tabela.bytesCorretoresPorBloco, qrcode.tabela.nivelCorrecaoErro, 10, 16, 22, 28);
            break;
        case 3:COMPARE_MODO_CORRECAO(qrcode.tabela.bytesCorretoresPorBloco, qrcode.tabela.nivelCorrecaoErro, 15, 26, 18, 22);
            break;
        default:break;
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
    ERROR();
    unsigned char *codigo, *codigo_aux;
    unsigned short *aux_paraIntercalar;
    int i, j, k = 0;
    if (qrcode.tabela.qtBlocosGrupo_1 == 1) {
        codigo = CodigosCorretores(qrcode.msgNumbers, qrcode.tamanhoDa_msgNumbers, qrcode.tabela.bytesCorretoresPorBloco);
        LOG("\ncodigos corretores : ");
        imprimeVetor(codigo, qrcode.tabela.bytesCorretoresPorBloco);
    } else if (qrcode.tabela.qtBlocosGrupo_1 == 2) {
        aux_paraIntercalar = (unsigned short *) calloc(qrcode.tamanhoDa_msgNumbers, sizeof(unsigned short));
        for (i = 0, j = qrcode.tamanhoDa_msgNumbers / 2; i < qrcode.tamanhoDa_msgNumbers / 2;) {
            aux_paraIntercalar[k++] = qrcode.msgNumbers[i++];
            aux_paraIntercalar[k++] = qrcode.msgNumbers[j++];
        }
        free(qrcode.msgNumbers);
        qrcode.msgNumbers = aux_paraIntercalar;
        LOG("\n    INTERCALADA :\n    ");
        logFile = fopen("debug.txt", "a");
        for (i = 0; i < qrcode.tamanhoDa_msgNumbers; ++i) {
            fprintf(logFile, "%d ", qrcode.msgNumbers[i]);
        }
        
        fclose(logFile);
        
        codigo = CodigosCorretores(qrcode.msgNumbers,
                                   qrcode.tamanhoDa_msgNumbers / 2, qrcode.tabela.bytesCorretoresPorBloco);
        codigo_aux = CodigosCorretores(
                qrcode.msgNumbers + qrcode.tabela.bytesCorretoresPorBloco,
                qrcode.tamanhoDa_msgNumbers / 2, qrcode.tabela.bytesCorretoresPorBloco);
        codigo = realloc(codigo, qrcode.tabela.bytesCorretoresPorBloco * 2);
        for (i = qrcode.tabela.bytesCorretoresPorBloco, j = 0; j < qrcode.tabela.bytesCorretoresPorBloco; j++, i++) {
            codigo[i] = codigo_aux[j];
        }
        free(codigo_aux);
        LOG("\ncodigos corretores : ", codigo);
        imprimeVetor(codigo, qrcode.tabela.bytesCorretoresPorBloco * 2);
    }
    qrcode.codigosCorretores = codigo;

}

// Programa que mostra exemplo de como utilizar a biblioteca QRCode.h para determinar os Error Correction Codewords



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
    
    // As 4 linhas seguintes libera a mem?ria alocada dinamicamente pela fun??o de c?lculos dos c?digos corretores
    free(cod1);
    free(cod2);
    free(cod3);
    free(codStringFormat);
    
    return 0;
}

void imprimeVetor(unsigned char v[], int N) {
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
