#include<stdio.h>
#include<math.h>
#define NMAX 100

void gaussPivo(int m, int n, float a[m][n], float x[n-1]){

    int i,j,k;
    float temp, term;

    for(i=0;i<m-1;i++){
        for(k=i+1;k<m;k++){
            if(fabs(a[i][i])<fabs(a[k][i])){
                //Swap the rows
                for(j=0;j<n;j++){

                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }

        for(k=i+1;k<m;k++){
            term=a[k][i]/ a[i][i];
            for(j=0;j<n;j++){
                a[k][j]=a[k][j]-term*a[i][j];
            }
        }
    }

    //substituição regressiva para calcular os coeficientes
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++){
            x[i]=x[i]-a[i][j]*x[j];
        }
        x[i]=x[i]/a[i][i];
    }
}

void ajustePolinomial(int nPontos, float tabela[NMAX][NMAX+1], int grau, float coeficientes[grau+1], float pontosAjustados[nPontos]){

    int i, j, k;
    float X[2*grau+1], B[grau+1][grau+2], Y[grau+1];

    for(i=0;i<=2*grau;i++){
        X[i]=0;
        for(j=0;j<nPontos;j++){
            X[i]=X[i]+pow(tabela[j][0],i);
        }
    }
    for(i=0;i<=grau;i++){
        Y[i]=0;
        for(j=0;j<nPontos;j++){
            Y[i]=Y[i]+pow(tabela[j][0],i)*tabela[j][1];
        }
    }
    for(i=0;i<=grau;i++){
        for(j=0;j<=grau;j++){
            B[i][j]=X[i+j];
        }
    }
    for(i=0;i<=grau;i++){
        B[i][grau+1]=Y[i];
    }
    gaussPivo(grau+1, grau+2, B, coeficientes);

    for(i=0;i<nPontos;i++){
        for(j=0;j<=grau;j++){
            pontosAjustados[i]+=coeficientes[j]*pow(tabela[i][0],j);
        }
    }

}

int main(void){
    int nPontos, grau, i, j;

    printf("\nDigite o numero de pontos na tabela: ");
    scanf("%d",&nPontos);

    float tabela[NMAX][NMAX+1];
    printf("\nDigite os valores de x e y(Ex: 1 5): \n");
    for(i=0; i<nPontos; i++){
        scanf ("%f",&tabela[i][0]);
        scanf("%f",&tabela[i][1]);
    }

    printf("\nDigite o grau do polinômio:\n");
    scanf("%d",&grau);

    float coeficientes[grau+1], pontosAjustados[nPontos];

    ajustePolinomial(nPontos, tabela, grau, coeficientes, pontosAjustados);

    //print da equacao polinomial
    printf("\nP(x)= ");
    for(i=0;i<=grau;i++){
        printf(" %8.4f x^%d ", coeficientes[i],i);
        if(i != grau){
            printf("+");
        }else{
            printf("\n");
        }
    }
    //print dos pontos ajustados
    for(i=0;i<nPontos;i++){
        printf("\nPonto Ajustado x%d : %8.4f",i, pontosAjustados[i]);
    }
}
