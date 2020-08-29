#include<stdio.h>


void interpoladorLagrange(float tabela[100][2], int nPontos, float pontoX){

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

int main(void){

    float tabela[100][2], pontoX;
    int nPontos,i;

    printf("\n\nDigite o numero de pontos na tabela: ");
    scanf("%d",&nPontos);

    printf("\n\nDigite os valores de x e y(Ex: 1 5): \n");
    for(i=0; i<nPontos; i++){
        scanf ("%f",&tabela[i][0]);
        scanf("%f",&tabela[i][1]);
    }
    printf("\n\nTabela digitada :\n");
    printf("-----X------Y------\n");
    for(i=0; i<nPontos; i++)
    {

        printf("| %2.4f  %2.4f  |",tabela[i][0],tabela[i][1]);
        printf("\n");
    }
    printf("-------------------");

    printf("\nDigite o valor de X para encontrar o respectivo Y: ");
    scanf("%f",&pontoX);

    interpoladorLagrange(tabela, nPontos, pontoX);

}
