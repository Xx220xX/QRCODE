//
// Created by MORADIA082663 on 19/12/2018.
//

#ifndef QRCODE_MASKRAMENTO_H
#define QRCODE_MASKRAMENTO_H

#include "Object.h"

int temBloco_Aux_A2(int i0, int j0, int *mat, int m, int n);

int padrao_Aux_A3(int i0, int j0, int *mat, int m, int n);

int fiveEqualBlocksColuns_Aux_A1(int i0, int j0, int *mat, int m, int n);

int fiveEqualBlocksLines_Aux_A1(int i0, int j0, int *mat, int m, int n);

int Penalidade_A1(int *mat, int m, int n) {
    int i, j;
    int pontuacao = 0;
    int aux;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            //verificar se ha cinco bloquinho iguais consecutivos, se sim, penalidade = 3, a caso apos os cincos há mais blocos, 1 de penalidade por cada bloco
            //verificar na horizontal e na vertical, e somar as duas
            aux = fiveEqualBlocksLines_Aux_A1(i, j, mat, m, n);
            if (aux) {
                pontuacao += aux;
                aux += 1;
                j += aux;
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            //verificar se ha cinco bloquinho iguais consecutivos, se sim, penalidade = 3, a caso apos os cincos há mais blocos, 1 de penalidade por cada bloco
            //verificar na horizontal e na vertical, e somar as duas
            aux = fiveEqualBlocksColuns_Aux_A1(i, j, mat, m, n);
            if (aux) {
                pontuacao += aux;
                aux += 1;
                i += aux;
            }
        }
    }
}

int Penalidade_A2(int *mat, int m, int n) {
    int i, j;
    int blocos = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            //contar a quantidade de blocos de 2x2 da mesma cor, incluindo os sobrepostos, penalidade = numero de blocos * 3;
            blocos += temBloco_Aux_A2(i, j, mat, m, n);
        }
    }
    return (blocos * 3);
}

int Penalidade_A3(int *mat, int m, int n) {
    //procurar o padrão
    //10111010000 ou 00001011101 (cores), Cada vez que esse padrão é encontrado, adicione 40 à pontuação de penalidade
    int i, j;
    int pontuacao = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            pontuacao += padrao_Aux_A3(i, j, mat, m, n);
        }
    }
    return pontuacao;
}


int Penalidade_A4(int *mat, int m, int n) {
    int i, j, pretas = 0, total;
    int porcentagem, multiplo_ant, multiplo_seg, penalidade;
    total = m * n;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i * n + j] == 1)
                pretas++;
        }
    }
    porcentagem = total / pretas;
    multiplo_ant = ((porcentagem / 5) * 5 - 50) / 5;
    multiplo_seg = (((porcentagem + 5) / 5) * 5 - 50) / 5;
    if (multiplo_ant < 0)
        multiplo_ant *= (-1);
    if (multiplo_seg < 0)
        multiplo_seg *= (-1);
    
    if (multiplo_ant < multiplo_seg)
        penalidade = multiplo_ant * 10;
    else
        penalidade = multiplo_seg * 10;
    return penalidade;
}

int penalidadeMax(int *mat, int m, int n) {
    int pontuacao = 0, aux;
    aux = Penalidade_A1(mat, m, n);
    LOG("    Penalidade 1: %d\n", aux);
    pontuacao += aux;
    aux = Penalidade_A2(mat, m, n);
    LOG("    Penalidade 2: %d\n", aux);
    pontuacao += aux;
    aux = Penalidade_A3(mat, m, n);
    LOG("    Penalidade 3: %d\n", aux);
    pontuacao += aux;
    aux = Penalidade_A4(mat, m, n);
    LOG("    Penalidade 4: %d\n", aux);
    pontuacao += aux;
    LOG("    Penalidade total : %d\n", pontuacao);
    return pontuacao;
}


