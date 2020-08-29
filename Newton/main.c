#include<stdio.h>

void interpoladorNewton(float tabela[100][2], int nPontos, float pontoX){

    int i,j,k;
    float d[10][10], t, y=0,s=1;

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

int main(void){

        int i, nPontos;
        float tabela[100][2], pontoX;

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
    }
