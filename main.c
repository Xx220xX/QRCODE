#include<stdio.h>
#include<locale.h>
#include"Object.h"
#include "CODIFIC.h"
#include<stdlib.h>

int main(){
    setlocale(LC_ALL,"pt-br");
    fclose(fopen("debug.txt","w"));
    char vet[] = "8675309";
    qrcode.mensagemAserCriptografada = vet;
    qrcode.MODE_CORRECAO_AUTOMATICO = 1;
    qrcode.MODE_correcaoDeErro = CORRECAO_MODO_H;
    CODF_ETAPA1();
    CODF_ETAPA2();
    CODF_ETAPA3();
    CODF_ETAPA4();
    CODF_ETAPA5();
    freeqr();
    printf("fim");
return 0;
}
