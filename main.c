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
    qrcode.config.temmsg = vet[0];
    if (!qrcode.config.temmsg) {
        qrcode.error = NULLPoiterException;
    }
    CODF_ALL_STEPS();
    CORREC_ALL();
    FINAL_ETAPA1();
    Posicionar_AllSTeps();
    MASK_ETAPA_MASCARAR();
    insere_string_format_ETAPA_1();
    printaQRIMG(qrcode.QRImagem, qrcode.config.numeroDoUltimoArquivo, 1);
}
#define tamanho 128

int main() {
    qrcode.mensagemAserCriptografada = 0;
    qrcode.config.MODE_CORRECAO_AUTOMATICO = 1;
    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
    system("chcp 1252");
    system("cls");
    menu();
    setlocale(LC_ALL, "Portuguese");
    fclose(fopen("debug.txt", "w"));
    char vet[tamanho] = "á";
    fflush(stdin);
    // fgets(vet, tamanho, stdin);
    
    // gerarQR(vet);
    
    
    freeqr();
    printaERRO();
    printf("\nfim");
    return 0;
}
