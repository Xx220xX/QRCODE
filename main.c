#include<stdio.h>
#include<locale.h>
#include"Object.h"
#include "CODIFIC.h"
#include "CORRECAO_DE_ERROS.h"
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
    CODF_ALL_STEPS();
    //CORREC_ETAPA8();
    freeqr();
    printf("\nfim");
return 0;
}