void aplicando_Masc(int num_mascara, int *origin, int *buff, int m, int n) {
    int i, j;
    LOG("\n\n modulo2\n");
    printaQRIMG(qrcode.QRImagem.mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
    LOG("\n\n");
    
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            if (origin[i * n + j] < 20) {
                buff[i * n + j] = (origin[i * n + j] % 2);
                if (num_mascara == 0) {
                    printf("i : %d, j : %d __ %d, mat = %d\n", i, j, origin[i * n + j], buff[i * n + j]);
                }
            } else {
                buff[i * n + j] = (origin[i * n + j] % 2);
                switch (num_mascara) {
                    case 0:
                        if ((i + j) % 2 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                            printf("+");
                        }
                        break;
                    case 1:
                        if (i % 2 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    case 2:
                        if (j % 3 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    case 3:
                        if ((i + j) % 3 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    case 4:
                        if (((i / 2) + (j / 3)) % 2 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    case 5:
                        if (((i * j) % 2) + ((i * j) % 3) == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    case 6:
                        if ((((i * j) % 2) + ((i * j) % 3)) % 2 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    case 7:
                        if ((((i + j) % 2) + ((i * j) % 3)) % 2 == 0) {
                            buff[i * n + j] = origin[i * n + j] == '1' ? 0 : 1;
                        }
                        break;
                    default:break;
                }
                if (num_mascara == 0) {
                    printf("----------->i : %d, j : %d __ %d, mat = %d\n", i, j, origin[i * n + j], buff[i * n + j]);
                }
    
            }
        }
    }
    
}

void MASK_ETAPA_MASCARAR() {
    LOG("\n\n_______________________Mascarar_____________________________ \n\n");
    int pontuacao1, pontuacao2;
    int i = 0;
    int melhorMask = 0;
    int *mat = (int *) calloc(qrcode.QRImagem.m * qrcode.QRImagem.n, sizeof(int));
    for (int i = 0; i < 8; i++) {
        LOG("\n   Mascara %d\n", i);
        aplicando_Masc(i, qrcode.QRImagem.mat, mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
        printaQRIMG(mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
        if (i == 0) {
            pontuacao1 = penalidadeMax(mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
        } else {
            pontuacao2 = penalidadeMax(mat, qrcode.QRImagem.m, qrcode.QRImagem.n);
            if (pontuacao1 > pontuacao2) {
                pontuacao1 = pontuacao2;
                melhorMask = i;
            }
        }
    }
    free(mat);
}

int temBloco_Aux_A2(int i0, int j0, int *mat, int m, int n) {
    int a;
    if (i0 >= 0 && i0 < m && i0 + 1 < m) {
        if (j0 >= 0 && j0 < n && j0 + 1 < n) {
            a = mat[i0 * n + j0];
            if (a == mat[i0 * n + j0 + 1] && a == mat[(i0 + 1) * n + j0] && mat[(i0 + 1) * n + j0 + 1]) {
                return 1;
            }
        }
    }
    return 0;
}

int padrao_Aux_A3(int i0, int j0, int *mat, int m, int n) {
    int i = 0, k = i0;
    int vet1[11] = {1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0};
    int vet2[11] = {0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1};
    int p1 = 1, p2 = 1;
    int pontuacao = 0;
    for (i = 0; i0 < i0 + 11; i0++, i++) {
        if (i0 >= m) {
            p1 = p2 = 0;
            break;
        }
        if (vet1[i] != mat[i0 * n + j0] && p1) {
            p1 = 0;
        }
        if (vet2[i] != mat[i0 * n + j0] && p2) {
            p2 = 0;
        }
    }
    if (p1) {
        pontuacao += 40;
    }
    if (p2) {
        pontuacao += 40;
    }
    for (p1 = 1, p2 = 1, i = 0; j0 < j0 + 11; j0++, i++) {
        if (j0 >= n) {
            p1 = p2 = 0;
            break;
        }
        if (vet1[i] != mat[i0 * n + j0] && p1) {
            p1 = 0;
        }
        if (vet2[i] != mat[i0 * n + j0] && p2) {
            p2 = 0;
        }
    }
    if (p1) {
        pontuacao += 40;
    }
    if (p2) {
        pontuacao += 40;
    }
    return pontuacao;
}

int fiveEqualBlocksLines_Aux_A1(int i0, int j0, int *mat, int m, int n) {
    int repetidos = 0;
    for (; j0 < n; j0++) {
        if (j0 + 1 < n) {
            if (mat[i0 * n + j0] == mat[i0 * n + (j0 + 1)]) {
                repetidos++;
            } else {
                break;
            }
        }
    }
    if (repetidos > 5) {
        return repetidos - 2;
    }
    return 0;
}

int fiveEqualBlocksColuns_Aux_A1(int i0, int j0, int *mat, int m, int n) {
    int repetidos = 0;
    for (; i0 < n; i0++) {
        if (i0 + 1 < m) {
            if (mat[i0 * n + j0] == mat[(i0 + 1) * n + j0]) {
                repetidos++;
            } else {
                break;
            }
        }
    }
    if (repetidos > 5) {
        return repetidos - 2;
    }
    return 0;
}


#endif //QRCODE_MASKRAMENTO_H
