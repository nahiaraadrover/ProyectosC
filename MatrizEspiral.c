/*Crea una matriz dinamica de  3x3, hace que el usuario cargue los 9 elementos y la imprime por pantalla en forma de espiral*/

#include <stdio.h>
#include <stdlib.h>

void CargarMat(int, int, int **);
void MostrarMat(int, int, int **);
int ** CrearMat(int,int);

int main()
{
    int f=3,c=3;
    int **mat=CrearMat(f,c);
    CargarMat(f,c,mat);
    MostrarMat(f,c,mat);
    MatEspiral(mat,f,c);

   return 0;
}
int ** CrearMat(int filas,int columnas)
{
    int **mat = malloc(filas * sizeof(int*));

    if(!mat)
    {
        puts("Error sin memoria");
        return NULL;
    }

    for (int i = 0; i < filas; i++)
    {
        mat[i] = malloc(columnas * sizeof(int));
        if(!mat[i])
        {
            for (int j = 0; j < i; j++)
            {
                free(mat[j]);
            }
            free(mat);
            puts("Error sin memoria");
            return NULL;
        }
    }

    return mat;
}
void CargarMat(int f, int c, int **mat)
{
    int i,j;

    for(i=0;i<f;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("Ingrese elemento:\n");
            scanf("%d",&mat[i][j]);
        }
    }
}

void MostrarMat(int f, int c, int **mat)
{
    int i,j;

    for(i=0;i<f;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }
}
void MatEspiral(int **mat,int f,int c)
{
    int iF=0,iC=0,finalF=f-1,finalC=c-1,i;
    printf("Matriz recorrida en forma de espiral/caracol:\n");
    while(iF<=finalF && iC<=finalC)
    {
        for(i=iC;i<=finalC;i++)
        {
            printf("%d\t",mat[iF][i]);
        }
        iF++;

      for(i=iF;i<=finalF;i++)
       {
         printf("%d\t",mat[i][finalC]);
        }
       finalC--;

      if(iF<=finalF)
        {
         for(i=finalC;i>=iC;i--)
        {
            printf("%d\t",mat[finalF][i]);
        }
          finalF--;
         }


    if (iC<= finalC)
        {
            for (int i = finalF; i >= iF; i--)
            {
                printf("%d\t", mat[i][iC]);
            }
            iC++;
        }

    }
}
