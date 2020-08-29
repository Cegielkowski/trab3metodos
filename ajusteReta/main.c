#include <stdio.h>
#include<stdlib.h>
#include <math.h>

int main ()
{
  
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
  
 
return 0;

}

