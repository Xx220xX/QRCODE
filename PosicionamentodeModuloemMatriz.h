#ifndef QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
#define QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H

void fazerQuadrado(int i0, int j0, int tamanhoI, int tamanhoJ, char *mat, int m, int n, char value) {
    int i, j;
    if(mat == 0){
        qrcode.error =NULLPoiterException;
        return;
    }
    
    for (i = i0; i < tamanhoI+i0; ++i) {
        if(i<0)continue;
        if(i>= m){
            qrcode.error = ArrayIndexOutOfBoundsException;
            return;
        }
        
        mat[i * n + j0] = value;
        mat[i * n + (j0 + tamanhoJ-1)] = value;
    }
    for (j = j0; j < tamanhoJ+j0; ++j) {
        if(j<0)continue;
        if(j>= n){
            qrcode.error = ArrayIndexOutOfBoundsException;
            return;
        }
        mat[i0 * n + j] = value;
        mat[(i0+tamanhoI-1) * n + j] = value;
    }
}

void printMatchar(char *mat, int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            if (mat[i*n+j] == 0){
                printf("  ");
            }else
            printf("%d ",mat[i*n+j]);
        }
        printf("\n");
    }
}

void Posicionar_ETAPA1() {
    int m=24,n;
    m += (qrcode.tabela.version-1)*4;
    n=m;
    char *mat =calloc(m*n, sizeof(char));
    fazerQuadrado(0,0,7,7,mat,m,n,3);
    fazerQuadrado(0,n-7,7,7,mat,m,n,3);
    fazerQuadrado(m-7,0,7,7,mat,m,n,3);
    fazerQuadrado(2,2,3,3,mat,m,n,1);
    fazerQuadrado(2,n-5,3,3,mat,m,n,1);
    fazerQuadrado(m-5,2,3,3,mat,m,n,1);
    printMatchar(mat,m,n);
    qrcode.QRImagem.mat=mat;
    qrcode.QRImagem.m=m;
    qrcode.QRImagem.n=n;
}

#endif //QRCODE_POSICIONAMENTODEMODULOEMMATRIZ_H
