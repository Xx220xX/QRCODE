#ifndef QRCODE_CORRECAO_DE_ERROS_H_H
#define QRCODE_CORRECAO_DE_ERROS_H_H

#include <stdio.h>
#include "Object.h"

void printaVetUChar(unsigned char *v, int N);

void printaUnsignedSHORT(unsigned short *numbers, int tamanho) {
    int i;
    logFile = fopen("debug.txt", "a");
    for (i = 0; i < tamanho; ++i) {
        fprintf(logFile, "%d ", numbers[i]);
    }
    fclose(logFile);
}

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
                qrcode.strbits + (bytes * 8), qrcode.strbits + ((1 + bytes) * 8), qrcode.strbits + qrcode.tamanhoDaStrbits * 8);
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
    LOG("CORRECAO_ETAPA8\n   tamanhoDa_msgNumbers: %d\n   numero de bytesCorretoresPorBloco %d\n\n str bits agr : \n     ", bytes, qrcode.tabela.bytesCorretoresPorBloco);
    logFile = fopen("debug.txt", "a");
    printa8Bits(logFile, qrcode.strbits, qrcode.tamanhoDaStrbits);
    fprintf(logFile, "\n\n    msg Numbers: \n     ");
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
        qrcode.tamanhoDosCodigosCorretores = qrcode.tabela.bytesCorretoresPorBloco;
        codigo = CodigosCorretores(qrcode.msgNumbers, qrcode.tamanhoDa_msgNumbers, qrcode.tabela.bytesCorretoresPorBloco);
        LOG("\n\n\n______codigos corretores______ :\n       ");
        printaVetUChar(codigo, qrcode.tabela.bytesCorretoresPorBloco);
    } else if (qrcode.tabela.qtBlocosGrupo_1 == 2) {
        qrcode.tamanhoDosCodigosCorretores = qrcode.tabela.bytesCorretoresPorBloco * 2;
        codigo = CodigosCorretores(qrcode.msgNumbers, (qrcode.tamanhoDa_msgNumbers / 2), qrcode.tabela.bytesCorretoresPorBloco);
        codigo_aux = CodigosCorretores(qrcode.msgNumbers + (qrcode.tamanhoDa_msgNumbers / 2), (qrcode.tamanhoDa_msgNumbers / 2), qrcode.tabela.bytesCorretoresPorBloco);
    
        /*** INTERCALAR ***/
        aux_paraIntercalar = (unsigned short *) calloc(qrcode.tamanhoDa_msgNumbers, sizeof(unsigned short));
        for (i = 0, j = qrcode.tamanhoDa_msgNumbers / 2; i < qrcode.tamanhoDa_msgNumbers / 2; i++, j++) {
            aux_paraIntercalar[k] = qrcode.msgNumbers[i];
            aux_paraIntercalar[k + 1] = qrcode.msgNumbers[j];
            k += 2;
        }
        LOG("\n\n    msg INTERCALADA :\n    ");
        printaUnsignedSHORT(aux_paraIntercalar, qrcode.tamanhoDa_msgNumbers);
        fprintf(logFile, "    fim da intercalada\n\n");
    
        /*** codigo corretores 1*/
        LOG("\n______________ BLOCO 1:\n         msgNumbers bloco 1\n                   ");
        printaUnsignedSHORT(qrcode.msgNumbers, (qrcode.tamanhoDa_msgNumbers / 2));
    
        LOG("\n                    codigos corretores : \n                   ");
        printaVetUChar(codigo, qrcode.tabela.bytesCorretoresPorBloco);
        /*** codigo corretores 2*/
        LOG("\n______________ BLOCO 2:\n         msgNumbers bloco 2\n                   ");
        printaUnsignedSHORT(qrcode.msgNumbers + (qrcode.tamanhoDa_msgNumbers / 2), qrcode.tamanhoDa_msgNumbers / 2);
    
        LOG("\n                    codigos corretores : \n                   ");
        printaVetUChar(codigo_aux, qrcode.tabela.bytesCorretoresPorBloco);
        for (i = 0, k = 0, j = 0; i < qrcode.tabela.bytesCorretoresPorBloco; i++, j++) {
            qrcode.codigosCorretores = (char *) realloc(qrcode.codigosCorretores, k + 2);
            qrcode.codigosCorretores[k++] = codigo[i];
            qrcode.codigosCorretores[k++] = codigo_aux[j];
        }
        qrcode.codigosCorretores = (char *) realloc(qrcode.codigosCorretores, k + 1);
        qrcode.codigosCorretores[k] = 0;
    
        LOG("\n\n   corretores  INTERCALADos :\n    ");
        printaVetUChar(qrcode.codigosCorretores, qrcode.tamanhoDosCodigosCorretores);
        qrcode.msgNumbers = aux_paraIntercalar;
        free(codigo);
        codigo = qrcode.codigosCorretores;
        free(codigo_aux);
    }
    qrcode.codigosCorretores = codigo;
    
}


void printaVetUChar(unsigned char *v, int N) {
    unsigned short i;
    logFile = fopen("debug.txt", "a");
    for (i = 0; i < N; i++) {
        fprintf(logFile, "%d ", v[i]);
    }
    fprintf(logFile, "\n");
    fclose(logFile);
}


#endif //QRCODE_CORRECAO_DE_ERROS_H_H
