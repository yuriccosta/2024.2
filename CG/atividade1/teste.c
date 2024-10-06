#include <stdio.h>
/* #include <stdlib.h>

void ler_imagem1(int ** var){
    *var = (int **)malloc((5) * sizeof(int *));
    *var[0] = (int *)malloc((5) * sizeof(int));
    var[0][0] = 15;
    printf("Endereço de var: %p\n", &var);
    printf("Valor de var: %p\n", var);
    printf("Endereço de var[0]: %p\n", &var[0]);
    printf("Valor de var[0]: %p\n", var[0]);
    printf("Valor de var[0][0]: %d\n", var[0][0]);
    
}

int somar(int *numero){
    printf("ANTES DO MALLOC: Endereço de numero: %p\n", &numero);
    printf("ANTES DO MALLOC: Valor de numero: %p\n", numero);
    numero = malloc(sizeof(int));
    *numero = 10;
    printf("Endereço de numero: %p\n", &numero);
    printf("Valor de numero: %p\n", numero);
    printf("Valor de numero: %d\n", *numero);
    return *numero + 1;
} */
int main(int argc, char const *argv[])
{
    int c = 0;
    for (double cont = 0.0; cont < 1.0; cont += 0.01){
        printf("imagens/transicao%03d.pnm\n", (int)(cont * 100));
        //printf("%lf\n", cont);
    }

    printf("%03d\n", (int)(0.400000l * 20));
    printf("%d\n", c);
    return 0;
}
/**/