#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "Fecha.h"
#include "Fecha.c"
int ingresarEnteroPositivo(const char* mensaje);




int main()
{
    Fecha fIngr = ingresarFecha();

    printf("La fecha ingresada es: %d/%d/%d", fIngr.dia,fIngr.mes,fIngr.anio);

    int dias = ingresarEnteroPositivo("Ingrese la cantidad de dias a sumar:");

    Fecha fSuma = sumarDiasAFecha(&fIngr, dias);
    
    printf("La fecha resultante es: %d/%d/%d\n", fSuma.dia,fSuma.mes,fSuma.anio);

    return 0;
}

int ingresarEnteroPositivo(const char* mensaje)
{
    int n;
    printf("%s\n", mensaje);
    scanf("%d", &n);

    while(n <= 0)
    {
        printf("Error. %s\n", mensaje);
        scanf("%d", &n);
    }

    return n;
}



