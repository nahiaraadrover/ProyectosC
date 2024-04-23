#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fecha/Fecha.h"
#include "../Cadena/Cadena.c"


#define TAM_DNI 8
#define TAM_APYNOM 50
#define TAM_SEXO 1
#define TAM_FECHA 8
#define TAM_SUELDO 12

#define CANT_EMPL 10
#define ARG_BIN 1
#define ARG_TXT 2
#define ARG_TIPO_TXT 3

#define TODO_OK 0
#define ERROR_ARCH 1
#define ERROR_LINEA_LARGA 2

#define TAM_LINEA 500


typedef struct
{
    int dni;
    char apYNom[TAM_APYNOM + 1];
    char sexo;
    Fecha fechaIngr;
    float sueldo;
}
Empleado;


typedef int (*TxtABin)(char* linea, Empleado* empl);


int generarEmpleadosBin(const char* nombreArch);
int archBinATxt(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt);
int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt);
int archTxtABin2(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt);
int txtVarABin(char* linea, Empleado* empl);
int txtFijoABin(char* linea, Empleado* empl);
int mostrarEmpleadosBin(const char* nombreArch);


int main(int argc, char* argv[])
{
    // int ret = generarEmpleadosBin(argv[ARG_BIN]);

    // if(ret != TODO_OK)
    //     return ret;

    // archBinATxt(argv[ARG_BIN], argv[ARG_TXT], argv[ARG_TIPO_TXT][0]);

    int ret = archTxtABin2(argv[ARG_BIN], argv[ARG_TXT], argv[ARG_TIPO_TXT][0]);

	mostrarEmpleadosBin(argv[ARG_BIN]);

    return ret;
}


int generarEmpleadosBin(const char* nombreArch)
{
    Empleado empleados[CANT_EMPL] =
    {
        {11222333, "Perez, Juan", 'M', {1, 2, 2020}, 100000.00},
        {22333444, "Gomez, Ana", 'F', {2, 3, 2020}, 200000.00},
        {33444555, "Gonzalez, Luis", 'M', {3, 4, 2020}, 300000.00},
        {44555666, "Rodriguez, Maria", 'F', {4, 5, 2020}, 400000.00},
        {55666777, "Fernandez, Carlos", 'M', {5, 6, 2020}, 500000.00},
        {66777888, "Lopez, Sofia", 'F', {6, 7, 2020}, 600000.00},
        {77888999, "Martinez, Jorge", 'M', {7, 8, 2020}, 700000.00},
        {88999000, "Sanchez, Andrea", 'F', {8, 9, 2020}, 800000.00},
        {99000011, "Gimenez, Pablo", 'M', {9, 10, 2020}, 900000.00},
        {10000122, "Blanco, Carolina", 'F', {10, 11, 2020}, 1000000.00}
    };

    FILE* archEmpleados = fopen(nombreArch, "wb");

    if(archEmpleados == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", nombreArch);
        return 1;
    }

    fwrite(empleados, sizeof(Empleado), CANT_EMPL, archEmpleados); // Como es un vector de estructura, tiene la direccion del primer byte
                                                                   // de la primera escrictura  y no hace falta &

    fclose(archEmpleados);

    return TODO_OK;
}


