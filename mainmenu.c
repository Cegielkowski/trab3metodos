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

//complemento para executar o ajuste polinomial
void gaussPivo(int m, int n, float a[m][n], float x[n-1]){

    int i,j,k;
    float temp, term;

    for(i=0;i<m-1;i++){
        for(k=i+1;k<m;k++){
            if(fabs(a[i][i])<fabs(a[k][i])){
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

void ajustePolinomial(int nPontos, float tabela[NMAX][NMAX+1], int grau, float coeficientes[NMAX], float pontosAjustados[NMAX]){

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

float AjusteExponencial(int n, float tabela[NMAX][NMAX+1])
{
	int i;
	float SomatorioX=0, SomatorioX2=0, SomatorioY=0, SomatorioXY=0, a, b, A, B, YAjustado[NMAX+1];
    /* Cálculo dos somatórios */
    for(i=1;i<=n;i++)
    {
      SomatorioX = SomatorioX + tabela[0][i];
      SomatorioX2 = SomatorioX2 + tabela[0][i]*tabela[0][i];
      SomatorioY = SomatorioY + log(tabela[1][i]);
      SomatorioXY = SomatorioXY + tabela[0][i]*log(tabela[1][i]);
     }

     /* Cálculo de A e B */
     B = (n*SomatorioXY-SomatorioX*SomatorioY)/(n*SomatorioX2-SomatorioX*SomatorioX);
     A = (SomatorioY - B*SomatorioX)/n;

     /* Transformando A em a e B em b */
     a = exp(A);
     b = exp(B);

     printf("\nOs valores sao: a=%0.2f e b = %0.2f",a,b);
     /* Cálculo dos valores de Y ajustados */
     for (i=1;i<=n;i++)
     {
       YAjustado[i] = a * pow(b, tabela[0][i]);
       printf("\nValor de y[%d] ajustado: %f", i,YAjustado[i]);
     }

}

int main(void){

    float tabela[NMAX][NMAX+1], pontoX, pontosAjustados[NMAX], coeficientes[NMAX];
    int metodo=9, i, j, nPontos, grau;

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
            int i = 0;
            float pontos, x, somax, y, somay, xy, xquad;

            somax = 0;

            somay = 0;

            xy = 0;

            xquad = 0;

            float yquad = 0;

            float a = 0;

            float b = 0;

            float r = 0;

            printf ("######### REGRESSAO LINEAR ##########\n\n");

            printf ("Diga quantos pontos voce tem: ");

            scanf ("%f", &pontos);

            fflush (stdin);

            for (i = 0; i < pontos; i++)
                {

            printf ("\nDigite o valor do %d ponto\n", (i + 1));

            printf ("Digite o valor de " "X" ": ");

            scanf ("%f", &x);

            fflush (stdin);

            printf ("Digite o valor de " "Y" ": ");

            scanf ("%f", &y);

            fflush (stdin);

            somax += x;

            somay += y;

            xy += (x * y);

            xquad += (x * x);

            yquad += (y * y);

            printf ("SomaX= %.2f, SomaY= %.2f, XY= %.2f, Xquad= %.2f", somax,
                       somay, xy, xquad);

            }

                //equacao da reta
                a =
                (((pontos * xy) - (somax * somay)) / ((pontos * xquad) -
                                  (somax * somax)));

            b = (((somay / pontos) - (a * (somax / pontos))));

            printf ("\n\nA equacao da reta e %.1fx + %f \n\n", a, b);

                //coeficiente de pearson
                r =
                (((pontos * xy) -
                  (somax * somay)) / (sqrt (((pontos * xquad) - (pow (somax, 2))) *
                            ((pontos * yquad) - (pow (somay, 2))))));

            printf ("O coeficiente de Pearson e %.5f\n\n", r);

            break;

        case 5:
            printf("\nAJUSTE POLINOMIAL ESCOLHIDO\n\n");

            printf("\nDigite o numero de pontos na tabela: ");
            scanf("%d",&nPontos);

            printf("\nDigite os valores de x e y(Ex: 1 5): \n");
            for(i=0; i<nPontos; i++){
                scanf ("%f",&tabela[i][0]);
                scanf("%f",&tabela[i][1]);
            }

            printf("\nDigite o grau do polinomio:\n");
            scanf("%d",&grau);

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

            break;

        case 6:
            printf("\nAJUSTE EXPONENCIAL ESCOLHIDO\n\n");
            printf("Digite o numero de pontos tabelados.\n");
 			scanf("%d", &nPontos);
 			for(i=1;i<=nPontos;i++)
 			{
  				printf("Digite x[%d]=",i);
  				scanf("%f", &tabela[0][i]);
  				printf("Digite y[%d]=",i);
  				scanf("%f", &tabela[1][i]);
 			}
 			AjusteExponencial(nPontos, tabela);
            break;

        default:
            printf("\nOpcao Invalida!\nEscolha novamente...\n\n");
        }
    }
    return 0;
}
