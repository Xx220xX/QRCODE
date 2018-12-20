#ifndef QRCODE_MENUWINDONS_H
#define QRCODE_MENUWINDONS_H

#include <conio2.h>
#include <afxres.h>
#include "Object.h"

#define MENU_baixo 804
#define MENU_esquerda 754
#define MENU_direita 774
#define MENU_cima 724
#define MENU_esc 274
#define MENU_enter 13


void destacarAtual(int x0, int y0, char pString[][29], int atual, int numeroDeOp);

void mostraQR(int x0, int y0) {
    int i, j;
    for (i = 0; i < qrcode.QRImagem.m; i++) {
        for (j = 0; j < qrcode.QRImagem.n; ++j) {
            if (qrcode.QRImagem.mat[i * qrcode.QRImagem.n + j]) {
                textbackground(BLACK);
            } else {
                textbackground(WHITE);
            }
            gotoxy(x0 + j, y0 + i);
            printf(" ");
        }
    }
    
}

void apagaArquivos() {

}

int selecionar(int x0, int y0, char opcoes[][29], int numeroDeOp) {
    int i = 0;
    int c;
    gotoxy(x0, y0 + i * 2);
    textcolor(LIGHTGREEN);
    printf("___%s___", opcoes[i]);
    for (i = 1; i < numeroDeOp; ++i) {
        gotoxy(x0, y0 + i * 2);
        printf("%s", opcoes[i]);
    }
    for (i = 1;;) {
        if (kbhit()) {
            c = getch();
            printf("%d\n", c);
            switch (c) {
                case MENU_baixo:i = i + 1 < numeroDeOp ? i + 1 : 1;
                    break;
                case MENU_esc:return 0;
                case MENU_cima:i = i > 1 ? i - 1 : numeroDeOp - 1;
                    break;
                case MENU_enter:return i;
                default:gotoxy(x0, y0 + numeroDeOp + 3);
                    textcolor(LIGHTRED);
                    printf("use as setas");
                    Sleep(500);
                    gotoxy(x0, y0 + numeroDeOp + 3);
                    textcolor(WHITE);
                    printf("               ");
            }
            destacarAtual(x0, y0, opcoes, i, numeroDeOp);
        }
    }
    return 0;
}

void destacarAtual(int x0, int y0, char pString[][29], int atual, int numeroDeOp) {
    int i = 0;
    gotoxy(x0, y0 + i * 2);
    textcolor(LIGHTGREEN);
    printf("___%s___", pString[i]);
    textcolor(WHITE);
    for (i = 1; i < numeroDeOp; ++i) {
        gotoxy(x0, y0 + i * 2);
        printf("                                        ");
        if (i == atual) {
            textcolor(LIGHTBLUE);
            printf("-->%s", pString[i]);
            textcolor(WHITE);
        }
    }
}

void pegarMsg(char *vet, int x0, int y0) {
    gotoxy(x0, y0);
    fgets(vet, 128, stdin);
}

void qrConfig() {
    system("cls");
    char opcoes[7][29] = {"qrConfig Modo de correcao", "L-LOWER", "M-Medium", "Q-quality", "H-High", "Automatico(Recomendado)", "SAIR"};
    int escolha;
    char vet[128] = {0};
    for (;;) {
        escolha = selecionar(15, 1, opcoes, 6);
        switch (escolha) {
            case 0:return;
            case 1:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_L;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                break;
            case 2:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_M;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                break;
            case 3:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_Q;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                break;
            case 4:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                break;
            case 5:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 1;
                break;
            case 6:return;;
            default:break;
            
        }
    }
}
void menu() {
    char opcoes[6][29] = {"MENU", "ESCREVER UMA MENSAGEM", "GERAR QR", "MUDAR PROPRIEDADES DO QRCODE", "APAGAR TODAS IMAGENS", "SAIR"};
    int escolha;
    char vet[128] = {0};
    for (;;) {
        escolha = selecionar(15, 1, opcoes, 6);
        switch (escolha) {
            case 0:return;
            case 1:pegarMsg(vet, 10, 10);
                break;
            case 2:gerarQR(vet);
                break;
            case 3:qrConfig();
                break;
            case 4:apagaArquivos();
                break;
            case 5:return;
            default:break;
            
        }
    }
}

#endif //QRCODE_MENUWINDONS_H
