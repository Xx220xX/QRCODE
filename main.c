#include<stdio.h>
#include<locale.h>
#include"Object.h"
#include "CODIFIC.h"
#include "CORRECAO_DE_ERROS.h"
#include "FINAL_MENSAGE.h"
#include "PosicionamentodeModuloemMatriz.h"
#include "Maskramento.h"
#include "FormatoEInformacaoDaVersao.h"
#include "MenuWindons.h"
#include<stdlib.h>

void gerarQR(char *vet) {
    int i = 0;
    for (; vet[i]; i++) {
        if (vet[i] == '\n') {
            vet[i] = 0;
            break;
        }
    }
    qrcode.config.temmsg = vet[0] != 0;
    
    if (!qrcode.config.temmsg) {
        qrcode.error = NULLPoiterException;
        return;
    }
    qrcode.mensagemAserCriptografada = vet;
    CODF_ALL_STEPS();
    CORREC_ALL();
    FINAL_ETAPA1();
    Posicionar_AllSTeps();
    MASK_ETAPA_MASCARAR();
    insere_string_format_ETAPA_1();
    printaQRIMG(qrcode.QRImagem, qrcode.config.numeroDoUltimoArquivo, 1);
    
}


int main() {
    FILE *file;
    system("chcp 1252");
    system("cls");
    qrcode.mensagemAserCriptografada = 0;
    qrcode.config.MODE_CORRECAO_AUTOMATICO = 1;
    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
    file = fopen("qr.config", "rb");
    fread(&qrcode.config.numeroDoUltimoArquivo, 1, sizeof(unsigned int), file);
    fclose(file);
    setlocale(LC_ALL, "Portuguese");
    fclose(fopen("debug.txt", "w"));
    menu();
    //gerarQR("ola");
    freeqr();
    printf("\nfim");
    return 0;
}
