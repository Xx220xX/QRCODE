#ifndef QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
#define QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
#define separadores  4
#define espacoReservado 9
#define fixosPretos 3
#define fixosBrancos 6
#define fixosPretosTemporal 5
#define fixosBrancosTemporal 2
#define testeERROR()\
    if(i * ordem + j<0 || i * ordem + j>=ordem*ordem){\
        qrcode.error=ArrayIndexOutOfBoundsException;\
        LOG("\n  i = %d, j =  %d \n",i,j);\
        return;\
    }

void fazerQuadrado(int i0, int j0, int tamanhoI, int tamanhoJ, int *mat, int m, int n, char value) {
    int i, j;
    if (mat == 0) {
        qrcode.error = NULLPoiterException;
        return;
    }
    
    for (i = i0; i < tamanhoI + i0; ++i) {
        
        if (i >= 0 && i < m && j0 >= 0 && j0 < n) {
            mat[i * n + j0] = value;
        }
        if ((j0 + tamanhoJ - 1) >= 0 && (j0 + tamanhoJ - 1) < n && i >= 0 && i < m) {
            mat[i * n + (j0 + tamanhoJ - 1)] = value;
        }
    }
    for (j = j0; j < tamanhoJ + j0; ++j) {
        if (j >= 0 && j < n && i0 >= 0 && i0 < m) {
            mat[i0 * n + j] = value;
        }
        if ((i0 + tamanhoI - 1) >= 0 && (i0 + tamanhoI - 1) < m && j >= 0 && j < n) {
            mat[(i0 + tamanhoI - 1) * n + j] = value;
        }
    }
}

void printMatchar(int *mat, int m, int n) {
    int i, j;
    logFile = fopen("debug.txt", "a");
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            if (mat[i * n + j] == 0) {
                fprintf(logFile, "  ");
            } else
                fprintf(logFile, "%d ", mat[i * n + j]);
        }
        fprintf(logFile, "\n");
    }
    fclose(logFile);
}

void Posicionar_ETAPA1() {
    ERROR();
    int m = 21, n;
    m += (qrcode.tabela.version - 1) * 4;
    n = m;
    int *mat = (int *) calloc(m * n, sizeof(int));
    //externo preto 7x7
    fazerQuadrado(0, 0, 7, 7, mat, m, n, fixosPretos);
    fazerQuadrado(0, n - 7, 7, 7, mat, m, n, fixosPretos);
    fazerQuadrado(m - 7, 0, 7, 7, mat, m, n, fixosPretos);
    //interno branco 5x5
    fazerQuadrado(1, 1, 5, 5, mat, m, n, fixosBrancos);
    fazerQuadrado(1, n - 6, 5, 5, mat, m, n, fixosBrancos);
    fazerQuadrado(m - 6, 1, 5, 5, mat, m, n, fixosBrancos);
    //interno preto 3x3
    fazerQuadrado(2, 2, 3, 3, mat, m, n, fixosPretos);
    fazerQuadrado(2, n - 5, 3, 3, mat, m, n, fixosPretos);
    fazerQuadrado(m - 5, 2, 3, 3, mat, m, n, fixosPretos);
    //interno 1x1
    fazerQuadrado(3, 3, 1, 1, mat, m, n, fixosPretos);
    fazerQuadrado(3, n - 4, 1, 1, mat, m, n, fixosPretos);
    fazerQuadrado(m - 4, 3, 1, 1, mat, m, n, fixosPretos);
    
    //fazerQuadrado(qrcode.tabela.version*4+9, 8, 1, 1, mat, m, n, fixosPretos);
    
    qrcode.QRImagem.mat = mat;
    qrcode.QRImagem.m = m;
    qrcode.QRImagem.n = n;
}

void Posicionar_ETAPA2() {
    ERROR();
    //adicionar separadores
    fazerQuadrado(-1, -1, 9, 9, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, separadores);
    fazerQuadrado(-1, qrcode.QRImagem.n - 8, 9, 9, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, separadores);
    fazerQuadrado(qrcode.QRImagem.m - 8, -1, 9, 9, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, separadores);
    
}

void Posicionar_ETAPA3() {
//adicionar padroes de alinhamento
    ERROR();
    
    if (qrcode.tabela.version == 2) {
        fazerQuadrado(16, 16, 5, 5, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, fixosPretos);
        fazerQuadrado(17, 17, 3, 3, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, fixosBrancos);
        fazerQuadrado(18, 18, 1, 1, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, fixosPretos);
    } else if (qrcode.tabela.version == 3) {
        fazerQuadrado(20, 20, 5, 5, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, fixosPretos);
        fazerQuadrado(21, 21, 3, 3, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, fixosBrancos);
        fazerQuadrado(22, 22, 1, 1, qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n, fixosPretos);
    }
    
}

