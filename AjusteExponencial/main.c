#include<stdio.h>
#include<conio.h>
#include<math.h>

#define NMAX 10

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

int main()
{
	int nPontos, i;
 	float tabela[NMAX][NMAX+1];
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
  
}
