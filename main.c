#include<stdio.h>
#include<locale.h>
#include"Object.h"
#include "CODIFIC.h"
#include "CORRECAO_DE_ERROS.h"
#include<stdlib.h>


int main() {
    setlocale(LC_ALL, "pt-br");
    fclose(fopen("debug.txt", "w"));
    char vet[] = "8675309";
    qrcode.mensagemAserCriptografada = vet;
    qrcode.MODE_CORRECAO_AUTOMATICO = 0;
    qrcode.MODE_correcaoDeErro = CORRECAO_MODO_M;
    CODF_ALL_STEPS();
    CORREC_ETAPA8();

    CORREC_CORRIGIR();
    freeqr();
    printf("\nfim");
    return 0;
}
