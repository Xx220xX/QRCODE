#include<stdio.h>
#include<locale.h>
#include"Object.h"
#include "CODIFIC.h"
#include<stdlib.h>

void printa(char *str) {
    int i, j, k = 0;
    for (i = 0; str[k]; ++i) {
        for (j = 0; str[k] && j < 8; j++) {
            printf("%c", str[k++]);
        }
        printf(" ");
    }
}
int main(){
    setlocale(LC_ALL,"pt-br");
    fclose(fopen("debug.txt","w"));
    char vet[] = "8";
    qrcode.mensagemAserCriptografada = vet;
    qrcode.MODE_CORRECAO_AUTOMATICO = 1;
    qrcode.MODE_correcaoDeErro = CORRECAO_MODO_H;
    CODF_ETAPA1();
    CODF_ETAPA2();
    CODF_ETAPA3();
    CODF_ETAPA4();
    CODF_ETAPA5();
    CODF_ETAPA6();
    printa(qrcode.strbits);
    freeqr();
    printf("\nfim");
return 0;
}