void Posicionar_ETAPA4() {
    ERROR();
    //padroes_tempo
    int i, j, ordem = qrcode.QRImagem.m;
    int add = 1; //alternar preto e branco
    //vertical
    for (i = 6, j = 6; i < ordem; i++) {
        if (!qrcode.QRImagem.mat[i * ordem + j]) {
            if (add) {
                qrcode.QRImagem.mat[i * ordem + j] = fixosPretosTemporal;
            } else {
                qrcode.QRImagem.mat[i * ordem + j] = fixosBrancosTemporal;
            }
            add = !add;
        }
    }//horizontal
    for (i = 6, j = 6, add = 1; j < ordem; j++) {
        if (!qrcode.QRImagem.mat[i * ordem + j]) {
            if (add) {
                qrcode.QRImagem.mat[i * ordem + j] = fixosPretos;
            } else {
                qrcode.QRImagem.mat[i * ordem + j] = fixosBrancos;
            }
            add = !add;
        }
    }
}

void Posicionar_ETAPA5() {
    
    int i = 0, j = 8;
    int ordem = qrcode.QRImagem.m;
    //lateral da querda superior
    while (i <= 8) {
        qrcode.QRImagem.mat[i * ordem + j] = espacoReservado;
        if (i == 5) {
            i = i + 2;
        } else
            i++;
    }
    //baixo da esquerda superior
    i = 8;
    j = 0;
    while (j <= 8) {
        qrcode.QRImagem.mat[i * ordem + j] = espacoReservado;
        if (j == 5) {
            j = j + 2;
        } else
            j++;
    }
    //baixo da direita superior
    j = ordem - 8;
    while (j < ordem) {
        qrcode.QRImagem.mat[i * ordem + j] = espacoReservado;
        j++;
    }
    //lateral esquerda inferior
    i = ordem - 1;
    j = 8;
    while (i >= ordem - 7) {
        qrcode.QRImagem.mat[i * ordem + j] = espacoReservado;
        i--;
    }
    qrcode.QRImagem.mat[i * ordem + j] = fixosPretos; //modulo preto
    
}

void Posicionar_ETAPA6() {
    ERROR();
    //colocar strbits na matriz
    int acrecimoDoI = -1;
    int i = qrcode.QRImagem.m - 1, j = i, k;
    int ordem = i + 1;
    for (k = 0; k < qrcode.tamanhoDaStrbits;) {
        testeERROR()
        //  printf("eae man k = %d de %d\n", k, qrcode.tamanhoDaStrbits);
        
        testeERROR()
        if (!qrcode.QRImagem.mat[i * ordem + j]) {
            qrcode.QRImagem.mat[i * ordem + j] = qrcode.strbits[k++];
        }
        j--;
        testeERROR()
        if (!qrcode.QRImagem.mat[i * ordem + j]) {
            qrcode.QRImagem.mat[i * ordem + j] = qrcode.strbits[k++];
        }
        i += acrecimoDoI;
        j++;
        if (i < 0) {
            acrecimoDoI = -acrecimoDoI;
            i = 0;
            j -= 2;
        } else if (i >= ordem) {
            acrecimoDoI = -acrecimoDoI;
            i = ordem - 1;
            j -= 2;
        }
    }
}

void Posicionar_AllSTeps() {
    ERROR();
    LOG("\n\n________________posicionando na matriz __________________\n\n   Etapa 1: \n     ");
    Posicionar_ETAPA1();
    LOG("Tamanho da matriz : %d\n\n   ####saida na ETAPA1\n", qrcode.QRImagem.m);
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    Posicionar_ETAPA2();
    LOG("\n\n   ####saida na Etapa2:\n");
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    Posicionar_ETAPA3();
    LOG("\n\n   ####saida na Etapa3:\n");
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    Posicionar_ETAPA4();
    LOG("\n\n   ####saida na Etapa4:\n");
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    Posicionar_ETAPA5();
    LOG("\n\n   ####saida na Etapa5:\n");
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    Posicionar_ETAPA6();
    LOG("\n\n   ####saida na Etapa6:\n");
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    LOG("\n\n   ####saida FINAL da posiconar Matriz:\n");
    
}
#endif //QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
