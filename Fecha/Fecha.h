#ifndef FECHA_H
#define FECHA_H

#include <stdbool.h>

typedef struct Fecha
{
    int dia;
    int mes;
    int anio;
}
Fecha;

Fecha ingresarFecha();
bool esFechaValida(const Fecha* fecha);
Fecha sumarDiasAFecha(const Fecha* fecha, int dias);



#endif // FECHA_H
