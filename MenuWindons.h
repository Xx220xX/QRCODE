#ifndef QRCODE_MENUWINDONS_H
#define QRCODE_MENUWINDONS_H

#include <conio2.h>
#include <afxres.h>
#include <ctype.h>
#include "Object.h"

#define MENU_baixo 804
#define MENU_esquerda 754
#define MENU_direita 774
#define MENU_cima 'w'
#define MENU_esc 's'
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
    textbackground(BLACK);
    system("pause");
    
}

void apagaArquivos() {
    qrcode.config.numeroDoUltimoArquivo = 0;
    system("del *.pbm");
}

int selecionar(int x0, int y0, char opcoes[][29], int numeroDeOp) {
    int i = 0;
    int c;
    gotoxy(x0, y0 + i * 2);
    textcolor(LIGHTGREEN);
    printf("___%s___", opcoes[i]);
    textcolor(WHITE);
    destacarAtual(x0, y0, opcoes, i, numeroDeOp);
    for (i = 1; i < numeroDeOp; ++i) {
        gotoxy(x0, y0 + i * 2);
        printf("[%d]%s", i, opcoes[i]);
    }
    for (i = 1;;) {
        if (kbhit()) {
            c = getch();
    
    
            if (isalnum(c)) {
                if (c - '0' >= 1 && c - '0' < numeroDeOp) {
                    i = c - '0';
                }
                destacarAtual(x0, y0, opcoes, i, numeroDeOp);
            } else if (c == '\n' || c == 13) {
                return i;
            }
        }
        c = 0;
    }
    return 0;
}

void destacarAtual(int x0, int y0, char pString[][29], int atual, int numeroDeOp) {
    int i = 0;
    gotoxy(x0, y0 + i * 2);
    printf("                                  ");
    gotoxy(x0, y0 + i * 2);
    textcolor(LIGHTGREEN);
    printf("___%s___", pString[i]);
    textcolor(WHITE);
    for (i = 1; i < numeroDeOp; ++i) {
        gotoxy(x0, y0 + i * 2);
        printf("                                        ");
        gotoxy(x0, y0 + i * 2);
        if (i == atual) {
            textcolor(LIGHTBLUE);
            printf("-->[%d]%s", i, pString[i]);
            textcolor(WHITE);
        } else {
            printf("[%d]%s", i, pString[i]);
        }
    }
}

void verificaErro(int x0, int y0) {
    if (qrcode.error < 0) {
        gotoxy(x0, y0 + 1);
        if (qrcode.error == EXCEPTION_LENGTH_UNSUPPORTED) {
            printf("\n\nERROR: %s", "EXCEPTION_LENGTH_UNSUPPORTED(),Programa nao suporta tamanho da msg");
            if (!qrcode.config.MODE_CORRECAO_AUTOMATICO) {
                gotoxy(x0, y0 + 1);
                printf("tente com um nivel menor de correcao :D");
            } else {
                qrcode.config.temmsg = 0;
            }
        } else if (qrcode.error == EXCEPTION_BUG_IN_CHOSEN_VERSION) {
            printf("\n\nERROR: %s", "EXCEPTION_BUG_IN_CHOSEN_VERSION");
        } else if (qrcode.error == ArrayIndexOutOfBoundsException) {
            printf("\n\nERROR: %s", "ArrayIndexOutOfBoundsException()");
        } else if (qrcode.error == NULLPoiterException) {
            printf("\n\nERROR: %s", "NULLPoiterException(), sua msg esta nula \\('-')/ poh");
        } else {
            printf("\n\nERROR: %s", "UnknownException()");
        }
        Sleep(1500);
        return;
    }
    qrcode.config.numeroDoUltimoArquivo++;
    mostraQR(30, 10);
}

void pegarMsg(char *vet, int x0, int y0) {
    gotoxy(x0, y0);
    fgets(vet, 128, stdin);
}

void qrConfig() {
    system("cls");
    char opcoes[7][29] = {"qrConfig Modo de correcao", "L-LOWER", "M-Medium", "Q-quality", "H-High", "Automatico(Recomendado)", "SAIR"};
    int escolha;
    for (;;) {
        escolha = selecionar(15, 1, opcoes, 6);
        switch (escolha) {
            case 0:return;
            case 1:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_L;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                return;
            
            case 2:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_M;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                return;
            
            case 3:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_Q;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                return;
            case 4:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 0;
                return;
            case 5:qrcode.tabela.nivelCorrecaoErro = CORRECAO_MODO_H;
                qrcode.config.MODE_CORRECAO_AUTOMATICO = 1;
                return;
            case 6:return;
            default:break;
            
        }
    }
}

void printaInfo(int x0, int y0) {
    gotoxy(x0, y0);
    printf("                              ");
    gotoxy(x0, y0);
    if (qrcode.config.MODE_CORRECAO_AUTOMATICO)
        printf("NIVEL DE CORRECAO : Auto");
    else
        printf("NIVEL DE CORRECAO : %c", qrcode.tabela.nivelCorrecaoErro);
}

void menu() {
    char opcoes[6][29] = {"MENU ", "ESCREVER UMA MENSAGEM:", "GERAR QR", "MUDAR PROPRIEDADES DO QRCODE", "APAGAR TODAS IMAGENS", "SAIR"};
    textcolor(WHITE);
    int escolha;
    char vet[128] = {0};
    destacarAtual(5, 1, opcoes, 1, 6);
    for (;;) {
        printaInfo(5, 30);
        escolha = selecionar(5, 1, opcoes, 6);
        switch (escolha) {
            case 0:return;
            case 1:pegarMsg(vet, 35, 3);
                break;
            case 2:gerarQR(vet);
                verificaErro(10, 17);
                break;
            case 3:qrConfig();
                break;
            case 4:apagaArquivos();
                break;
            case 5:return;
            default:break;
        }
        system("cls");
    }
}

#endif //QRCODE_MENUWINDONS_H
