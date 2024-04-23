/*Crea una matriz cuadrada(MISMA CANT. DE FILAS QUE DE COLUMNAS) de forma dinamica,
la carga el usuario y segun los valores ingresados identifica si es una matriz simetrica o no*/


#include <stdio.h>
#include <stdlib.h>

int **crearMat(int ,int ,int);
void destruirmat(int **, int );
void cargarmat(int **,int ,int );
void mostrarMatriz(int**, int, int);
void EsSimetrica(int **,int,int);



int main()
{
  int f,c,ce;
  do

    printf("Ingrese cantidad de filas y columnas de la matriz:");
    scanf("%d",&f);

    c=f;

    if(f==c)
    {
         int **mat=crearMat(f,c,sizeof(int));
        cargarmat(mat,c,f);
        mostrarMatriz(mat,f,c);
        EsSimetrica(mat,f,c);
        destruirmat(mat,f);

    }

}

int **crearMat(int f,int c,int ce)
{
   int **mat=malloc(f*sizeof(int*));
   if(!mat)
   {
       puts("sin memoria.");
       return NULL;
   }
   int **ult=mat+(f-1);
   int **i;
   for(i=mat;i<=ult;i++)
   {
       *i=malloc(f*ce);
       if (!*i)
      {
       for(int *j=mat;j<=i;j++)
       {
           free(*j);

       }
           free(mat);
           puts("Error");
           return NULL;
      }
   }

    return mat;
}

void destruirmat(int **mat, int f)
{
    int **ult=mat+(f-1);
    int **i;
    for(i=mat;i<=ult;i++)
    {
        free(*i);
    }
    free(mat);
}
void cargarmat(int **mat,int c,int f)
{
    int i,j;
    for(i=0;i<f;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("Ingrese elemento:");
            scanf("%d",&mat[i][j]);

        }
    }
}

void mostrarMatriz(int** mat, int filas, int columnas)
{
    int i,j;
    for(i=0; i<filas; i++)
    {
        for(j=0; j<columnas; j++)
        {

            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}
void EsSimetrica(int **mat,int c,int f)
{
    int i,IniC=0,FinalF=f-1,Filacont=f-1,ColCont=c-1,band=0;

    while(band==0 && IniC<=c-1 && FinalF>=f-1)
    {
        for(i=IniC;i<FinalF;i++)
        {
            if(mat[i][IniC]==mat[Filacont][ColCont])
            {
                band=0;
            }
            else
            {
                band=1;
            }


            ColCont--;
        }
        Filacont--;
        IniC++;
        FinalF--;
    }
    if(band==0)
    {
        printf("La matriz es simetrica");
    }
    else
    {
        printf("No es simetrica.");
    }
}