int archBinATxt(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nombreArchBin, "rb");

    if(!archBin)
        return ERROR_ARCH;

    FILE* archTxt = fopen(nombreArchTxt, "wt");

    if(!archTxt)
        return ERROR_ARCH;

    char* formatoTxt = tipoTxt == 'V'? "%d|%s|%c|%d/%d/%d|%.2f\n" : "%08d%-50s%c%02d%02d%04d%012.2f\n"; // La alineacion siempre es a la izquierda,
                                                                                                        // Con el - se cambia para que sea a la derecha

    Empleado empl;
    fread(&empl, sizeof(Empleado), 1, archBin);
    while(!feof(archBin))
    {
        fprintf
        (
            archTxt,
            formatoTxt,
            empl.dni, empl.apYNom, empl.sexo, empl.fechaIngr.dia, empl.fechaIngr.mes, empl.fechaIngr.anio, empl.sueldo /*Convierte los registros a texto
                                                                                                                         y los graba en el archivo de texto */
        );

        fread(&empl, sizeof(Empleado), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nombreArchBin, "wb");

    if(!archBin)
        return ERROR_ARCH;

    FILE* archTxt = fopen(nombreArchTxt, "rt");

    if(!archTxt)
        return ERROR_ARCH;

    char* formatoTxt = tipoTxt == 'V'? "%d|%[^|]|%c|%d/%d/%d|%f" : "%8d%50[^\n]%c%2d%2d%4d%12f";

    Empleado empl;
    while
    (
        fscanf
        (
            archTxt,
            formatoTxt,
            &empl.dni, empl.apYNom, &empl.sexo,
			&empl.fechaIngr.dia, &empl.fechaIngr.mes, &empl.fechaIngr.anio, // Los & son para que convierta el tipo de archivo a binario, pero como apynom
                                                                            // Ya es un vector de char, lo copia directamente
			&empl.sueldo
        ) != EOF
    )
    {
        rTrim(empl.apYNom);

		fwrite(&empl, sizeof(Empleado), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


int archTxtABin2(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nombreArchBin, "wb");

    if(!archBin)
        return ERROR_ARCH;

    FILE* archTxt = fopen(nombreArchTxt, "rt");

    if(!archTxt)
		return ERROR_ARCH;

	TxtABin txtABin = tipoTxt == 'V'? txtVarABin : txtFijoABin;

    Empleado empl;
    char linea[TAM_LINEA];
	fgets(linea, TAM_LINEA, archTxt);
	while(!feof(archTxt))
    {
		txtABin(linea, &empl);
		fwrite(&empl, sizeof(Empleado), 1, archBin);
		fgets(linea, TAM_LINEA, archTxt);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


int txtVarABin(char* linea, Empleado* empl)
{
	char* act = strchr(linea, '\n');

	if(!act)
		return ERROR_LINEA_LARGA;

	*act = '\0';
	act = strrchr(linea, '|');
	sscanf(act + 1, "%f", &empl->sueldo);

	*act = '\0';
	act = strrchr(linea, '|');
	sscanf(act + 1, "%d/%d/%d", &empl->fechaIngr.dia, &empl->fechaIngr.mes, &empl->fechaIngr.anio);

	*act = '\0';
	act = strrchr(linea, '|');
	empl->sexo = *(act + 1);

	*act = '\0';
	act = strrchr(linea, '|');
	strncpy(empl->apYNom, act + 1, TAM_APYNOM);
	empl->apYNom[TAM_APYNOM] = '\0';

	*act = '\0';
	sscanf(linea, "%d", &empl->dni);

	return TODO_OK;
}


int txtFijoABin(char* linea, Empleado* empl)
{
	char* act = strchr(linea, '\n');

	if(!act)
		return ERROR_LINEA_LARGA;

	*act = '\0';
	act -= TAM_SUELDO;
	sscanf(act, "%f", &empl->sueldo);

	*act = '\0';
	act -= TAM_FECHA;
	sscanf(act, "%2d%2d%4d", &empl->fechaIngr.dia, &empl->fechaIngr.mes, &empl->fechaIngr.anio);

	*act = '\0';
	act -= TAM_SEXO;
	empl->sexo = *act;

	*act = '\0';
	act -= TAM_APYNOM;
	strcpy(empl->apYNom, act);
	rTrim(empl->apYNom);

	*act = '\0';
	sscanf(linea, "%d", &empl->dni);

	return TODO_OK;
}


int mostrarEmpleadosBin(const char* nombreArch)
{
	FILE* archEmpleados = fopen(nombreArch, "rb");

	if(archEmpleados == NULL)
	{
		printf("No se pudo abrir el archivo %s\n", nombreArch);
		return 1;
	}

	Empleado empl;
	fread(&empl, sizeof(Empleado), 1, archEmpleados);
	while(!feof(archEmpleados))
	{
		printf
		(
			"%08d\t%-30s\t%c\t%02d/%02d/%04d\t%012.2f\n",
			empl.dni, empl.apYNom, empl.sexo, empl.fechaIngr.dia, empl.fechaIngr.mes, empl.fechaIngr.anio, empl.sueldo
		);

		fread(&empl, sizeof(Empleado), 1, archEmpleados);
	}

	fclose(archEmpleados);

	return TODO_OK;
}

int archBinATxt_ALU(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archTxt = fopen(nombreArchTxt,"wt");
    if(!archTxt)
        return ERROR_ARCH;

    FILE* archBin = fopen(nombreArchBin,"rb");
    if(!archBin)
        return ERROR_ARCH;

    char* tipoTexto = tipoTxt == 'V'? "%d|%s|%c|%d/%d/%d|%.2f" : "%08d%-30s%c%02d/%02d/%04d|%012.2f";

    Empleado empl;

    fread(&empl,sizeof(Empleado),1,archBin);

    while(!feof(archBin))
    {
        fprintf(archTxt,
                tipoTexto,
        empl.dni,empl.apYNom,empl.sexo,empl.fechaIngr.dia,empl.fechaIngr.mes,empl.fechaIngr.anio,empl.sueldo);

        fread(&empl,sizeof(Empleado),1,archBin);
    }
    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

int archTxtABin_ALU(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archTxt = fopen(nombreArchTxt,"rt");
    if(!archTxt)
        return ERROR_ARCH;

    FILE* archBin = fopen(nombreArchBin,"wb");
    if(!archBin)
        return ERROR_ARCH;

    char* tipoTexto = tipoTxt == 'V'? "%d|%[^|]|c|%d/%d/%d|%.2f" : "%08d%50[^\n]c%02d/%02d/%04d|%012.2f";

    Empleado empl;


    while(
          fscanf(archTxt,

                 tipoTexto,

                 &empl.dni,empl.apYNom,&empl.sexo,&empl.fechaIngr.dia,&empl.fechaIngr.mes,&empl.fechaIngr.anio,&empl.sueldo

                 ) != EOF
          )
    {
        rTrim(empl.apYNom);
       fwrite(&empl,sizeof(Empleado),1,archBin);
    }
    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}
