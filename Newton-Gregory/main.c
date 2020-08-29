#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NMAX 100

int fatorial(int n){
    int i,f=1;
    for(i=1;i<=n;i++){
        f=f*i;
    }
    return f;
}

void interpoladorNewtonGregory(float tabela[NMAX][NMAX+1], int nPontos, float pontoX){

    float h, p, y, px=1;
    int i, j;

    //Montando tabela da Ordem de F
    for(j=2;j<=nPontos;j++){
        for(i=0;i<nPontos-1;i++){
        tabela[i][j]=tabela[i+1][j-1]-tabela[i][j-1];
        }
    }

    //Calculo de f(pontoX)
    h=tabela[1][0]-tabela[0][0];
    p=(pontoX-tabela[0][0])/h;
    y=tabela[0][1];
    for(i=1;i<nPontos;i++){
        px=px*(p-(i-1));
        y=y+(tabela[0][i+1]*px)/fatorial(i);
    }

    printf("\n\nO valor de f(%2.4f) e' de: %2.4f\n", pontoX, y);

}

int main(void){

    float tabela[NMAX][NMAX+1], pontoX;
    int i, nPontos;

    printf("\nDigite o numero de pontos na tabela: ");
    scanf("%d",&nPontos);

    printf("\nDigite os valores de x e y(Ex: 1 5): \n");
    for(i=0; i<nPontos; i++){
        scanf ("%f",&tabela[i][0]);
        scanf("%f",&tabela[i][1]);
    }

    printf("\nTabela digitada :\n");
    printf("-----X------Y------\n");
    for(i=0; i<nPontos; i++){
        printf("| %2.4f  %2.4f  |\n",tabela[i][0],tabela[i][1]);
    }
    printf("-------------------");

    printf("\n\nDigite o valor de X para encontrar o respectivo Y: ");
    scanf("%f",&pontoX);

    interpoladorNewtonGregory(tabela, nPontos, pontoX);
}
