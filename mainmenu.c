/*
TRABALHO 3 DISCIPLINA DE METODOS NUMERICOS COMPUTACIONAIS
UNESP Bauru - 1 SEM 2020
AMANDA MEIRA        151020191
ARTHUR CIPOLARI     151022071
LUCAS CEGIELKOWSKI  161025978
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NMAX 100

void interpoladorLagrange(float tabela[NMAX][NMAX+1], int nPontos, float pontoX){

    float y, s=1,t=1;
    int i,j;

    for(i=0; i<nPontos; i++){
        s=1;
        t=1;
        for(j=0; j<nPontos; j++){
            if(j!=i){
                s=s*(pontoX-tabela[j][0]);
                t=t*(tabela[i][0]-tabela[j][0]);
            }
        }
        y=y+((s/t)*tabela[i][1]);
    }
    printf("\n\nO valor de f(%2.4f) e' de: %2.4f", pontoX, y);
}

void interpoladorNewton(float tabela[NMAX][NMAX+1], int nPontos, float pontoX){

    int i,j,k;
    float d[NMAX][NMAX], t, y=0,s=1;

    for(j=0;j<nPontos;j++){
        for(i=0;i<nPontos-j;i++){
            d[i][j]=0;
        }
    }
    for(i=0;i<nPontos;i++){
        d[i][0]=tabela[i][1];
    }
    for(j=0;j<nPontos;j++){
        for(i=0;i<nPontos-j;i++){
            if(j==0)    continue;
            d[i][j]=(d[i+1][j-1]-d[i][j-1])/(tabela[i+j][0]-tabela[i][0]);
        }
    }
    y=tabela[0][1];
    for(k=1;k<nPontos;k++){
        s=s*(pontoX-tabela[k-1][0]);
        t=s*d[0][k];
        y=y+t;
    }

    printf("\n\nO valor de f(%2.4f) e' de: %2.4f", pontoX, y);
}

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
    int metodo=9, i, nPontos;

	printf("Programa desenvolvido para o Trabalho 3 da\ndisciplina de Metodos Numericos Computacionais\nda UNESP Bauru - 1 Sem 2020\n\n\n");


    while (metodo!=0){
        printf("\n\n=============MENU===============");
        printf("\n================================");
        printf("\n===  1-Intepolador Lagrange  ===");
        printf("\n===  2-Interpolador Newton   ===");
        printf("\n===  3-Interp.Newton-Gregory ===");
        printf("\n===  4-Ajuste Reta           ===");
        printf("\n===  5-Ajuste Polinomial     ===");
        printf("\n===  6-Ajuste Exponencial    ===");
        printf("\n===  0-Para Sair             ===");
        printf("\n================================");
        printf("\n================================");
        printf("\nEscolha: ");
        scanf ("%d", &metodo);
        if(metodo==0){
            printf ("\nPressione qualquer tecla para fechar...\n");
            exit(0);
        }
        switch (metodo){
        case 1:
            printf("\nINTERPOLADOR LAGRANGE ESCOLHIDO\n\n");
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

            interpoladorLagrange(tabela, nPontos, pontoX);
            break;

        case 2:
           	printf("\nINTERPOLADOR NEWTON ESCOLHIDO\n\n");

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

            interpoladorNewton(tabela, nPontos, pontoX);
            break;

        case 3:
            printf("\nINTERPOLADOR NEWTON-GREGORY ESCOLHIDO\n\n");

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
            break;

        case 4:
            printf("\nAJUSTE RETA ESCOLHIDO\n\n");
            break;

        case 5:
            printf("\nAJUSTE POLINOMIAL ESCOLHIDO\n\n");
            break;

        case 6:
            printf("\nAJUSTE EXPONENCIAL ESCOLHIDO\n\n");
            break;

        default:
            printf("\nOpcao Invalida!\nEscolha novamente...\n\n");
        }
    }
    return 0;
}
