#include<stdio.h>
#include<locale.h>
#include"Object.h"
#include "CODIFIC.h"
#include "CORRECAO_DE_ERROS.h"
#include "FINAL_MENSAGE.h"
#include "PosicionamentodeModuloemMatriz.h"
#include<stdlib.h>

#define tamanho 128

int main() {
    qrcode.tabela.version = 3;
    Posicionar_ETAPA1();
    Posicionar_ETAPA2();
    Posicionar_ETAPA3();
    Posicionar_ETAPA4();
    return 0;
    system("chcp 1252");
    system("cls");
    setlocale(LC_ALL, "Portuguese");
    fclose(fopen("debug.txt", "w"));
    char vet[tamanho] = "á";
    fflush(stdin);
    fgets(vet, tamanho, stdin);
    printf("%s", vet);
    int i = 0;
    for (; vet[i]; i++) {
        if (vet[i] == '\n') {
            vet[i] = 0;
            break;
        }
    }
    qrcode.mensagemAserCriptografada = vet;
    qrcode.MODE_CORRECAO_AUTOMATICO = 1;
    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
    CODF_ALL_STEPS();
    CORREC_ALL();
    FINAL_ETAPA1();
    system("start debug.txt");
    freeqr();
    
    printf("\nfim");
    return 0;
}
