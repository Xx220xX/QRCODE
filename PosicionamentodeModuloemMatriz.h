#ifndef QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
#define QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
#define separadores  1
#define espacoReservado 4
#define fixosPretos 3
#define fixosBrancos 2

void fazerQuadrado(int i0, int j0, int tamanhoI, int tamanhoJ, char *mat, int m, int n, char value) {
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

void printMatchar(char *mat, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            if (mat[i * n + j] == 0) {
                printf("  ");
            } else
                printf("%d ", mat[i * n + j]);
        }
        printf("\n");
    }
}

void Posicionar_ETAPA1() {
    ERROR();
    int m = 24, n;
    m += (qrcode.tabela.version - 1) * 4;
    n = m;
    char *mat = calloc(m * n, sizeof(char));
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
    printMatchar(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    
}

void Posicionar_ETAPA3() {

}

void Posicionar_ETAPA5() {
    //4 -> espaçoReservado
    int i = 8;
    int ordem = qrcode.QRImagem.m;
    //lateral da querda superior
    while (i <= ordem * 8 + 8) {
        qrcode.QRImagem.mat[i] = espacoReservado;
        if (i = ordem * 5 + 8) {
            i = i + 2 * ordem;
        } else
            i += ordem;
    }
    //baixo da esquerda superior
    i = ordem * 8;
    while (i <= ordem * 8 + 8) {
        qrcode.QRImagem.mat[i] = espacoReservado;
        if (i = ordem * 8 + 5) {
            i = i + 2;
        } else
            i++;
    }
    //baixo da direita superior
    i = i + ordem - 16;
    while (i <= 9 * ordem - 1) {
        qrcode.QRImagem.mat[i] = espacoReservado;
        i++;
    }
    //lateral esquerda inferior
    i = ordem * (ordem - 1) + 8;
    while (i >= (ordem * (ordem - 7) + 8)) {
        qrcode.QRImagem.mat[i] = espacoReservado;
        i = i - ordem;
    }
    qrcode.QRImagem.mat[i] = 3; //modulo preto
}

#endif //QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
