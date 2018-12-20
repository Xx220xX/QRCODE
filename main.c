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

#define tamanho 128

int main() {
    system("chcp 1252");
    system("cls");
    //menu();
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
    qrcode.MODE_CORRECAO_AUTOMATICO = 0;
    qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_Q;
    CODF_ALL_STEPS();
    CORREC_ALL();
    FINAL_ETAPA1();
    Posicionar_AllSTeps();
    MASK_ETAPA_MASCARAR();
    insere_string_format_ETAPA_1();
    //system("start debug.txt");
    freeqr();
    printaERRO();
    printf("\nfim");
    return 0;
}
