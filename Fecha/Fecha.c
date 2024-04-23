#include <stdio.h>
#include <stdbool.h>

#include "Fecha.h"

#define ANIO_BASE 1601


#define esBisiesto(anio) (((anio) % 4 == 0 && (anio) % 100 != 0) || (anio) % 400 == 0)

int CantDiasMes(int mes, int anio);

Fecha ingresarFecha()
{
    Fecha fecha;
    puts("INGRESE LA FECHA EN EL FORMATO DD/MM/AAAA");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while (!esFechaValida(&fecha))
    {
        puts("Fecha invalida. Ingrese la fecha en el formato dd/mm/aaaa");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }

    return fecha;

}

bool esFechaValida(const Fecha* f)
{
    if(f->anio >= ANIO_BASE)
        if(f->mes >= 1 && f->dia <= CantDiasMes(f->mes,f->anio) && f->dia > 0)
            return true;

    return false;
}

Fecha sumarDiasAFecha(const Fecha* fecha, int dias)
{
    Fecha fSuma = *fecha;
    fSuma.dia += dias;

    while (fSuma.dia>CantDiasMes(fSuma.mes, fSuma.anio))    
    {
        fSuma.dia -= CantDiasMes(fSuma.mes, fSuma.anio);
        fSuma.mes++;

        if(fSuma.mes > 12)
        {
            fSuma.mes = 1;
            fSuma.anio++;
        }
    }
    

    return fSuma;

}

int CantDiasMes(int mes, int anio)
{
    int cdm[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(mes == 2 && esBisiesto(anio))
        return 29;
    else
        return cdm[mes];
}

