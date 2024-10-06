#include <stdio.h>
#include <stdlib.h>

FILE *fpin1, *fpin2, *fpout;
int ** imagemR1, ** imagemG1, ** imagemB1, ** imagemR2, ** imagemG2, ** imagemB2;
int ncol, nlin, quantizacao;

void abrir_imagem(int argc, char *argv[]){
    if (argc <= 2)
    {
        printf("Modo correto de uso: <prog> <imagemIn> <imagemOut>\n");
        exit(0);
    }

    if ((fpin1 = fopen(argv[1], "r")) == NULL)
    {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[1]);
        exit(1);
    }

    if ((fpin2 = fopen(argv[2], "r")) == NULL)
    {
        printf("Nao foi possivel abrir arquivo de imagem %s\n", argv[2]);
        exit(1);
    }
}

void ler_cabecalho(FILE *fp){
    char controle[4];
    fscanf(fp, "%s\n", controle);
    fscanf(fp, "%d %d\n", &ncol, &nlin);
    fscanf(fp, "%d\n", &quantizacao);
} // Fim: ler_cabecalho


void ler_imagem(int ***imagemB, int ***imagemG, int ***imagemR, FILE *fp){
    int cont, col, lin;
    *imagemR = (int **)malloc((nlin + 1) * sizeof(int *));
    *imagemG = (int **)malloc((nlin + 1) * sizeof(int *));
    *imagemB = (int **)malloc((nlin + 1) * sizeof(int *));
    for (cont = 0; cont < nlin; cont++)
    {
        (*imagemR)[cont] = (int *)malloc(ncol * sizeof(int));
        if ((*imagemR)[cont] == NULL)
        { /* Alocar memoria para a matriz de pixels */
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
        (*imagemG)[cont] = (int *)malloc(ncol * sizeof(int));
        if ((*imagemG)[cont] == NULL)
        { /* Alocar memoria para a matriz de pixels */
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
        (*imagemB)[cont] = (int *)malloc(ncol * sizeof(int));
        if ((*imagemR)[cont] == NULL)
        { /* Alocar memoria para a matriz de pixels */
            printf("Falha na alocacao de memoria - 1\n");
            exit(1);
        }
    }
    for (lin = 0; lin < nlin; lin++){
        for (col = 0; col < ncol; col++){
            fscanf(fp, "%d ", &(*imagemR)[lin][col]);
            fscanf(fp, "%d ", &(*imagemG)[lin][col]);
            fscanf(fp, "%d ", &(*imagemB)[lin][col]);
        }
    }
} // Fim: ler_imagem

void gravar_imagemOut(char nomearquivo[]){
    if ((fpout = fopen(nomearquivo, "w")) == NULL)
    {
        printf("Nao foi possivel abrir arquivo de saida\n");
        exit(1);
    }

    fprintf(fpout, "P3\n");
    fprintf(fpout, "%d %d\n", ncol, nlin);
    fprintf(fpout, "%d\n", quantizacao);
    printf("Arquivo: %s aberto\n", nomearquivo);
}

void morphing_imagem(FILE *fp1, FILE *fp2){
    double cont;
    char nomearquivo[256];
    
    for (cont = 0.0; cont < 1.0; cont += 0.01){
        sprintf(nomearquivo, "imagensW/transicao%03.lf.pnm", (cont * 100));
        gravar_imagemOut(nomearquivo);
        for (int lin = 0; lin < nlin; lin++){
            for (int col = 0; col < ncol; col++){
                fprintf(fpout, "%0.lf ", (imagemR1[lin][col] * (1.0 - cont) + imagemR2[lin][col] * cont));
                fprintf(fpout, "%0.lf ", (imagemG1[lin][col] * (1.0 - cont) + imagemG2[lin][col] * cont));
                fprintf(fpout, "%0.lf\n", (imagemB1[lin][col] * (1.0 - cont) + imagemB2[lin][col] * cont));
            }
        }
        if (fclose(fpout))
        {
            printf("Erro no fechamento do arquivo de saida\n");
            exit(1);
        }
    }
}


int main(int argc, char *argv[]) {
    //sprintf(argv[1], "anakin.ppm");
    //sprintf(argv[2], "darthvader.ppm");
    abrir_imagem(argc, argv);

    ler_cabecalho(fpin1);
    ler_imagem(&imagemB1, &imagemG1, &imagemR1, fpin1);

    ler_cabecalho(fpin2);
    ler_imagem(&imagemB2, &imagemG2, &imagemR2, fpin2);
    
    morphing_imagem(fpin1, fpin2);

    if (fclose(fpin1))
    {
        printf("Erro no fechamento do arquivo de entrada\n");
        exit(1);
    }

    if (fclose(fpin2))
    {
        printf("Erro no fechamento do arquivo de entrada\n");
        exit(1);
    }

    return 0;
}
