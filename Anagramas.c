/*Indica si dos palabras son anagramas o no*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define TAM 30

int anagrama(char*str1,char*str2);


int main()
{
    char palabra1[]="mani";
    char palabra2[]="iman";
    int ana;
    ana=anagrama(palabra1, palabra2);
    if(ana==1)
        printf("Son anagramas");
    else
        printf("No son anagramas");

    return 0;

}
int anagrama(char*str1,char*str2)
{
    int cont=0,cant=0;
    char*cad=str1;
    char*cad2=str2;
    while(*cad2)
    {
        if(*cad2>='A'&&*cad2<='z')
            cont++;
        cad2++;
    }
    cad2=str2;
    while(*cad)
    {
        if(*cad>='A'&&*cad<='z')
            cant++;
        cad++;
    }
    cad=str1;
    if(cont!=cant)
        return 0;
    while(*cad)
    {
        if(*cad>='A'&&*cad<='z')
        {
            cad2=str2;
            while(*cad2!=*cad&&*cad2)
                cad2++;
            if(*cad2=='\0')
                return 0;
        }
        cad++;
    }
    cad=str1;
    cad2=str2;
    while(*cad2)
    {
        if(*cad2>='A'&&*cad2<='z')
        {
            cad=str1;
            while(*cad!=*cad2&&*cad)
                cad++;
            if(*cad=='\0')
                return 0;
        }
        cad2++;
    }
    return 1;
}

